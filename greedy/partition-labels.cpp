// 字符串 S
// 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。返回一个表示每个字符串片段的长度的列表。

//  

// 示例：

// 输入：S = "ababcbacadefegdehijhklij"
// 输出：[9,7,8]
// 解释：
// 划分结果为 "ababcbaca", "defegde", "hijhklij"。
// 每个字母最多出现在一个片段中。
// 像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。
//  

// 提示：

// S的长度在[1, 500]之间。
// S只包含小写字母 'a' 到 'z' 。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/partition-labels
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
// 方法一：
// 记录开始和结束时间，并按照开始时间排序后；
// 维护一个left和right指针；每次right和下一个开始时间比较；
// 方法二：
// 不需要记录开始时间，只需要记录字符结束时间；
// 遍历字符串，维护left和right，用每个字符的end更新当前的right；
// 如果当前的right和index相等，说明到了可以划分的边界；

class Solution {
   public:
    static bool myCmp(vector<int> &a, vector<int> &b) { return a[0] < b[0]; }
    vector<int> partitionLabels(string S) {
        vector<int> res;
        vector<vector<int>> posData(26, vector<int>(2, INT_MAX));

        for (int i = 0; i < S.size(); ++i) {
            int idx = S[i] - 'a';
            if (posData[idx][0] == INT_MAX) {
                posData[idx][0] = i;
            }
            posData[idx][1] = i;
        }
        sort(posData.begin(), posData.end(), myCmp);
        int left = posData[0][0];
        int right = posData[0][1];
        for (int i = 1; i < posData.size() && posData[i][0] != INT_MAX; ++i) {
            if (right > posData[i][0]) {
                right = max(posData[i][1], right);
                continue;
            }

            res.push_back(right - left + 1);
            left = posData[i][0];
            right = posData[i][1];
        }
        res.push_back(right - left + 1);
        return res;
    }
};

//=========================
class Solution {
   public:
    vector<int> partitionLabels(string S) {
        int last[26];
        int length = S.size();
        for (int i = 0; i < length; i++) {
            last[S[i] - 'a'] = i;
        }
        vector<int> partition;
        int start = 0, end = 0;
        for (int i = 0; i < length; i++) {
            end = max(end, last[S[i] - 'a']);
            if (i == end) {
                partition.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return partition;
    }
};
