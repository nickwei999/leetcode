/* 给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1
的最大矩形，并返回其面积。

 
示例 1：


输入：matrix =
[["1","0","1","0","0"],
 ["1","0","1","1","1"],
 ["1","1","1","1","1"],
 ["1","0","0","1","0"]]
输出：6
解释：最大矩形如上图所示。
示例 2：

输入：matrix = []
输出：0
示例 3：

输入：matrix = [["0"]]
输出：0
示例 4：

输入：matrix = [["1"]]
输出：1
示例 5：

输入：matrix = [["0","0"]]
输出：0

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximal-rectangle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/*
方法一：动态规划
1、以i行为单位，用left数组记录，截止到j列（即点matrix[i][j]）,连续为1的长度记录为 left[i][j];
2、从点matrix[i][j]，往上遍历，所有以 matrix[k][j] 作为最右下角的矩形：
其长度为：  len = min(left[i][j], left[i-1][j] ... , left[k][j])；
其宽度为：  width = i - k + 1;
其面积为： len*width;

时间复杂度为： row^2*col
*/

class Solution {
   public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int>> left(row, vector<int>(col, 0));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (j == 0) {
                    left[i][j] = matrix[i][j] == '1' ? 1 : 0;
                    continue;
                }
                left[i][j] = matrix[i][j] == '1' ? (left[i][j - 1] + 1) : 0;
            }
        }

        int res = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (left[i][j] == 0) {
                    continue;
                }
                int len = left[i][j];
                for (int k = i; k >= 0; --k) {  // row--
                    len = min(len, left[k][j]);
                    if (len == 0) {
                        break;
                    }
                    int erea = len * (i - k + 1);
                    res = max(res, erea);
                }
            }
        }

        return res;
    }
};