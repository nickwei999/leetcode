// 给定不同面额的硬币 coins 和一个总金额
// amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
// 你可以认为每种硬币的数量是无限的。
// 示例 1：

// 输入：coins = [1, 2, 5], amount = 11
// 输出：3
// 解释：11 = 5 + 5 + 1
// 示例 2：

// 输入：coins = [2], amount = 3
// 输出：-1
// 示例 3：

// 输入：coins = [1], amount = 0
// 输出：0
// 示例 4：

// 输入：coins = [1], amount = 1
// 输出：1
// 示例 5：

// 输入：coins = [1], amount = 2
// 输出：2
//  

// 提示：

// 1 <= coins.length <= 12
// 1 <= coins[i] <= 231 - 1
// 0 <= amount <= 104
// 通过次数147,369提交次数353,248

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/coin-change
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 动态规划：
// 方法一：
// 将金额为n的最少兑换为dp[n];
// dp[n] = min{ d[k] + dp[n-k] };  0 <= k <= n/2;
// 此方法通用，但是k在移动，会计算出很多不必要的中间过程；

// 方法二：
// 将金额为n的最少兑换为dp[n];
// dp[n] = min{dp[n-1] + coins[k]}; 0 <= k < coins.size();

class Solution {
    vector<int> count;
    int dp(vector<int> &coins, int rem) {
        if (rem < 0) return -1;
        if (rem == 0) return 0;
        if (count[rem] != 0) return count[rem];
        int Min = INT_MAX;
        for (int coin : coins) {
            int res = dp(coins, rem - coin);
            if (res >= 0 && res < Min) {
                Min = res + 1;
            }
        }
        count[rem] = Min == INT_MAX ? -1 : Min;
        return count[rem];
    }

   public:
    int coinChange(vector<int> &coins, int amount) {
        if (amount < 1) return 0;
        count.resize(amount + 1);
        return dp(coins, amount);
    }
};
//===================================
//方法一超时：
class Solution0 {
   public:
    int coinChangeInner(vector<int> &dp, int amount) {
        if (amount < 0) return -1;
        if (amount == 0) return 0;
        if (dp[amount] != 0) return dp[amount];
        int tmp = INT_MAX;
        for (int i = 1; i <= amount / 2; ++i) {
            int j = amount - i;
            int left = coinChangeInner(dp, i);
            int right = coinChangeInner(dp, j);
            if (left >= 0 && left < INT_MAX && right >= 0 && right < INT_MAX) {
                tmp = min(left + right, tmp);
            }
        }
        dp[amount] = tmp == INT_MAX ? -1 : tmp;
        return dp[amount];
    }
    int coinChange(vector<int> &coins, int amount) {
        vector<int> dp(amount + 1, 0);
        for (auto &x : coins) {
            if (x <= amount) {
                dp[x] = 1;
            }
        }
        return coinChangeInner(dp, amount);
    }
};