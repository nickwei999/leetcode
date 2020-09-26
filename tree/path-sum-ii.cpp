// 遍历+回溯,时间复杂度O(n^2);
// 时间复杂度：O(N^2)O(N
// 2
//  )，其中 NN
//  是树的节点数。在最坏情况下，树的上半部分为链状，下半部分为完全二叉树，并且从根节点到每一个叶子节点的路径都符合题目要求。此时，路径的数目为
//  O(N)O(N)，并且每一条路径的节点个数也为
//  O(N)O(N)，因此要将这些路径全部添加进答案中，时间复杂度为 O(N^2)O(N
// 2
//  )。

// 空间复杂度：O(N)O(N)，其中 NN
// 是树的节点数。空间复杂度主要取决于栈空间的开销，栈中的元素个数不会超过树的节点数。

// path-sum-ii
// 给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。

// 说明: 叶子节点是指没有子节点的节点。

// 示例:
// 给定如下二叉树，以及目标和 sum = 22，

//               5
//              / \
//             4   8
//            /   / \
//           11  13  4
//          /  \    / \
//         7    2  5   1
// 返回:

// [
//    [5,4,11,2],
//    [5,8,4,5]
// ]

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/path-sum-ii
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
 public:
  void pathSumInner(TreeNode *node, int &sum, vector<int> &tmpRes,
                    vector<vector<int>> &res) {
    if (node == nullptr) {
      return;
    }
    sum -= node->val;
    tmpRes.push_back(node->val);

    if (node->left == nullptr && node->right == nullptr && sum == 0) {
      res.push_back(tmpRes);
    }
    pathSumInner(node->left, sum, tmpRes, res);
    pathSumInner(node->right, sum, tmpRes, res);

    sum += node->val;
    tmpRes.pop_back();
  }
  vector<vector<int>> pathSum(TreeNode *root, int sum) {
    vector<vector<int>> res;
    vector<int> tmpRes;
    pathSumInner(root, sum, tmpRes, res);
    return res;
  }
};