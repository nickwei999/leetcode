// 二叉搜索树，中序遍历，记录上一个值，众数
// 501. 二叉搜索树中的众数
// 给定一个有相同值的二叉搜索树（BST），找出 BST
// 中的所有众数（出现频率最高的元素）。

// 假定 BST 有如下定义：

// 结点左子树中所含结点的值小于等于当前结点的值
// 结点右子树中所含结点的值大于等于当前结点的值
// 左子树和右子树都是二叉搜索树
// 例如：
// 给定 BST [1,null,2,2],

//    1
//     \
//      2
//     /
//    2
// 返回[2].

// 提示：如果众数超过1个，不需考虑输出顺序

// 进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内）

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/find-mode-in-binary-search-tree
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
  int tmpMaxCnt;
  int maxCnt;
  bool isInit;

 public:
  void findModeInner(TreeNode *node, int &lastVal, vector<int> &res) {
    if (node == nullptr) {
      return;
    }
    findModeInner(node->left, lastVal, res);

    if (isInit) {
      tmpMaxCnt = (lastVal == node->val) ? (tmpMaxCnt + 1) : 1;
    } else {
      isInit = true;
      tmpMaxCnt = 1;
    }

    lastVal = node->val;
    if (tmpMaxCnt > maxCnt) {
      maxCnt = tmpMaxCnt;
      res.clear();
      res.push_back(node->val);
    } else if (tmpMaxCnt == maxCnt) {
      res.push_back(node->val);
    }

    findModeInner(node->right, lastVal, res);
  }

  vector<int> findMode(TreeNode *root) {
    vector<int> res;
    isInit = false;
    tmpMaxCnt = 0;
    maxCnt = 0;
    int last = 0;
    findModeInner(root, last, res);
    return res;
  }
};