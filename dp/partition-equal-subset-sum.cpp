// 416. 分割等和子集
// 给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

// 注意:

// 每个数组中的元素不会超过 100
// 数组的大小不会超过 200
// 示例 1:

// 输入: [1, 5, 11, 5]

// 输出: true

// 解释: 数组可以分割成 [1, 5, 5] 和 [11].

// 示例 2:

// 输入: [1, 2, 3, 5]

// 输出: false

// 解释: 数组不能分割成两个元素和相等的子集.
//  https://leetcode-cn.com/problems/partition-equal-subset-sum/

#if 0
方法一：动态规划
思路与算法

这道题可以换一种表述：给定一个只包含正整数的非空数组 \textit{nums}[0]nums[0]，判断是否可以从数组中选出一些数字，使得这些数字的和等于整个数组的元素和的一半。因此这个问题可以转换成「0-10?1 背包问题」。这道题与传统的「0-10?1 背包问题」的区别在于，传统的「0-10?1 背包问题」要求选取的物品的重量之和不能超过背包的总容量，这道题则要求选取的数字的和恰好等于整个数组的元素和的一半。类似于传统的「0-10?1 背包问题」，可以使用动态规划求解。

在使用动态规划求解之前，首先需要进行以下判断。

根据数组的长度 nn 判断数组是否可以被划分。如果 n<2n<2，则不可能将数组分割成元素和相等的两个子集，因此直接返回 \text{false}false。

计算整个数组的元素和 \textit{sum}sum 以及最大元素 \textit{maxNum}maxNum。如果 \textit{sum}sum 是奇数，则不可能将数组分割成元素和相等的两个子集，因此直接返回 \text{false}false。如果 \textit{sum}sum 是偶数，则令 \textit{target}=\frac{\textit{sum}}{2}target= 
2
sum
?	
 ，需要判断是否可以从数组中选出一些数字，使得这些数字的和等于 \textit{target}target。如果 \textit{maxNum}>\textit{target}maxNum>target，则除了 \textit{maxNum}maxNum 以外的所有元素之和一定小于 \textit{target}target，因此不可能将数组分割成元素和相等的两个子集，直接返回 \text{false}false。

创建二维数组 \textit{dp}dp，包含 nn 行 \textit{target}+1target+1 列，其中 \textit{dp}[i][j]dp[i][j] 表示从数组的 [0,i][0,i] 下标范围内选取若干个正整数（可以是 00 个），是否存在一种选取方案使得被选取的正整数的和等于 jj。初始时，\textit{dp}dp 中的全部元素都是 \text{false}false。

在定义状态之后，需要考虑边界情况。以下两种情况都属于边界情况。

如果不选取任何正整数，则被选取的正整数等于 00。因此对于所有 0 \le i < n0≤i<n，都有 \textit{dp}[i][0]=\text{true}dp[i][0]=true。

当 i==0i==0 时，只有一个正整数 \textit{nums}[0]nums[0] 可以被选取，因此 \textit{dp}[0][\textit{nums}[0]]=\text{true}dp[0][nums[0]]=true。

对于 i>0i>0 且 j>0j>0 的情况，如何确定 \textit{dp}[i][j]dp[i][j] 的值？需要分别考虑以下两种情况。

如果 j \ge \textit{nums}[i]j≥nums[i]，则对于当前的数字 \textit{nums}[i]nums[i]，可以选取也可以不选取，两种情况只要有一个为 \text{true}true，就有 \textit{dp}[i][j]=\text{true}dp[i][j]=true。

如果不选取 \textit{nums}[i]nums[i]，则 \textit{dp}[i][j]=\textit{dp}[i-1][j]dp[i][j]=dp[i?1][j]；
如果选取 \textit{nums}[i]nums[i]，则 \textit{dp}[i][j]=\textit{dp}[i-1][j-\textit{nums}[i]]dp[i][j]=dp[i?1][j?nums[i]]。
如果 j < \textit{nums}[i]j<nums[i]，则在选取的数字的和等于 jj 的情况下无法选取当前的数字 \textit{nums}[i]nums[i]，因此有 \textit{dp}[i][j]=\textit{dp}[i-1][j]dp[i][j]=dp[i?1][j]。

状态转移方程如下：

\textit{dp}[i][j]=\begin{cases} \textit{dp}[i-1][j]~|~\textit{dp}[i-1][j-\textit{nums}[i]], & j \ge \textit{nums}[i] \\ \textit{dp}[i-1][j], & j < \textit{nums}[i] \end{cases}
dp[i][j]={ 
dp[i?1][j]?∣?dp[i?1][j?nums[i]],
dp[i?1][j],
?	
  
j≥nums[i]
j<nums[i]
?	
 

最终得到 \textit{dp}[n-1][\textit{target}]dp[n?1][target] 即为答案。

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/partition-equal-subset-sum/solution/fen-ge-deng-he-zi-ji-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
#endif
/* 二维动态规划 */
class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int max = *max_element(nums.begin(), nums.end());
    if ((sum & 1) || max > sum / 2) {
      return false;
    }
    const int col = sum / 2 + 1;
    const int row = nums.size();
    // 创建二维数组 dp，包含 n 行 target+1 列，
    // 其中 dp[i][j] 表示从数组的 [0,i][0,i] 下标范围内选取若干个正整数（可以是 0 个），是否存在一种选取方案使得被选取的正整数的和等于 j。
    // 初始时，dp 中的全部元素都是 false。
    vector<vector<bool>> dp(row, vector<bool>(col, false));
    for (int i = 0; i < row; ++i) {
      dp[i][0] = true;
    }
    dp[0][nums[0]] = true;

    for (int i = 1; i < row; ++i) {
      for (int j = 1; j < col; ++j) {
        if (dp[i][j]) {
          continue;
        }
        dp[i][j] = dp[i - 1][j];
        if (!dp[i][j] && nums[i] <= j) {
          dp[i][j] = dp[i - 1][j - nums[i]];
        }
      }
    }

    return dp[row - 1][col - 1];
  }
};

//回溯超时
// class Solution {
//   bool res;
//   void bt(int& sum, int idx, vector<int>& nums) {
//     if (sum == 0 || res == true) {
//       res = true;
//       return;
//     } else if (sum < 0 && idx != 0) {
//       return;
//     }

//     for (; idx < nums.size(); idx++) {
//       sum -= nums[idx];
//       bt(sum, idx + 1, nums);
//       sum += nums[idx];
//     }
//   }

//  public:
//   // 回溯
//   bool canPartition(vector<int>& nums) {
//     int mid = 0;
//     for (auto& x : nums) {
//       mid += x;
//     }
//     if (mid & 1) {
//       return false;
//     }
//     mid >>= 1;
//     sort(nums.begin(), nums.end(), greater<int>());
//     res = false;
//     bt(mid, 0, nums);
//     return res;
//   }
// };
