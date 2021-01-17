/* n 块石头放置在二维平面中的一些整数坐标点上。每个坐标点上最多只能有一块石头。

如果一块石头的 同行或者同列 上有其他石头存在，那么就可以移除这块石头。

给你一个长度为 n 的数组 stones ，其中 stones[i] = [xi, yi] 表示第 i
块石头的位置，返回 可以移除的石子 的最大数量。

 

示例 1：

输入：stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
输出：5
解释：一种移除 5 块石头的方法如下所示：
1. 移除石头 [2,2] ，因为它和 [2,1] 同行。
2. 移除石头 [2,1] ，因为它和 [0,1] 同列。
3. 移除石头 [1,2] ，因为它和 [1,0] 同行。
4. 移除石头 [1,0] ，因为它和 [0,0] 同列。
5. 移除石头 [0,1] ，因为它和 [0,0] 同行。
石头 [0,0] 不能移除，因为它没有与另一块石头同行/列。
示例 2：

输入：stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
输出：3
解释：一种移除 3 块石头的方法如下所示：
1. 移除石头 [2,2] ，因为它和 [2,0] 同行。
2. 移除石头 [2,0] ，因为它和 [0,0] 同列。
3. 移除石头 [0,2] ，因为它和 [0,0] 同行。
石头 [0,0] 和 [1,1] 不能移除，因为它们没有与另一块石头同行/列。
示例 3：

输入：stones = [[0,0]]
输出：0
解释：[0,0] 是平面上唯一一块石头，所以不可以移除它。
 

提示：

1 <= stones.length <= 1000
0 <= xi, yi <= 104
不会有两块石头放在同一个坐标点上

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/most-stones-removed-with-same-row-or-column
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/* 方法一：
石头就是二维上的点； 根据题意多个石头在同行或者同列即最后可以移除只剩下一个；
归结图论：即有多少个连通分量就是剩余多少个石头；
如果石头横坐标或者纵坐标是相同即两者存在一条边，通过dfs或者bfs可以求出有多少个连通分量；

时间复杂度：O(n^2)
枚举计算任意两个石子是否在同行或同列，建图时间复杂度 O(n^2)
dfs：每个点和每个边都被枚举一次O(n+m)
 */

class Solution {
   public:
    void dfs(int d, vector<vector<int>> &edge, vector<int> &vis) {
        vis[d] = 1;
        for (auto &y : edge[d]) {
            if (!vis[y]) {
                dfs(y, edge, vis);
            }
        }
    }
    int removeStones(vector<vector<int>> &stones) {
        int n = stones.size();
        vector<vector<int>> edge(n);
        vector<int> vis(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (stones[i][1] == stones[j][1] ||
                    stones[i][0] == stones[j][0]) {
                    edge[i].push_back(j);
                }
            }
        }

        int nums = 0;
        for (int i = 0; i < n; ++i) {
            if (vis[i]) {
                continue;
            }
            ++nums;
            dfs(i, edge, vis);
        }

        return n - nums;
    }
};

/* 方法二：
使用并查集，求解连通分量 */

class UnionSet {
   private:
    int cnt = 0;
    unordered_map<int, int> hash;  // node, parent;
   public:
    int find(int x) {
        if (hash.count(x) == 0) {
            hash[x] = x;
            cnt++;
        }

        if (hash[x] != x) {
            hash[x] = find(hash[x]);
        }

        return hash[x];
    }

    void join(int x, int y) {
        int xP = find(x);
        int yP = find(y);
        if (xP == yP) {
            return;
        }
        hash[xP] = yP;
        cnt--;
    }

    int getCnt() { return cnt; }
};
class Solution {
   public:
    // 并查集使用 hashmap实现；横坐标+10000
    int removeStones(vector<vector<int>> &stones) {
        int n = stones.size();
        UnionSet un;
        for (auto &x : stones) {
            un.join(x[0] + 10000, x[1]);
        }
        return n - un.getCnt();
    }
};