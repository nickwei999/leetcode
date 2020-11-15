// 给定一个以字符串表示的非负整数 num，移除这个数中的 k
// 位数字，使得剩下的数字最小。

// 注意:

// num 的长度小于 10002 且 ≥ k。
// num 不会包含任何前导零。
// 示例 1 :

// 输入: num = "1432219", k = 3
// 输出: "1219"
// 解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。
// 示例 2 :

// 输入: num = "10200", k = 1
// 输出: "200"
// 解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。
// 示例 3 :

// 输入: num = "10", k = 2
// 输出: "0"
// 解释: 从原数字移除所有的数字，剩余为空就是0。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/remove-k-digits
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 解法：
// 对于两个相同长度的数字序列，最左边不同的数字决定了这两个数字的大小，例如，
// 对于 A = 1axxxA，B = 1bxxxB，如果 a > ba>b 则 A > BA>B。
// 基于此，我们可以知道，若要使得剩下的数字最小，需要保证靠前的数字尽可能小。
// 如425删除一位，4比2大，所以删除4；
// 总结删除一个字符的贪心策略：
// 给定一个长度为 n 的数字序列 [D0 ... Dn-1],从左往右找到第一个位置 i（i>0）使得
// Di < Di-1
//  删除Di；如果不存在，说明整个数字序列单调不降，删去最后一个数字即可。

// 可使用单调栈：
// 对于每个数字，如果该数字小于栈顶元素，我们就不断地弹出栈顶元素，直到：
// 栈为空
// 或者新的栈顶元素不大于当前数字
// 或者我们已经删除了 kk 位数字

// 时间复杂度为O(n)
class Solution {
   public:
    string removeKdigits(string num, int k) {
        vector<char> stk;
        for (auto& digit : num) {
            while (stk.size() > 0 && stk.back() > digit && k) {
                stk.pop_back();
                k -= 1;
            }
            stk.push_back(digit);
        }

        for (; k > 0; --k) {
            stk.pop_back();
        }

        string ans = "";
        bool isLeadingZero = true;
        for (auto& digit : stk) {
            if (isLeadingZero && digit == '0') {
                continue;
            }
            isLeadingZero = false;
            ans += digit;
        }
        return ans == "" ? "0" : ans;
    }
};
