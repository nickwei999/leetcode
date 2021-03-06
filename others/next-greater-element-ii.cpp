/* 给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字
x
的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出
-1。

示例 1:

输入: [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数；
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/next-greater-element-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

// 单调栈
class Solution {
   public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        if (nums.empty()) return {};
        int n = nums.size();
        stack<int> stk;  //存储idx
        vector<int> res(n, -1);
        for (int i = 0; i < n; ++i) {
            //大于出栈
            while (!stk.empty() && nums[stk.top()] < nums[i]) {
                res[stk.top()] = nums[i];
                stk.pop();
            }

            stk.push(i);
        }

        int idx = stk.top();
        for (int i = 0; i != idx; i++) {
            while (!stk.empty() && nums[stk.top()] < nums[i]) {
                res[stk.top()] = nums[i];
                stk.pop();
            }
        }

        return res;
    }
};

class Solution {
   public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, -1);
        stack<int> stk;
        for (int i = 0; i < n * 2 - 1; i++) {
            while (!stk.empty() && nums[stk.top()] < nums[i % n]) {
                ret[stk.top()] = nums[i % n];
                stk.pop();
            }
            stk.push(i % n);
        }
        return ret;
    }
};
