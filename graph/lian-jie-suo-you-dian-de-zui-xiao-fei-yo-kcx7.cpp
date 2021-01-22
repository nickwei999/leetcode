/* 给你一个points?数组，表示 2D 平面上的一些点，其中?points[i] = [xi, yi]?。

连接点?[xi, yi] 和点?[xj, yj]?的费用为它们之间的 曼哈顿距离?：|xi - xj| + |yi -
yj|?，其中?|val|?表示?val?的绝对值。

请你返回将所有点连接的最小总费用。只有任意两点之间
有且仅有?一条简单路径时，才认为所有点都已连接。

?

示例 1：



输入：points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
输出：20
解释：

我们可以按照上图所示连接所有点得到最小总费用，总费用为 20 。
注意到任意两个点之间只有唯一一条路径互相到达。
示例 2：

输入：points = [[3,12],[-2,5],[-4,1]]
输出：18
示例 3：

输入：points = [[0,0],[1,1],[1,0],[-1,1]]
输出：4
示例 4：

输入：points = [[-1000000,-1000000],[1000000,1000000]]
输出：4000000
示例 5：

输入：points = [[0,0]]
输出：0
?

提示：

1 <= points.length <= 1000
-106?<= xi, yi <= 106
所有点?(xi, yi)?两两不同。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/min-cost-to-connect-all-points
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/* 最小生成树的模板题目： Kruskal 算法
1、两两互链接创建图；
2、图按照边权重排序；
3、建立并查集；
4、按照排序后的边，在并查集里查看是否已链接，如果没有那么这条边添加进去，否则接着遍历；

复杂度：
时间复杂度：O(n^2log(n))，其中 n 是节点数。一般 Kruskal 是 O(mlogm)
的算法，但本题中 m=n^2 空间复杂度：O(n^2)
 */

class DisjointSetUnion {
   private:
    vector<int> f, rank;
    int n;

   public:
    DisjointSetUnion(int _n) {
        n = _n;
        rank.resize(n, 1);
        f.resize(n);
        for (int i = 0; i < n; i++) {
            f[i] = i;
        }
    }

    int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

    int unionSet(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            return false;
        }
        if (rank[fx] < rank[fy]) {
            swap(fx, fy);
        }
        rank[fx] += rank[fy];
        f[fy] = fx;
        return true;
    }
};

struct Edge {
    int len, x, y;
    Edge(int len, int x, int y) : len(len), x(x), y(y) {}
};

class Solution {
   public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        auto dist = [&](int x, int y) -> int {
            return abs(points[x][0] - points[y][0]) +
                   abs(points[x][1] - points[y][1]);
        };
        int n = points.size();
        DisjointSetUnion dsu(n);
        vector<Edge> edges;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                edges.emplace_back(dist(i, j), i, j);
            }
        }
        sort(edges.begin(), edges.end(),
             [](Edge a, Edge b) -> int { return a.len < b.len; });
        int ret = 0, num = 1;
        for (auto& [len, x, y] : edges) {
            if (dsu.unionSet(x, y)) {
                ret += len;
                num++;
                if (num == n) {
                    break;
                }
            }
        }
        return ret;
    }
};
