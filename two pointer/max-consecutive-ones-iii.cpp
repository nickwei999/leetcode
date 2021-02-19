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
