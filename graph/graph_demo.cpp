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