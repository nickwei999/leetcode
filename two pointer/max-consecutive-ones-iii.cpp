/* 给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从 0 变成 1 。

返回仅包含 1 的最长（连续）子数组的长度。

 

示例 1：

输入：A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
输出：6
解释：
[1,1,1,0,0,1,1,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 6。
示例 2：

输入：A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
输出：10
解释：
[0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 10。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/max-consecutive-ones-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/* 方法一：
找到一段连续的1，向右边扩展；
如果到达右边界还未使用完K,则向左边扩展；直到使用完K或者达到左边界； */

#define min(a, b) ((a) >= (b) ? (b) : (a))

class Solution {
   public:
    int longestOnes(vector<int>& A, int K) {
        // 每一段1开始作为边界进行左右延伸；
        vector<int> dataLen;
        int n = A.size();
        int tmpLen = 1;

        for (int i = 0; i < A.size(); ++i) {
            if (i == n - 1 || A[i] != A[i + 1]) {
                dataLen.push_back(tmpLen);
                tmpLen = 1;
                continue;
            }
            tmpLen++;
        }

        int res = min(K, A.size());
        tmpLen = 0;

        // 从1开始的
        for (int i = A[0] == 0 ? 1 : 0; i < dataLen.size(); i += 2) {
            int j = i;  // j is all oneNumbers;
            int leftK = K;

            tmpLen = 0;  // go right
            while (j < dataLen.size() && leftK >= 0) {
                tmpLen += dataLen[j];
                if (j + 1 < dataLen.size()) {
                    tmpLen += min(leftK, dataLen[j + 1]);
                    leftK -= dataLen[j + 1];
                }
                j += 2;
            }

            j = i;  // go left
            while (j > 0 && leftK > 0) {
                if (j != i) {
                    tmpLen += dataLen[j];
                }
                if (j - 1 >= 0) {
                    tmpLen += min(leftK, dataLen[j - 1]);
                    leftK -= dataLen[j - 1];
                }
                j -= 2;
            }
            res = max(res, tmpLen);
        }

        return res;
    }
};

/* 前缀和：
每个位置记录从开始到当前有多少个0；两个相减即中间有多少个0；
如果两者差大于K，那么移动左指针，直到差小于K;更新距离 */
class Solution {
   public:
    int longestOnes(vector<int>& A, int K) {
        int n = A.size();
        int left = 0, lsum = 0, rsum = 0;
        int ans = 0;
        for (int right = 0; right < n; ++right) {
            rsum += 1 - A[right];
            while (lsum < rsum - K) {
                lsum += 1 - A[left];
                ++left;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};

/* 类似题目：
今天，书店老板有一家店打算试营业 customers.length 分钟。每分钟都有一些顾客（customers[i]）会进入书店，所有这些顾客都会在那一分钟结束后离开。

在某些时候，书店老板会生气。 如果书店老板在第 i 分钟生气，那么 grumpy[i] =
1，否则 grumpy[i] = 0。
当书店老板生气时，那一分钟的顾客就会不满意，不生气则他们是满意的。

书店老板知道一个秘密技巧，能抑制自己的情绪，可以让自己连续 X
分钟不生气，但却只能使用一次。

请你返回这一天营业下来，最多有多少客户能够感到满意的数量。
 

示例：

输入：customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], X = 3
输出：16
解释：
书店老板在最后 3 分钟保持冷静。
感到满意的最大客户数量 = 1 + 1 + 1 + 1 + 7 + 5 = 16.
 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/grumpy-bookstore-owner
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

class Solution {
   public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        // 损失客户数量前缀和
        // 算出损失数量最大的X段
        int left = 0, tmpMax = 0;
        int n = grumpy.size();
        int lSum = 0, rSum = 0;
        for (int right = 0; right < n; ++right) {
            while (right - left + 1 > X) {
                lSum += customers[left] * grumpy[left];
                left++;
            }
            rSum += customers[right] * grumpy[right];
            tmpMax = max(tmpMax, rSum - lSum);
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (grumpy[i] == 0) {
                res += customers[i];
            }
        }

        res += tmpMax;
        return res;
    }
};