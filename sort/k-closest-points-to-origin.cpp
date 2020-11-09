// 我们有一个由平面上的点组成的列表 points。需要从中找出 K 个距离原点 (0, 0)
// 最近的点。

// （这里，平面上两点之间的距离是欧几里德距离。）

// 你可以按任何顺序返回答案。除了点坐标的顺序之外，答案确保是唯一的。

//  

// 示例 1：

// 输入：points = [[1,3],[-2,2]], K = 1
// 输出：[[-2,2]]
// 解释：
// (1, 3) 和原点之间的距离为 sqrt(10)，
// (-2, 2) 和原点之间的距离为 sqrt(8)，
// 由于 sqrt(8) < sqrt(10)，(-2, 2) 离原点更近。
// 我们只需要距离原点最近的 K = 1 个点，所以答案就是 [[-2,2]]。
// 示例 2：

// 输入：points = [[3,3],[5,-1],[-2,4]], K = 2
// 输出：[[3,3],[-2,4]]
// （答案 [[-2,4],[3,3]] 也会被接受。）

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/k-closest-points-to-origin
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 方法一： 排序取出前K个；
// 时间复杂度：O(nlog n)
// 空间复杂度：O(logn)
class Solution {
   public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        sort(points.begin(), points.end(),
             [](const vector<int>& u, const vector<int>& v) {
                 return u[0] * u[0] + u[1] * u[1] < v[0] * v[0] + v[1] * v[1];
             });
        return {points.begin(), points.begin() + K};
    }
};

// 方法二：优先队列，大堆
// 时间复杂度：O(nlogK)
// 空间复杂度：O(K)
class Solution {
   public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        priority_queue<pair<int, int>> q;
        for (int i = 0; i < K; ++i) {
            q.emplace(points[i][0] * points[i][0] + points[i][1] * points[i][1],
                      i);
        }
        int n = points.size();
        for (int i = K; i < n; ++i) {
            int dist =
                points[i][0] * points[i][0] + points[i][1] * points[i][1];
            if (dist < q.top().first) {
                q.pop();
                q.emplace(dist, i);
            }
        }
        vector<vector<int>> ans;
        while (!q.empty()) {
            ans.push_back(points[q.top().second]);
            q.pop();
        }
        return ans;
    }
};

// 方法三： 快速选择（快速排序的思想）
// 时间复杂度：期望为 O(n)、最坏O(n^2)
// 空间复杂度：期望为 O(logn)，可以用循环替代，为O(1);
class Solution {
   private:
    mt19937 gen{random_device{}()};

   public:
    void random_select(vector<vector<int>>& points, int left, int right,
                       int K) {
        int pivot_id = uniform_int_distribution<int>{left, right}(gen);
        int pivot = points[pivot_id][0] * points[pivot_id][0] +
                    points[pivot_id][1] * points[pivot_id][1];
        swap(points[right], points[pivot_id]);
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            int dist =
                points[j][0] * points[j][0] + points[j][1] * points[j][1];
            if (dist <= pivot) {
                ++i;
                swap(points[i], points[j]);
            }
        }
        ++i;
        swap(points[i], points[right]);
        // [left, i-1] 都小于等于 pivot, [i+1, right] 都大于 pivot
        if (K < i - left + 1) {
            random_select(points, left, i - 1, K);
        } else if (K > i - left + 1) {
            random_select(points, i + 1, right, K - (i - left + 1));
        }
    }

    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        int n = points.size();
        random_select(points, 0, n - 1, K);
        return {points.begin(), points.begin() + K};
    }
};