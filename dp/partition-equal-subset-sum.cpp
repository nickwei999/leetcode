// 416. �ָ�Ⱥ��Ӽ�
// ����һ��ֻ�����������ķǿ����顣�Ƿ���Խ��������ָ�������Ӽ���ʹ�������Ӽ���Ԫ�غ���ȡ�

// ע��:

// ÿ�������е�Ԫ�ز��ᳬ�� 100
// ����Ĵ�С���ᳬ�� 200
// ʾ�� 1:

// ����: [1, 5, 11, 5]

// ���: true

// ����: ������Էָ�� [1, 5, 5] �� [11].

// ʾ�� 2:

// ����: [1, 2, 3, 5]

// ���: false

// ����: ���鲻�ָܷ������Ԫ�غ���ȵ��Ӽ�.
//  https://leetcode-cn.com/problems/partition-equal-subset-sum/

#if 0
����һ����̬�滮
˼·���㷨

�������Ի�һ�ֱ���������һ��ֻ�����������ķǿ����� \textit{nums}[0]nums[0]���ж��Ƿ���Դ�������ѡ��һЩ���֣�ʹ����Щ���ֵĺ͵������������Ԫ�غ͵�һ�롣�������������ת���ɡ�0-10?1 �������⡹��������봫ͳ�ġ�0-10?1 �������⡹���������ڣ���ͳ�ġ�0-10?1 �������⡹Ҫ��ѡȡ����Ʒ������֮�Ͳ��ܳ������������������������Ҫ��ѡȡ�����ֵĺ�ǡ�õ������������Ԫ�غ͵�һ�롣�����ڴ�ͳ�ġ�0-10?1 �������⡹������ʹ�ö�̬�滮��⡣

��ʹ�ö�̬�滮���֮ǰ��������Ҫ���������жϡ�

��������ĳ��� nn �ж������Ƿ���Ա����֡���� n<2n<2���򲻿��ܽ�����ָ��Ԫ�غ���ȵ������Ӽ������ֱ�ӷ��� \text{false}false��

�������������Ԫ�غ� \textit{sum}sum �Լ����Ԫ�� \textit{maxNum}maxNum����� \textit{sum}sum ���������򲻿��ܽ�����ָ��Ԫ�غ���ȵ������Ӽ������ֱ�ӷ��� \text{false}false����� \textit{sum}sum ��ż�������� \textit{target}=\frac{\textit{sum}}{2}target= 
2
sum
?	
 ����Ҫ�ж��Ƿ���Դ�������ѡ��һЩ���֣�ʹ����Щ���ֵĺ͵��� \textit{target}target����� \textit{maxNum}>\textit{target}maxNum>target������� \textit{maxNum}maxNum ���������Ԫ��֮��һ��С�� \textit{target}target����˲����ܽ�����ָ��Ԫ�غ���ȵ������Ӽ���ֱ�ӷ��� \text{false}false��

������ά���� \textit{dp}dp������ nn �� \textit{target}+1target+1 �У����� \textit{dp}[i][j]dp[i][j] ��ʾ������� [0,i][0,i] �±귶Χ��ѡȡ���ɸ��������������� 00 �������Ƿ����һ��ѡȡ����ʹ�ñ�ѡȡ���������ĺ͵��� jj����ʼʱ��\textit{dp}dp �е�ȫ��Ԫ�ض��� \text{false}false��

�ڶ���״̬֮����Ҫ���Ǳ߽����������������������ڱ߽������

�����ѡȡ�κ�����������ѡȡ������������ 00����˶������� 0 \le i < n0��i<n������ \textit{dp}[i][0]=\text{true}dp[i][0]=true��

�� i==0i==0 ʱ��ֻ��һ�������� \textit{nums}[0]nums[0] ���Ա�ѡȡ����� \textit{dp}[0][\textit{nums}[0]]=\text{true}dp[0][nums[0]]=true��

���� i>0i>0 �� j>0j>0 ����������ȷ�� \textit{dp}[i][j]dp[i][j] ��ֵ����Ҫ�ֱ����������������

��� j \ge \textit{nums}[i]j��nums[i]������ڵ�ǰ������ \textit{nums}[i]nums[i]������ѡȡҲ���Բ�ѡȡ���������ֻҪ��һ��Ϊ \text{true}true������ \textit{dp}[i][j]=\text{true}dp[i][j]=true��

�����ѡȡ \textit{nums}[i]nums[i]���� \textit{dp}[i][j]=\textit{dp}[i-1][j]dp[i][j]=dp[i?1][j]��
���ѡȡ \textit{nums}[i]nums[i]���� \textit{dp}[i][j]=\textit{dp}[i-1][j-\textit{nums}[i]]dp[i][j]=dp[i?1][j?nums[i]]��
��� j < \textit{nums}[i]j<nums[i]������ѡȡ�����ֵĺ͵��� jj ��������޷�ѡȡ��ǰ������ \textit{nums}[i]nums[i]������� \textit{dp}[i][j]=\textit{dp}[i-1][j]dp[i][j]=dp[i?1][j]��

״̬ת�Ʒ������£�

\textit{dp}[i][j]=\begin{cases} \textit{dp}[i-1][j]~|~\textit{dp}[i-1][j-\textit{nums}[i]], & j \ge \textit{nums}[i] \\ \textit{dp}[i-1][j], & j < \textit{nums}[i] \end{cases}
dp[i][j]={ 
dp[i?1][j]?�O?dp[i?1][j?nums[i]],
dp[i?1][j],
?	
  
j��nums[i]
j<nums[i]
?	
 

���յõ� \textit{dp}[n-1][\textit{target}]dp[n?1][target] ��Ϊ�𰸡�

���ߣ�LeetCode-Solution
���ӣ�https://leetcode-cn.com/problems/partition-equal-subset-sum/solution/fen-ge-deng-he-zi-ji-by-leetcode-solution/
��Դ�����ۣ�LeetCode��
����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
#endif
/* ��ά��̬�滮 */
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
    // ������ά���� dp������ n �� target+1 �У�
    // ���� dp[i][j] ��ʾ������� [0,i][0,i] �±귶Χ��ѡȡ���ɸ��������������� 0 �������Ƿ����һ��ѡȡ����ʹ�ñ�ѡȡ���������ĺ͵��� j��
    // ��ʼʱ��dp �е�ȫ��Ԫ�ض��� false��
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

//���ݳ�ʱ
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
//   // ����
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
