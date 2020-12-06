/* 给你一个按升序排序的整数数组
num（可能包含重复数字），请你将它们分割成一个或多个子序列，其中每个子序列都由连续整数组成且长度至少为
3 。

如果可以完成上述分割，则返回 true ；否则，返回 false 。

 

示例 1：

输入: [1,2,3,3,4,5]
输出: True
解释:
你可以分割出这样两个连续子序列 :
1, 2, 3
3, 4, 5
 

示例 2：

输入: [1,2,3,3,4,4,5,5]
输出: True
解释:
你可以分割出这样两个连续子序列 :
1, 2, 3, 4, 5
3, 4, 5
 

示例 3：

输入: [1,2,3,4,4,5]
输出: False

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/split-array-into-consecutive-subsequences
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

//方法一：
// 对数字x而言，加入一个x-1结尾的子序列比新建子序列更优(因为新建长度为1，小于加入x-1子序列的长度)；
// 如果不存在x-1，那么新建一个子序列，x为结尾；
// 如果存在多个x-1结尾子序列，为了能满足，长度最少为3，需要将x加入最短的子序列中；
// 由此分析可由hash表和最小堆实现；hash表key为以x结尾的数字，data为x结尾子序列的长度；

// 时间复杂度：O(nlogn)，其中 n 是数组的长度。
// 需要遍历数组，对于数组中的每个数，都要对哈希表和最小堆进行更新。每个数对应的最小堆的长度不超过
// n， 因此每次对最小堆的操作的时间复杂度是O(logn)，数组长度为
// n，因此时间复杂度是O(nlogn)。
// 然后需要遍历哈希表中的每一条记录，判断是否满足每个子序列的长度都不小于
// 33，子序列的数量不会超过 n，因此时间复杂度是 O(n)O(n)。 因此总时间复杂度是
// O(nlogn)

class Solution {
   public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> mp;
        for (auto& x : nums) {
            if (mp.find(x) == mp.end()) {
                mp[x] = priority_queue<int, vector<int>, greater<int>>();
            }
            if (mp.find(x - 1) != mp.end()) {
                int prevLength = mp[x - 1].top();
                mp[x - 1].pop();
                if (mp[x - 1].empty()) {
                    mp.erase(x - 1);
                }
                mp[x].push(prevLength + 1);
            } else {
                mp[x].push(1);
            }
        }
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            priority_queue<int, vector<int>, greater<int>> queue = it->second;
            if (queue.top() < 3) {
                return false;
            }
        }
        return true;
    }
};

// 方法二：
// 使用两个hash：  记录数字剩余次数和以此数字结尾的子序列数量；
// 遍历数组数字x而言，加入一个x-1结尾的子序列比新建子序列更优(因为新建长度为1，小于加入x-1子序列的长度)；
// 即：
// 如果 x-1 结尾的子序列存在，那么x-1结尾子序列计数减一， x结尾子序列加一；
// x剩余次数减一； 如果 x-1 结尾的子序列不存在，
// 那么查找x+1、x+2计数是否大于0，不大于0即无法组成长度大于等于3的子序列，返回false;
// 否则，x、x+1、x+2子序列计数都减一，x+2结尾子序列计数加一；

class Solution {
   public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int, int> cntHash, tailHash;
        for (const auto& x : nums) {
            cntHash[x]++;
        }
        for (const auto& x : nums) {
            if (cntHash[x] == 0) continue;
            if (tailHash[x - 1] <= 0) {
                if (cntHash[x + 1] <= 0 || cntHash[x + 2] <= 0) {
                    return false;
                }
                cntHash[x]--;
                cntHash[x + 1]--;
                cntHash[x + 2]--;
                tailHash[x + 2]++;
            } else {
                cntHash[x]--;
                tailHash[x - 1]--;
                tailHash[x]++;
            }
        }
        return true;
    }
};