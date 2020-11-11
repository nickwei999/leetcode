// 给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord
// 的最短转换序列的长度。转换需遵循如下规则：

// 每次转换只能改变一个字母。
// 转换过程中的中间单词必须是字典中的单词。
// 说明:

// 如果不存在这样的转换序列，返回 0。
// 所有单词具有相同的长度。
// 所有单词只由小写字母组成。
// 字典中不存在重复的单词。
// 你可以假设 beginWord 和 endWord 是非空的，且二者不相同。
// 示例 1:

// 输入:
// beginWord = "hit",
// endWord = "cog",
// wordList = ["hot","dot","dog","lot","log","cog"]

// 输出: 5

// 解释: 一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog",
//      返回它的长度 5。
// 示例 2:

// 输入:
// beginWord = "hit"
// endWord = "cog"
// wordList = ["hot","dot","dog","lot","log"]

// 输出: 0

// 解释: endWord "cog" 不在字典中，所以无法进行转换。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/word-ladder
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 单向bfs
// 将wrodlist存进hash表，并设置未访问过；
// 将beginWord入que,bfs按层次取出单词，并查看是否到终点
// 逐个改变取出的单词，将在wordList出现的并且没有访问的都存进que;
// 重复这个过程知道终点或者队列为空；

class Solution {
   public:
    bool findFinalWord(const string &endWord,
                       unordered_map<string, bool> &dirWord,
                       queue<string> &que) {
        string lastWord = que.front();
        que.pop();
        if (lastWord == endWord) {
            return true;
        }
        for (int j = 0; j < lastWord.size(); ++j) {
            string tmpWord = lastWord;
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                if (tmpWord[j] == ch) {
                    continue;
                }
                tmpWord[j] = ch;
                if (dirWord.find(tmpWord) != dirWord.end() &&
                    !dirWord[tmpWord]) {
                    que.push(tmpWord);
                    dirWord[tmpWord] = true;
                }
            }
        }
        return false;
    }

    int ladderLength(string beginWord, string endWord,
                     vector<string> &wordList) {
        unordered_map<string, bool> dirWord;
        for (auto &x : wordList) {
            dirWord[x] = false;
        }
        if (dirWord.count(endWord) == 0) {
            return 0;
        }
        queue<string> que;
        que.push(beginWord);
        int res = 0;
        while (!que.empty()) {
            ++res;
            int bfsCnt = que.size();
            for (int i = 0; i < bfsCnt; ++i) {
                if (findFinalWord(endWord, dirWord, que)) {
                    return res;
                }
            }
        }
        return 0;
    }
};

// 双向bfs：
// 维护两个方向的已访问表；
// 维护两个队列；
// 每一轮从两个方向同时bfs，如果一方遍历到对方的已访问列表说明两方相遇；
class Solution {
   public:
    bool findFinalWord(int queID, unordered_set<string> &dirWord,
                       unordered_set<string> (&visitWord)[2],
                       queue<string> (&InputQue)[2]) {
        auto &que = InputQue[queID];
        auto &selfVisit = visitWord[queID];
        auto &otherVisit = visitWord[1 - queID];
        int queSize = que.size();
        while (queSize--) {
            auto lastWord = que.front();
            que.pop();
            for (int j = 0; j < lastWord.size(); ++j) {
                string tmpWord = lastWord;
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    if (tmpWord[j] == ch) {
                        continue;
                    }
                    tmpWord[j] = ch;
                    if (otherVisit.count(tmpWord)) {
                        return true;
                    }
                    //字典不存在或自己访问过了
                    if (!dirWord.count(tmpWord) || selfVisit.count(tmpWord)) {
                        continue;
                    }
                    selfVisit.insert(tmpWord);
                    que.push(tmpWord);
                }
            }
        }

