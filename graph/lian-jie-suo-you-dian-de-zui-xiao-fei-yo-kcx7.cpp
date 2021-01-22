/* ����һ��points?���飬��ʾ 2D ƽ���ϵ�һЩ�㣬����?points[i] = [xi, yi]?��

���ӵ�?[xi, yi] �͵�?[xj, yj]?�ķ���Ϊ����֮��� �����پ���?��|xi - xj| + |yi -
yj|?������?|val|?��ʾ?val?�ľ���ֵ��

���㷵�ؽ����е����ӵ���С�ܷ��á�ֻ����������֮��
���ҽ���?һ����·��ʱ������Ϊ���е㶼�����ӡ�

?

ʾ�� 1��



���룺points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
�����20
���ͣ�

���ǿ��԰�����ͼ��ʾ�������е�õ���С�ܷ��ã��ܷ���Ϊ 20 ��
ע�⵽����������֮��ֻ��Ψһһ��·�����ൽ�
ʾ�� 2��

���룺points = [[3,12],[-2,5],[-4,1]]
�����18
ʾ�� 3��

���룺points = [[0,0],[1,1],[1,0],[-1,1]]
�����4
ʾ�� 4��

���룺points = [[-1000000,-1000000],[1000000,1000000]]
�����4000000
ʾ�� 5��

���룺points = [[0,0]]
�����0
?

��ʾ��

1 <= points.length <= 1000
-106?<= xi, yi <= 106
���е�?(xi, yi)?������ͬ��

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/min-cost-to-connect-all-points
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע�������� */

/* ��С��������ģ����Ŀ�� Kruskal �㷨
1�����������Ӵ���ͼ��
2��ͼ���ձ�Ȩ������
3���������鼯��
4�����������ıߣ��ڲ��鼯��鿴�Ƿ������ӣ����û����ô��������ӽ�ȥ��������ű�����

���Ӷȣ�
ʱ�临�Ӷȣ�O(n^2log(n))������ n �ǽڵ�����һ�� Kruskal �� O(mlogm)
���㷨���������� m=n^2 �ռ临�Ӷȣ�O(n^2)
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
