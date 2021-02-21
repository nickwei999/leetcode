/* 1438. 绝对差不超过限制的最长连续子数组
给你一个整数数组 nums ，和一个表示限制的整数
limit，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于
limit 。

如果不存在满足条件的子数组，则返回 0 。



示例 1：

输入：nums = [8,2,4,7], limit = 4
输出：2
解释：所有子数组如下：
[8] 最大绝对差 |8-8| = 0 <= 4.
[8,2] 最大绝对差 |8-2| = 6 > 4.
[8,2,4] 最大绝对差 |8-2| = 6 > 4.
[8,2,4,7] 最大绝对差 |8-2| = 6 > 4.
[2] 最大绝对差 |2-2| = 0 <= 4.
[2,4] 最大绝对差 |2-4| = 2 <= 4.
[2,4,7] 最大绝对差 |2-7| = 5 > 4.
[4] 最大绝对差 |4-4| = 0 <= 4.
[4,7] 最大绝对差 |4-7| = 3 <= 4.
[7] 最大绝对差 |7-7| = 0 <= 4.
因此，满足题意的最长子数组的长度为 2 。
示例 2：

输入：nums = [10,1,2,4,7,2], limit = 5
输出：4
解释：满足题意的最长子数组是 [2,4,7,2]，其最大绝对差 |2-7| = 5 <= 5 。
示例 3：

输入：nums = [4,2,2,2,4,4,2,2], limit = 0
输出：3 */

/* 方法一：滑动窗口
multiset_set 维护区间内的最大最小值
right指针不停向右移动，如果超了limit，则left指针向右移动，直到不超limit;
更新长度；

复杂度分析：
时间复杂度：O(nlogn)，其中 n 是数组长度。向有序集合中添加或删除元素都是O(logn)
的时间复杂度。每个元素最多被添加与删除一次。 空间复杂度：O(n)，其中 nn
是数组长度。最坏情况下有序集合将和原数组等大。 */

class Solution {
   public:
    int longestSubarray(vector<int>& nums, int limit) {
        multiset<int> set;
        int left = 0, right = 0, res = 0;
        int n = nums.size();
        while (right < n) {
            set.insert(nums[right++]);
            while (*set.rbegin() - *set.begin() > limit) {
                set.erase(set.find(nums[left++]));
            }

            res = max(res, right - left);
        }

        return res;
    }
};

/* 方法二：单调队列

在方法一中，我们仅需要统计当前窗口内的最大值与最小值，因此我们也可以分别使用两个单调队列解决本题。
在实际代码中，我们使用一个单调递增的队列 queMin 维护最小值，
一个单调递减的队列 queMax
维护最大值。这样我们只需要计算两个队列的队首的差值，即可知道当前窗口是否满足条件。

时间复杂度：O(n)，其中 n
是数组长度。我们最多遍历该数组两次，两个单调队列入队出队次数也均为 O(n)。
空间复杂度：O(n)，其中 n 是数组长度。最坏情况下单调队列将和原数组等大。 */
class Solution {
   public:
    int longestSubarray(vector<int>& nums, int limit) {
        deque<int> queMax, queMin;
        int n = nums.size();
        int left = 0, right = 0;
        int ret = 0;
        while (right < n) {
            while (!queMax.empty() && queMax.back() < nums[right]) {
                queMax.pop_back();
            }
            while (!queMin.empty() && queMin.back() > nums[right]) {
                queMin.pop_back();
            }
            queMax.push_back(nums[right]);
            queMin.push_back(nums[right]);
            while (!queMax.empty() && !queMin.empty() &&
                   queMax.front() - queMin.front() > limit) {
                if (nums[left] == queMin.front()) {
                    queMin.pop_front();
                }
                if (nums[left] == queMax.front()) {
                    queMax.pop_front();
                }
                left++;
            }
            ret = max(ret, right - left + 1);
            right++;
        }
        return ret;
    }
};
