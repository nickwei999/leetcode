/* 304. 二维区域和检索 - 矩阵不可变
给定一个二维矩阵，计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1)
，右下角为 (row2, col2) 。

Range Sum Query 2D
上图子矩阵左上角 (row1, col1) = (2, 1) ，右下角(row2, col2) = (4,
3)，该子矩形内元素的总和为 8。



示例：

给定 matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12


提示：

你可以假设矩阵不可变。
会多次调用 sumRegion 方法。
你可以假设 row1 ≤ row2 且 col1 ≤ col2 。 */

/* 二维前缀和：
priSum[i][j] 表示以横小于等于i,纵小于等于j的方块的前缀和；

+—————+—————+—————+—————+
|  0  |  1  |  2  |  3  |
+—————+—————+—————+—————+
|  4  |  5  |  6  |  7  |
+—————+—————+—————+—————+
|  8  |  9  |  10 |  11 |
+—————+—————+—————+—————+
|  12 |  13 |  14 |  15 |
+—————+—————+—————+—————+

假设求5坐标[r1+1, c1+1] 和 15坐标[r2+1, c2+1] 区域的和 S[5~15]；
S[5~15] = S[0~15] - S[0~3] -S[0~12] + S[0];
即：
S = priSum[r2+1, c2+1] - priSum[r1,c2+1] - priSum[r2+1, c1] + priSum[r1, c1];

 */

class NumMatrix {
    vector<vector<int>> priSum;

   public:
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty()) {
            return;
        }
        int row = matrix.size();
        int col = matrix[0].size();
        priSum.resize(row + 1, vector<int>(col + 1, 0));
        for (int i = 1; i <= row; ++i) {
            for (int j = 1; j <= col; ++j) {
                priSum[i][j] = priSum[i - 1][j] + priSum[i][j - 1] -
                               priSum[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return priSum[row2 + 1][col2 + 1] - priSum[row1][col2 + 1] -
               priSum[row2 + 1][col1] + priSum[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */