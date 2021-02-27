/* 395. 至少有 K 个重复字符的最长子串
给你一个字符串 s 和一个整数 k ，请你找出 s 中的最长子串，
要求该子串中的每一字符出现次数都不少于 k 。返回这一子串的长度。



示例 1：

输入：s = "aaabb", k = 3
输出：3
解释：最长子串为 "aaa" ，其中 'a' 重复了 3 次。
示例 2：

输入：s = "ababbc", k = 2
输出：5
解释：最长子串为 "ababb" ，其中 'a' 重复了 2 次， 'b' 重复了 3 次。 */

/* 方法一：
枚举字符种类数量 + 滑动窗口；
假设此次，考虑枚举c种字符类型数量；维护区间l,r；
移动r直到字符种类数量大于c;
此时移动l,直到字符种类小于等于c；
判断该字符种类数量情况下，是否每一种字符都满足条件（大于K个）；
如果满足条件，更新长度结果；

复杂度：
O(N⋅∣Σ∣+∣Σ∣^2)
N为数组大小，∣Σ∣为字符集
*/

class Solution {
   public:
    int longestSubstring(string s, int k) {
        int n = s.size();
        if (k == 1) return n;
        int res = 0;

        for (int c = 1; c < 27; ++c) {
            int cnt = 0;  //当前遍历到的字符种类数量
            int left = 0;
            int less = 0;  //当前计数小于k的字符种类数量
            vector<int> charCnt(26, 0);
            for (int right = 0; right < n; ++right) {
                int chIdx = s[right] - 'a';
                if (++charCnt[chIdx] == 1) {
                    cnt++;
                    less++;
                }
                if (charCnt[chIdx] == k) {
                    less--;
                }

                while (cnt > c) {
                    chIdx = s[left++] - 'a';
                    if (--charCnt[chIdx] == 0) {
                        cnt--;
                        less--;
                    }
                    if (charCnt[chIdx] == k - 1) {
                        less++;
                    }
                }

                if (less == 0) {
                    int len = right - left + 1;
                    if (len >= k && len > res) {
                        res = len;
                    }
                }
            }
        }

        return res;
    }
};

/* 方法二：
分治算法：
假设某个字符出现次数小于K,
那么包含该字符的子串都不可能是答案；
即可以以该字符进行分割字符串；

复杂度：
时间复杂度：O(N⋅∣Σ∣)，其中 NN 为字符串的长度，Σ 为字符集，
由于每次递归调用都会完全去除某个字符，因此递归深度最多为 ∣Σ∣。

空间复杂度：O(∣Σ∣^ 2)。递归的深度为 O(∣Σ∣)，每层递归需要开辟 O(∣Σ∣) 的额外空间。
 */

class Solution {
   public:
    int dfs(string &s, int l, int r, int k) {
        vector<int> cnt(26, 0);
        for (int i = l; i <= r; ++i) {
            int idx = s[i] - 'a';
            cnt[idx]++;
        }
        char spilt = 0;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] > 0 && cnt[i] < k) {
                spilt = i + 'a';
            }
        }

        // 不需要分割
        if (spilt == 0) {
            return r - l + 1;
        }

        int res = 0;
        while (l <= r) {
            while (l <= r && s[l] == spilt) {
                l++;
            };
            if (l > r) break;
            int start = l;
            while (l <= r && s[l] != spilt) {
                l++;
            };
            res = max(res, dfs(s, start, l - 1, k));
        }

        return res;
    }

    int longestSubstring(string s, int k) {
        // 任何一个字符出现次数小于k，那包含该字符的子串都不可能是结果；
        //  以该字符作为分割进行分治算法；
        if (k == 1) return s.size();
        return dfs(s, 0, s.size() - 1, k);
    }
};