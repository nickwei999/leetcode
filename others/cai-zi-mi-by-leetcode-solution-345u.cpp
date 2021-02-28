/* 外国友人仿照中国字谜设计了一个英文版猜字谜小游戏，请你来猜猜看吧。

字谜的迷面 puzzle
按字符串形式给出，如果一个单词 word 符合下面两个条件，那么它就可以算作谜底：

单词 word 中包含谜面 puzzle 的第一个字母。
单词 word 中的每一个字母都可以在谜面 puzzle 中找到。
例如，如果字谜的谜面是 "abcdefg"，那么可以作为谜底的单词有 "faced", "cabbage",
和 "baggage"；而 "beefed"（不含字母 "a"）以及 "based"（其中的 "s"
没有出现在谜面中）都不能作为谜底。
返回一个答案数组 answer，数组中的每个元素 answer[i] 是在给出的单词列表 words
中可以作为字谜迷面 puzzles[i] 所对应的谜底的单词数目。

 

示例：

输入：
words = ["aaaa","asas","able","ability","actt","actor","access"],
puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
输出：[1,1,3,2,4,0]
解释：
1 个单词可以作为 "aboveyz" 的谜底 : "aaaa"
1 个单词可以作为 "abrodyz" 的谜底 : "aaaa"
3 个单词可以作为 "abslute" 的谜底 : "aaaa", "asas", "able"
2 个单词可以作为 "absoryz" 的谜底 : "aaaa", "asas"
4 个单词可以作为 "actresz" 的谜底 : "aaaa", "asas", "actt", "access"
没有单词可以作为 "gaswxyz" 的谜底，因为列表中的单词都不含字母 'g'。
 

提示：

1 <= words.length <= 10^5
4 <= words[i].length <= 50
1 <= puzzles.length <= 10^4
puzzles[i].length == 7
words[i][j], puzzles[i][j] 都是小写英文字母。
每个 puzzles[i] 所包含的字符都不重复。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-valid-words-for-each-puzzle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/* 方法一：使用状态压缩；
将每个word转成二进制，比用map维护二进制的数量；
枚举puzzle,除第一个字符外的子集；
如果一个子集与第一个字符，在map中有计数cnt,那么该puzzle对应的个数需要加上cnt；
*/

class Solution {
   public:
    vector<int> findNumOfValidWords(vector<string>& words,
                                    vector<string>& puzzles) {
        unordered_map<int, int> frequency;

        for (const string& word : words) {
            int mask = 0;
            for (char ch : word) {
                mask |= (1 << (ch - 'a'));
            }
            if (__builtin_popcount(mask) <= 7) {
                ++frequency[mask];
            }
        }

        vector<int> ans;
        for (const string& puzzle : puzzles) {
            int total = 0;

            // 枚举子集方法一
            // for (int choose = 0; choose < (1 << 6); ++choose) {
            //     int mask = 0;
            //     for (int i = 0; i < 6; ++i) {
            //         if (choose & (1 << i)) {
            //             mask |= (1 << (puzzle[i + 1] - 'a'));
            //         }
            //     }
            //     mask |= (1 << (puzzle[0] - 'a'));
            //     if (frequency.count(mask)) {
            //         total += frequency[mask];
            //     }
            // }

            // 枚举子集方法二
            int mask = 0;
            for (int i = 1; i < 7; ++i) {
                mask |= (1 << (puzzle[i] - 'a'));
            }
            int subset = mask;
            do {
                int s = subset | (1 << (puzzle[0] - 'a'));
                if (frequency.count(s)) {
                    total += frequency[s];
                }
                subset = (subset - 1) & mask;
            } while (subset != mask);

            ans.push_back(total);
        }
        return ans;
    }
};

// 方法二：字典树
struct TrieNode {
    int frequency = 0;
    TrieNode* child[26];

    TrieNode() {
        for (int i = 0; i < 26; ++i) {
            child[i] = nullptr;
        }
    }
};

class Solution {
   private:
    TrieNode* root;

   public:
    vector<int> findNumOfValidWords(vector<string>& words,
                                    vector<string>& puzzles) {
        root = new TrieNode();

        auto add = [&](const string& word) {
            TrieNode* cur = root;
            for (char ch : word) {
                if (!cur->child[ch - 'a']) {
                    cur->child[ch - 'a'] = new TrieNode();
                }
                cur = cur->child[ch - 'a'];
            }
            ++cur->frequency;
        };

        // 在回溯的过程中枚举 puzzle 的所有子集并统计答案
        // find(puzzle, required, cur, pos) 表示 puzzle 的首字母为 required,
        //  当前搜索到字典树上的 cur 节点，并且准备枚举 puzzle 的第 pos
        //  个字母是否选择（放入子集中）
        // find 函数的返回值即为谜底的数量
        function<int(const string&, char, TrieNode*, int)> find =
            [&](const string& puzzle, char required, TrieNode* cur, int pos) {
                // 搜索到空节点，不合法，返回 0
                if (!cur) {
                    return 0;
                }
                // 整个 puzzle 搜索完毕，返回谜底的数量
                if (pos == 7) {
                    return cur->frequency;
                }

                // 选择第 pos 个字母
                int ret = find(puzzle, required, cur->child[puzzle[pos] - 'a'],
                               pos + 1);

                // 当 puzzle[pos] 不为首字母时，可以不选择第 pos 个字母
                if (puzzle[pos] != required) {
                    ret += find(puzzle, required, cur, pos + 1);
                }

                return ret;
            };

        for (string word : words) {
            // 将 word 中的字母按照字典序排序并去重
            sort(word.begin(), word.end());
            word.erase(unique(word.begin(), word.end()), word.end());
            // 加入字典树中
            add(word);
        }

        vector<int> ans;
        for (string puzzle : puzzles) {
            char required = puzzle[0];
            sort(puzzle.begin(), puzzle.end());
            ans.push_back(find(puzzle, required, root, 0));
        }
        return ans;
    }
};
