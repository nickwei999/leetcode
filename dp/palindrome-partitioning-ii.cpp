/* 给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文。

返回符合要求的 最少分割次数 。

 

示例 1：

输入：s = "aab"
输出：1
解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
示例 2：

输入：s = "a"
输出：0
示例 3：

输入：s = "ab"
输出：1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-partitioning-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/* 动态规划：
1、预处理算出[i,j]区间是否是回文；dp[i,j]表示是否是回文；
    如果i==j是回文；
    否则如果 s[i-1] == s[j+1] 并且[i,j]是回文，那么dp[i-1,j+1] 也是回文；
2、区间cnt[i]为最小的切割次数；
    那 cnt[i] = min{cnt[j]+1, cnt[i]}; 如果 dp[j, i]是回文字符；
    如果 dp[0,i]是回文，cnt[i]=0;

复杂度： O(n^2) */

class Solution {
   public:
    int minCut(string s) {
        int n = s.size();
        vector<vector<int>> g(n, vector<int>(n, true));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                g[i][j] = (s[i] == s[j]) && g[i + 1][j - 1];
            }
        }

        vector<int> f(n, INT_MAX);
        for (int i = 0; i < n; ++i) {
            if (g[0][i]) {
                f[i] = 0;
            } else {
                for (int j = 0; j < i; ++j) {
                    if (g[j + 1][i]) {
                        f[i] = min(f[i], f[j] + 1);
                    }
                }
            }
        }

        return f[n - 1];
    }
};