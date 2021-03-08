/* 给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s
所有可能的分割方案。

回文串 是正着读和反着读都一样的字符串。

 

示例 1：

输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
示例 2：

输入：s = "a"
输出：[["a"]]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-partitioning
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/* 1、区间【i,j】是否是回文字符预处理；
2、bt回溯，找出所有方案；
时间复杂度：O(n⋅2^n)，其中 n 是字符串 s 的长度。在最坏情况下，s 包含 n
个完全相同的字符，因此它的任意一种划分方法都满足要求。而长度为 n
的字符串的划分方案数为 O(2^n) 每一种划分方法需要 O(n)
的时间求出对应的划分结果并放入答案，因此总时间复杂度为
O(n⋅2^n)。尽管动态规划预处理需要 O(n^2)的时间，但在渐进意义下小于
O(n*2^n)，因此可以忽略。
 */
class Solution {
   private:
    vector<vector<int>> f;
    vector<vector<string>> ret;
    vector<string> ans;
    int n;

   public:
    void dfs(const string& s, int i) {
        if (i == n) {
            ret.push_back(ans);
            return;
        }
        for (int j = i; j < n; ++j) {
            if (f[i][j]) {
                ans.push_back(s.substr(i, j - i + 1));
                dfs(s, j + 1);
                ans.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        n = s.size();
        f.assign(n, vector<int>(n, true));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1];
            }
        }

        dfs(s, 0);
        return ret;
    }
};

/* 记忆+回溯 */
class Solution {
   private:
    vector<vector<int>> f;
    vector<vector<string>> ret;
    vector<string> ans;
    int n;

   public:
    void dfs(const string& s, int i) {
        if (i == n) {
            ret.push_back(ans);
            return;
        }
        for (int j = i; j < n; ++j) {
            if (isPalindrome(s, i, j) == 1) {
                ans.push_back(s.substr(i, j - i + 1));
                dfs(s, j + 1);
                ans.pop_back();
            }
        }
    }

    // 记忆化搜索中，f[i][j] = 0 表示未搜索，1 表示是回文串，-1 表示不是回文串
    int isPalindrome(const string& s, int i, int j) {
        if (f[i][j]) {
            return f[i][j];
        }
        if (i >= j) {
            return f[i][j] = 1;
        }
        return f[i][j] = (s[i] == s[j] ? isPalindrome(s, i + 1, j - 1) : -1);
    }

    vector<vector<string>> partition(string s) {
        n = s.size();
        f.assign(n, vector<int>(n));

        dfs(s, 0);
        return ret;
    }
};
