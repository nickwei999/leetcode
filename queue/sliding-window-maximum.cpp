/* 给你一个整数数组
nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的
k 个数字。滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。

 

示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sliding-window-maximum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/* 方法一：
使用优先队列保存 pair<value,index>;
每次遍历时，查看堆顶的值是否在滑动窗口之外，如果是那么删除；否则取顶的值作为窗口内的最大值；
遍历到的元素加入优先队列；

在最坏情况下，数组nums
中的元素单调递增，那么最终优先队列中包含了所有元素，没有元素被移除。
由于将一个元素放入优先队列的时间复杂度为 O(logn)，因此总时间复杂度为 O(nlogn)。
*/

class Solution {
   public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<pair<int, int>> q;
        for (int i = 0; i < k; ++i) {
            q.emplace(nums[i], i);
        }
        vector<int> ans = {q.top().first};
        for (int i = k; i < n; ++i) {
            q.emplace(nums[i], i);
            while (q.top().second <= i - k) {
                q.pop();
            }
            ans.push_back(q.top().first);
        }
        return ans;
    }
};

/* 方法二：单调队列
如果当前的滑动窗口中有两个下标 i 和 j，其中 i 在 j 的左侧（i < j），并且 i
对应的元素不大于 j 对应的元素（nums[i] ≤ nums[j]）
当j在的时候，最大值不可能是nums[i];
可以使用单调的双端队列，其中队列首部元素最大； deque<pair<value,index>> que;
对于新遍历到的一个元素而言，如果判断其值大于队列尾部元素，队列尾部弹出；
查看队列首部元素是否在窗口外，如果窗口外，直接弹出；
取队列首部元素既是滑动窗口内的最大值；

每个元素最多入一次队列，出一次队列，复杂度是O(n); */

class Solution {
   public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> q;
        for (int i = 0; i < k; ++i) {
            while (!q.empty() && nums[i] >= nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(i);
        }

        vector<int> ans = {nums[q.front()]};
        for (int i = k; i < n; ++i) {
            while (!q.empty() && nums[i] >= nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(i);
            while (q.front() <= i - k) {
                q.pop_front();
            }
            ans.push_back(nums[q.front()]);
        }
        return ans;
    }
};
