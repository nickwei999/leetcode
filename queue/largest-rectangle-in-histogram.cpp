/*
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1
。

    求在该柱状图中，能够勾勒出来的矩形的最大面积。

    以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高度为 [2, 1, 5, 6, 2,
3]。

    图中阴影部分为所能勾勒出的最大矩形面积，其面积为 10 个单位。

    示例 :

    输入 : [ 2, 1, 5, 6, 2, 3 ] 输出 : 10 */

// 方法一；
// 暴力 O(N^2)复杂度

/* 方法二：
使用单调栈：
针对每个i，找出右边比自己小的柱子，即这个柱子最大向右延伸的距离：r
针对每个i从右往左找出，比自己小的柱子，即这个柱子可以向左延伸的距离： l
包括这个柱子的矩形面积即： heights[i] * (l+r);
时间复杂度： O(2N) */
class Solution {
   public:
    int largestRectangleArea(vector<int> &heights) {
        stack<int> st;
        int n = heights.size();
        vector<int> smallIdx(n);  //保存右边第一比自己小的柱子索引
        for (int i = 0; i < n; ++i) {
            if (st.empty() || heights[i] >= heights[st.top()]) {
                st.push(i);
                continue;
            }
            while (!st.empty() && heights[i] < heights[st.top()]) {
                smallIdx[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }

        while (!st.empty()) {
            smallIdx[st.top()] = n;
            st.pop();
        }

        int res = 0;
        //计算左边矩形
        for (int i = n - 1; i >= 0; --i) {
            if (st.empty() || heights[i] >= heights[st.top()]) {
                st.push(i);
                continue;
            }
            while (!st.empty() && heights[i] < heights[st.top()]) {
                auto &h = heights[st.top()];
                int width = smallIdx[st.top()] - i - 1;
                res = max(res, width * h);
                st.pop();
            }
            st.push(i);
        }

        while (!st.empty()) {
            auto &h = heights[st.top()];
            int width = smallIdx[st.top()];
            res = max(res, width * h);
            st.pop();
        }

        return res;
    }
};
