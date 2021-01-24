求解多少个连通分量： bfs/dfs、并查集；
求解是否成环：拓扑排序；

最小生成树： Kruskal 算法，是时间复杂度一般是 O(mlogm); prim算法也是

// 双向bfs
class Solution {
    queue<int> qu[2];
    vector<bool> vis[2];
    bool bfs(int id) {
        int s = qu[id].size();  //每次只扩展当前这一层
        while (s--) {
            int str = qu[id].front();
            qu[id].pop();
            for () {
                //进行扩展和判断
                if (vis[1 - id][x]) {
                    return true;  //如果这个点对方访问过就返回true
                }
            }
        }
        return false;
    }

   public:
    int solve() {
        //一系列预处理操作
        vis[0].clear();
        vis[1].clear();
        vis[0][st] = true;
        vis[1][ed] = true;

        qu[0].clear();
        qu[1].clear();
        qu[0].push(st);
        qu[1].push(ed);

        int tim = 0;       //计时器用于判断走了多少步
        if () return tim;  //如果开始就等于最终就直接返回
        while (!qu[0].empty() && !qu[1].empty()) {
            tim++;
            if (bfs(0)) return tim;
            tim++;
            if (bfs(1)) return tim;
        }
    }
}

//拓扑排序

//并查集:
/* 复杂度：
时间复杂度：O(NlogN)，其中 N 是图中的节点个数。需要遍历图中的 N
条边，对于每条边，需要对两个节点查找祖先，如果两个节点的祖先不同则需要进行合并
需要进行 2 次查找和最多 1 次合并。一共需要进行 2N 次查找和最多 N
次合并，因此总时间复杂度是 O(2NlogN)=O(NlogN)。 */

/* 小技巧：
1、并查集建立点，一般可以直接是数组，然后按照下标索引；
    涉及到坐标的可以将 x*ColNums + y;
    如果是两两互联的，可以是 第i个点和第j个点；
2、建立有时候也可以是hash表，比如字符串等；
 */
class UnionSet {
   private:
    vector<int> root, rank;
    int size;

   public:
    UnionSet(int n) {
        root.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            root[i] = i;
            rank[i] = 1;
        }
        size = n;
    }

    // 路径压缩
    int find(int i) { return (root[i] != i) ? (root[i] = find(root[i])) : i; }

    // 成环返回
    bool join(int i, int j) {
        int iR = find(i);
        int jR = find(j);
        if (iR == jR) {
            return false;
        }

        /* 按秩合并 */
        if (rank[iR] < rank[jR]) {
            swap(iR, jR);
        }
        root[jR] = root[iR];
        rank[iR] += rank[jR];
        return true;
    }
};


Kruskal算法（联合并查集）：
1、所有的边按照权重排序；
2、从最小的边开始，建立并查集和最小生成树；
    如果该边链接的点已经在并查集中（并查集中，jion的时候两个根节点一样），那么该条边跳过；
    否则这点和边加入最小生成树；

prim算法（使用优先队列）：
1、从任意一点V开始；所有顶点置位没有访问状态；
2、从该点，遍历能到的没有范文过的所有其他顶点；加入优先级队列；
3、从队列中选取头部（权重最小的边）；
    如果该边链接的顶点已经访问过，那么从队列删除；
    否则将该边和顶点加入最小生成树，同时将该顶点置位访问过；
