/* 在本问题中, 树指的是一个连通且无环的无向图。

输入一个图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N)
的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。

结果图是一个以边组成的二维数组。每一个边的元素是一对[u, v] ，满足 u <
v，表示连接顶点u 和v的无向图的边。

返回一条可以删去的边，使得结果图是一个有着N个节点的树。如果有多个答案，则返回二维数组中最后出现的边。答案边 [u,
v] 应满足相同的格式 u < v。

示例 1：

输入: [[1,2], [1,3], [2,3]]
输出: [2,3]
解释: 给定的无向图为:
  1
 / \
2 - 3
示例 2：

输入: [[1,2], [2,3], [3,4], [1,4], [1,5]]
输出: [1,4]
解释: 给定的无向图为:
5 - 1 - 2
    |   |
    4 - 3

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/redundant-connection
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/* 使用并查集；
不停加入边，如果两个的根节点是同一个，说明是环，去除这条边即可；
复杂度：

时间复杂度：O(NlogN)，其中 N 是图中的节点个数。需要遍历图中的 N
条边，对于每条边，需要对两个节点查找祖先，如果两个节点的祖先不同则需要进行合并
需要进行 2 次查找和最多 1 次合并。一共需要进行 2N 次查找和最多 N
次合并，因此总时间复杂度是 O(2NlogN)=O(NlogN)。
这里的并查集使用了路径压缩，但是没有使用按秩合并，最坏情况下的时间复杂度是
O(NlogN)，平均情况下的时间复杂度依然是O(Nα(N))，其中 alphaα
为阿克曼函数的反函数， α(N) 可以认为是一个很小的常数。

空间复杂度：O(N)，其中 NN 是图中的节点个数。使用数组 parent 记录每个节点的祖先。
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

    int find(int i) { return (root[i] != i) ? (root[i] = find(root[i])) : i; }

    // 成环返回
    bool join(int i, int j) {
        int iR = find(i);
        int jR = find(j);
        if (iR == jR) {
            return false;
        }

        if (rank[iR] < rank[jR]) {
            swap(iR, jR);
        }
        root[jR] = root[iR];
        rank[iR] += rank[jR];
        return true;
    }
};

class Solution {
   public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        UnionSet un(edges.size() + 1);

        for (auto& x : edges) {
            if (!un.join(x[0], x[1])) {
                return {x[0], x[1]};
            }
        }

        return {};
    }
};
