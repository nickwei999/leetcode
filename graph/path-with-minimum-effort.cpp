/* 你准备参加一场远足活动。给你一个二维 rows x
columns 的地图 heights ，其中 heights[row][col] 表示格子 (row,
col) 的高度。一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1,
columns-1) （注意下标从 0 开始编号）。你每次可以往
上，下，左，右 四个方向之一移动，你想要找到耗费 体力 最小的一条路径。

一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的。

请你返回从左上角走到右下角的最小 体力消耗值 。

 

示例 1：



输入：heights = [[1,2,2],[3,8,2],[5,3,5]]
输出：2
解释：路径 [1,3,5,3,5] 连续格子的差值绝对值最大为 2 。
这条路径比路径 [1,2,2,2,5] 更优，因为另一条路径差值最大值为 3 。
示例 2：



输入：heights = [[1,2,3],[3,8,4],[5,3,5]]
输出：1
解释：路径 [1,2,3,4,5] 的相邻格子差值绝对值最大为 1 ，比路径 [1,3,5,3,5] 更优。
示例 3：


输入：heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
输出：0
解释：上图所示路径不需要消耗任何体力。
 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/path-with-minimum-effort
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

// 方法一：
// 将所有权重的边进行排序；
// 将边逐个加入并查集，如果左上和右下连通那就是答案；
// 时间复杂度： O(row*col*log(row*col))
// 并查集的时间复杂度为 O(mn⋅α(mn))，其中 α 为阿克曼函数的反函数.
// 由于后者在渐进意义下小于前者O(mnlog(mn))。

class DjFind {
    vector<int> p, rank;

   public:
    DjFind(int n) {
        p.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            p[i] = i;
        }
    }
    int find(int n) { return p[n] == n ? n : p[n] = find(p[n]); }

    bool join(int x, int y) {
        int xR = find(x);
        int yR = find(y);
        if (xR == yR) {
            return false;
        }
        if (rank[xR] < rank[yR]) {
            swap(xR, yR);
        }
        rank[xR] += rank[yR];
        p[yR] = p[xR];

        if (find(0) == find(p.size() - 1)) {
            return true;
        }
        return false;
    }
};

class Solution {
   public:
    int minimumEffortPath(vector<vector<int>> &heights) {
        // 将所有权重的边进行排序；
        // 将边逐个加入并查集，如果左上和右下连通那就是答案；
        int row = heights.size();
        int col = heights[0].size();
        DjFind un(row * col);

        const vector<vector<int>> dir({{0, 1}, {1, 0}});
        vector<vector<int>> path;  // x y weight
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {  // 向右和向下
                for (auto &d : dir) {
                    int x = i + d[0];
                    int y = j + d[1];
                    if (x < row && y < col) {
                        int w = abs(heights[i][j] - heights[x][y]);
                        path.push_back({i * col + j, x * col + y, w});
                    }
                }
            }
        }

        sort(path.begin(), path.end(),
             [](vector<int> &l, vector<int> &r) { return l[2] < r[2]; });

        for (auto &x : path) {
            if (un.join(x[0], x[1])) {
                return x[2];
            }
        }

        return 0;
    }
};

//方法二： 二分法，判定路径的最大消耗为C;看bfs能否走到右下角；可以不停缩小；

// 方法三： 使用Dijkstra算法