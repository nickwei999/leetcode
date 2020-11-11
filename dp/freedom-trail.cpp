// 电子游戏“辐射4”中，任务“通向自由”要求玩家到达名为“Freedom Trail
// Ring”的金属表盘，并使用表盘拼写特定关键词才能开门。

// 给定一个字符串 ring，表示刻在外环上的编码；给定另一个字符串 key，表示需要拼写的关键词。您需要算出能够拼写关键词中所有字符的最少步数。

// 最初，ring 的第一个字符与12:00方向对齐。您需要顺时针或逆时针旋转 ring
// 以使 key 的一个字符在 12:00
// 方向对齐，然后按下中心按钮，以此逐个拼写完 key 中的所有字符。

// 旋转 ring 拼出 key 字符 key[i] 的阶段中：

// 您可以将 ring 顺时针或逆时针旋转一个位置，计为1步。旋转的最终目的是将字符串 ring 的一个字符与
// 12:00 方向对齐，并且这个字符必须等于字符 key[i] 。
// 如果字符 key[i] 已经对齐到12:00方向，您需要按下中心按钮进行拼写，这也将算作 1
// 步。按完之后，您可以开始拼写 key 的下一个字符（下一阶段）, 直至完成所有拼写。
//  
// 输入: ring = "godding", key = "gd"
// 输出: 4
// 解释:
//  对于 key 的第一个字符 'g'，已经在正确的位置, 我们只需要1步来拼写这个字符。
//  对于 key 的第二个字符 'd'，我们需要逆时针旋转 ring "godding" 2步使它变成
//  "ddinggo"。 当然, 我们还需要1步进行拼写。 因此最终的输出是 4。
// 提示：

// ring 和 key 的字符串长度取值范围均为 1 至 100；
// 两个字符串中都只有小写字符，并且均可能存在重复字符；
// 字符串 key 一定可以由字符串 ring 旋转拼出。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/freedom-trail
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// dp[i][j]
// 表示完成key[i]字符时，对应ring中位置为j指向12点时，需要使用的最少步数；
// 那么 dp[i][j] = dp[i-1][k] + getMinStep(j,k);  k:  for each Pos in ring
// 表是 dp[i][j]是从上一个十二点的位置k转移来的；
// 最终结果是:min{dp[i][j]} ; j: for each Pos in ring

// 复杂度分析：
// 有key.size()个子问题；
// 每个子问题，j的位置最多有ring.size()个，k的位置最多有ring.size()个
// 所以是O(n*m*m)

class Solution {
   public:
    int getMinStep(int jpos, int lastKPos, const string &ring) {
        return min(abs(jpos - lastKPos),
                   (int)ring.size() - abs(jpos - lastKPos));
    }
    int findRotateSteps(string ring, string key) {
        // dp[i][j]
        // 表示完成key[i]时，ring对应位置为j指向12点，需要使用的最少步数；
        vector<vector<int>> dp(key.size(), vector<int>(ring.size(), INT_MAX));
        // ring中每个字符对应的idx，用于计算旋转的移位
        vector<vector<int>> ringCharPos(256);
        for (int i = 0; i < ring.size(); ++i) {
            ringCharPos[ring[i]].push_back(i);
        }
        // start status
        for (auto &jpos : ringCharPos[key[0]]) {
            dp[0][jpos] = getMinStep(jpos, 0, ring);
        }

        for (int i = 1; i < key.size(); ++i) {
            // for each jcharPos in ring
            for (auto &jpos : ringCharPos[key[i]]) {
                for (auto &lastkpos : ringCharPos[key[i - 1]]) {
                    dp[i][jpos] =
                        min(dp[i][jpos], dp[i - 1][lastkpos] +
                                             getMinStep(jpos, lastkpos, ring));
                }
            }
        }

        return *min_element(dp.back().begin(), dp.back().end()) + key.size();
    }
};
