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
    bool findFinaltWord(const string &endWord,
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
                if (findFinaltWord(endWord, dirWord, que)) {
                    return res;
                }
            }
        }
        return 0;
    }
};