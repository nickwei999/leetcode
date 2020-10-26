// 我们把数组 A 中符合下列属性的任意连续子数组 B 称为 “山脉”：

// B.length >= 3
// 存在 0 < i < B.length - 1 使得 B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ...
// > B[B.length - 1] （注意：B 可以是 A 的任意子数组，包括整个数组 A。）

// 给出一个整数数组 A，返回最长 “山脉” 的长度。

// 如果不含有 “山脉” 则返回 0。

//  

// 示例 1：

// 输入：[2,1,4,7,3,2,5]
// 输出：5
// 解释：最长的 “山脉” 是 [1,4,7,3,2]，长度为 5。
// 示例 2：

// 输入：[2,2,2]
// 输出：0
// 解释：不含 “山脉”。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/longest-mountain-in-array
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

//动态规划，left表示以自己为顶点，左边的上升长度；right表示以自己为顶点下降的长度；
class Solution {
   public:
    int longestMountain(vector<int>& A) {
        int res = 0;
        vector<int> left(A.size(), 0);
        vector<int> right(A.size(), 0);
        for (int i = 1; i < A.size(); ++i) {
            left[i] = A[i] > A[i - 1] ? (left[i - 1] + 1) : 0;
        }
        for (int i = A.size() - 1; i - 1 >= 0; --i) {
            right[i - 1] = A[i - 1] > A[i] ? (right[i] + 1) : 0;
        }
        for (int i = 0; i < A.size(); ++i) {
            if (left[i] > 0 && right[i] > 0)
                res = max(res, left[i] + right[i] + 1);
        }
        return res;
    }
};

// 方法二：
// 双指针，枚举山脚；
// 我们也可以枚举山脚。例如当我们从左向右遍历整个数组 AA
// 时，可以使用双指针的方法，一个指针枚举左侧山脚，另一个指针不断向右移动到右侧山脚。

// 具体地，我们使用指针 \textit{left}left 指向左侧山脚，它的初始值为
// 00。每次当我们固定 \textit{left}left 时：

// 我们首先需要保证 \textit{left} + 2 < nleft+2<n，这是因为山脉的长度至少为
// 33；其次我们需要保证 A[\textit{left}] < A[\textit{left} +
// 1]A[left]<A[left+1]，否则 \textit{left}left 对应的不可能时左侧山脚；

// 我们将右侧山脚的 \textit{right}right 的初始值置为
// \textit{left}+1left+1，随后不断地向右移动 \textit{right}right，直到不满足
// A[\textit{right}] < A[\textit{right} + 1]A[right]<A[right+1] 为止，此时：

// 如果 \textit{right} =
// n-1right=n−1，说明我们已经移动到了数组末尾，已经无法形成山脉了；

// 否则，\textit{right}right 指向的可能是山顶。我们需要额外判断是有满足
// A[\textit{right}] > A[\textit{right} +
// 1]A[right]>A[right+1]，这是因为如果两者相等，那么 \textit{right}right
// 指向的就不是山顶了。

// 如果 \textit{right}right
// 指向的确实是山顶，那么我们使用类似的方法，不断地向右移动
// \textit{right}right，直到不满足 A[\textit{right}] > A[\textit{right} +
// 1]A[right]>A[right+1] 为止，此时，\textit{right}right
// 指向右侧山脚，A[\textit{left}]A[left] 到 A[\textit{right}]A[right]
// 就对应着一座山脉；

// 需要注意的是，右侧山脚有可能是下一个左侧山脚，因此我们需要将
// \textit{right}right 的值赋予
// \textit{left}left，以便与进行下一次枚举。在其它所有不满足要求的情况下，\textit{right}right
// 对应的位置都不可能是下一个左侧山脚，因此可以将 \textit{right} + 1right+1
// 的值赋予 \textit{left}left。

// 在下面的代码中，当不满足要求时，我们立即将 \textit{right}right 的值加
// 11。这样一来，我们就可以统一在下一次枚举左侧山脚之前，将 \textit{right}right
// 的值赋予 \textit{left}left 了。

class Solution {
   public:
    int longestMountain(vector<int>& A) {
        int n = A.size();
        int ans = 0;
        int left = 0;
        while (left + 2 < n) {
            int right = left + 1;
            if (A[left] < A[left + 1]) {
                while (right + 1 < n && A[right] < A[right + 1]) {
                    ++right;
                }
                if (right < n - 1 && A[right] > A[right + 1]) {
                    while (right + 1 < n && A[right] > A[right + 1]) {
                        ++right;
                    }
                    ans = max(ans, right - left + 1);
                } else {
                    ++right;
                }
            }
            left = right;
        }
        return ans;
    }
};
