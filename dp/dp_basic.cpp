
#include <cstdio>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;
//算法导论 切割钢条
// dp[N]表示长度为N的最优解；
// 从k切割，产生dp[k]和dp[n-k]的两个子问题；
// dp[n] = max(dp[k]+dp[n-k], dp[n]); k: 0 -> n;
class Solution {
   public:
    int cutRodSloution(vector<int> &nums, int len) {
        vector<int> dp((nums.size() > len ? nums.size() : len) + 1);
        for (int i = 1; i <= nums.size(); ++i) {
            dp[i] = nums[i - 1];
        }
        for (int i = 1; i <= len; ++i) {
            for (int j = 1; j <= nums.size() && j <= i; ++j) {
                dp[i] = max(dp[i - j] + dp[j], dp[i]);
            }
        }
        return dp[len];
    }
};

int main1() {
    Solution s;
    int nums[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    vector<int> data(nums, nums + sizeof(nums) / sizeof(nums[0]));
    int len;
    cin >> len;
    cout << s.cutRodSloution(data, len);
}

//矩阵乘法
// m[i, j] 表示区间i，j进行最小乘法次数； m[i, j] =
//     min{m[i, k] + m[k + 1, j] + p[i - 1] * p[k] * p[j]};  // i <= k < j
// 自底向上，区间逐渐扩大：
// 1 <= i <= n - 1; m[i, i + 1];
// 1 <= i <= n - 2; m[i, i + 2];
//O(n^3)
void optimalParens(vector<vector<int>> &data, vector<vector<int>> &m,
                   vector<vector<int>> &posK) {
    int N = data.size() - 1;
    for (int i = 1; i <= N; ++i) {
        m[i][i] = 0;
    }
    for (int l = 2; l <= N; ++l) {
        for (int i = 1; i <= N - l + 1; ++i) {
            int j = i + l - 1;
            for (int k = i; k < j; ++k) {
                int tmpCnt = m[i][k] + m[k + 1][j] +
                             data[i][0] * data[k][1] * data[j][1];
                if (tmpCnt < m[i][j]) {
                    m[i][j] = tmpCnt;
                    posK[i][j] = k;
                }
            }
        }
    }
}
void printOptimalParens(vector<vector<int>> &posK, int i, int j)
{
    if (i == j) {
        printf("A%d", i);
        return;
    }
    printf("(");
    printOptimalParens(posK, i, posK[i][j]);
    printOptimalParens(posK, posK[i][j]+1, j);
    printf(")");
}
int main() {
    vector<vector<int>> data = {{0, 0},  {30, 35}, {35, 15}, {15, 5},
                                {5, 10}, {10, 20}, {20, 25}};
    int N = data.size();
    // m[i, j] 表示区间i，j进行最小乘法次数；
    vector<vector<int>> m(N, vector<int>(N, INT_MAX));
    // posK[i, j] 表示区间i，j进行最小乘法次数分割点的位置；
    vector<vector<int>> posK(N, vector<int>(N, INT_MAX));
    optimalParens(data, m, posK);
    cout << m[2][5] << endl;
    cout << m[1][6] << endl;
    printOptimalParens(posK, 1, 6);
}

最优挖掘子结构性质：
1、做出一个选择；如第一次切割位置k，会产生一个或多个待解决的子问题；
2、假定这选择会得到最优解；
3、假定可获得最优解后，确定会产生哪些子问题，以及如何最好的刻画子问题空间； ---关键：子问题需要相同；
4、利用cut-paste技术证明，作为原问题最优解的组成部分，每个子问题的解就是它本身的最优解；