        return false;
    }

    int ladderLength(string beginWord, string endWord,
                     vector<string> &wordList) {
        unordered_set<string> dirWord;
        for (auto &x : wordList) {
            dirWord.insert(x);
        }
        if (!dirWord.count(endWord)) {
            return 0;
        }

        unordered_set<string> visitWord[2];
        visitWord[0].insert(beginWord);
        visitWord[1].insert(endWord);

        queue<string> que[2];
        que[0].push(beginWord);
        que[1].push(endWord);

        int res = 1;
        while (!que[0].empty() && !que[1].empty()) {
            ++res;
            if (findFinalWord(0, dirWord, visitWord, que)) return res;
            ++res;
            if (findFinalWord(1, dirWord, visitWord, que)) return res;
        }
        return 0;
    }
};

//官方使用双向bfs
// 并且引入虚拟边建虚拟节点。对于单词 hit，我们创建三个虚拟节点 *it、h*t、hi*，
// 并让 hit 向这三个虚拟节点分别连一条边即可。如果一个单词能够转化为 hit，
// 那么该单词必然会连接到这三个虚拟节点之一。对于每一个单词，我们枚举它连接到的虚拟节点，
// 把该单词对应的 id 与这些虚拟节点对应的 id 相连即可。

// 最后我们将起点加入队列开始广度优先搜索，当搜索到终点时，我们就找到了最短路径的长度。
// 注意因为添加了虚拟节点，所以我们得到的距离为实际最短路径长度的两倍。
// 同时我们并未计算起点对答案的贡献，所以我们应当返回距离的一半再加一的结果。
class Solution {
   public:
    unordered_map<string, int> wordId;
    vector<vector<int>> edge;
    int nodeNum = 0;
    void addWord(string &word) {
        if (!wordId.count(word)) {
            wordId[word] = nodeNum++;
            edge.emplace_back();
        }
    }

    void addEdge(string &word) {
        addWord(word);
        int id1 = wordId[word];
        for (char &it : word) {
            char tmp = it;
            it = '*';
            addWord(word);
            int id2 = wordId[word];
            edge[id1].push_back(id2);
            edge[id2].push_back(id1);
            it = tmp;
        }
    }

    int ladderLength(string beginWord, string endWord,
                     vector<string> &wordList) {
        for (string &word : wordList) {
            addEdge(word);
        }
        addEdge(beginWord);
        if (!wordId.count(endWord)) {
            return 0;
        }

        vector<int> disBegin(nodeNum, INT_MAX);
        int beginId = wordId[beginWord];
        disBegin[beginId] = 0;
        queue<int> queBegin;
        queBegin.push(beginId);

        vector<int> disEnd(nodeNum, INT_MAX);
        int endId = wordId[endWord];
        disEnd[endId] = 0;
        queue<int> queEnd;
        queEnd.push(endId);

        while (!queBegin.empty() && !queEnd.empty()) {
            int queBeginSize = queBegin.size();
            for (int i = 0; i < queBeginSize; ++i) {
                int nodeBegin = queBegin.front();
                queBegin.pop();
                if (disEnd[nodeBegin] != INT_MAX) {
                    return (disBegin[nodeBegin] + disEnd[nodeBegin]) / 2 + 1;
                }
                for (int &it : edge[nodeBegin]) {
                    if (disBegin[it] == INT_MAX) {
                        disBegin[it] = disBegin[nodeBegin] + 1;
                        queBegin.push(it);
                    }
                }
            }

            int queEndSize = queEnd.size();
            for (int i = 0; i < queEndSize; ++i) {
                int nodeEnd = queEnd.front();
                queEnd.pop();
                if (disBegin[nodeEnd] != INT_MAX) {
                    return (disBegin[nodeEnd] + disEnd[nodeEnd]) / 2 + 1;
                }
                for (int &it : edge[nodeEnd]) {
                    if (disEnd[it] == INT_MAX) {
                        disEnd[it] = disEnd[nodeEnd] + 1;
                        queEnd.push(it);
                    }
                }
            }
        }
        return 0;
    }
};