// 常数空间遍历二叉树

// 我们在中序遍历的时候，一定先遍历左子树，然后遍历当前节点，最后遍历右子树。在常规方法中，我们用递归回溯或者是栈来保证遍历完左子树可以再回到当前节点，但这需要我们付出额外的空间代价。我们需要用一种巧妙地方法可以在
// O(1)O(1)
// 的空间下，遍历完左子树可以再回到当前节点。我们希望当前的节点在遍历完当前点的前驱之后被遍历，我们可以考虑修改它的前驱节点的
// \rm rightright 指针。当前节点的前驱节点的 \rm rightright
// 指针可能本来就指向当前节点（前驱是当前节点的父节点），也可能是当前节点左子树最右下的节点。如果是后者，我们希望遍历完这个前驱节点之后再回到当前节点，可以将它的
// \rm rightright 指针指向当前节点。

// Morris 中序遍历的一个重要步骤就是寻找当前节点的前驱节点，并且 Morris
// 中序遍历寻找下一个点始终是通过转移到 \rm rightright 指针指向的位置来完成的。

// 如果当前节点没有左子树，则遍历这个点，然后跳转到当前节点的右子树。
// 如果当前节点有左子树，那么它的前驱节点一定在左子树上，我们可以在左子树上一直向右行走，找到当前点的前驱节点。
// 如果前驱节点没有右子树，就将前驱节点的 \rm rightright
// 指针指向当前节点。这一步是为了在遍历完前驱节点后能找到前驱节点的后继，也就是当前节点。
// 如果前驱节点的右子树为当前节点，说明前驱节点已经被遍历过并被修改了 \rm
// rightright
// 指针，这个时候我们重新将前驱的右孩子设置为空，遍历当前的点，然后跳转到当前节点的右子树。
// 因此我们可以得到这样的代码框架：

// 作者：LeetCode-Solution
// 链接：https://leetcode-cn.com/problems/find-mode-in-binary-search-tree/solution/er-cha-sou-suo-shu-zhong-de-zhong-shu-by-leetcode-/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

TreeNode *cur = root, *pre = nullptr;
while (cur) {
  if (cur->left == nullptr) {
    // 遍历cur
    cur = cur->right;
    continue;
  }
  pre = cur->left;
  while (pre->right && pre->right != cur) {
    pre = pre->left;
  }

  if (pre->right == nullptr) {
    pre->right = cur;
    cur = cur->left;
  } else {
    pre->right = nullptr;
    //遍历cur
    cur = cur->right;
  }
}

// https://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html
void inorderMorrisTraversal(TreeNode *root) {
  TreeNode *cur = root, *prev = NULL;
  while (cur != NULL) {
    if (cur->left == NULL)  // 1.
    {
      printf("%d ", cur->val);
      cur = cur->right;
    } else {
      // find predecessor
      prev = cur->left;
      while (prev->right != NULL && prev->right != cur) prev = prev->right;

      if (prev->right == NULL)  // 2.a)
      {
        prev->right = cur;
        cur = cur->left;
      } else  // 2.b)
      {
        prev->right = NULL;
        printf("%d ", cur->val);
        cur = cur->right;
      }
    }
  }
}

void preorderMorrisTraversal(TreeNode *root) {
  TreeNode *cur = root, *prev = NULL;
  while (cur != NULL) {
    if (cur->left == NULL) {
      printf("%d ", cur->val);
      cur = cur->right;
    } else {
      prev = cur->left;
      while (prev->right != NULL && prev->right != cur) prev = prev->right;

      if (prev->right == NULL) {
        printf("%d ", cur->val);  // the only difference with inorder-traversal
        prev->right = cur;
        cur = cur->left;
      } else {
        prev->right = NULL;
        cur = cur->right;
      }
    }
  }
}

void reverse(TreeNode *from,
             TreeNode *to)  // reverse the tree nodes 'from' -> 'to'.
{
  if (from == to) return;
  TreeNode *x = from, *y = from->right, *z;
  while (true) {
    z = y->right;
    y->right = x;
    x = y;
    y = z;
    if (x == to) break;
  }
}

void printReverse(
    TreeNode *from,
    TreeNode *to)  // print the reversed tree nodes 'from' -> 'to'.
{
  reverse(from, to);

  TreeNode *p = to;
  while (true) {
    printf("%d ", p->val);
    if (p == from) break;
    p = p->right;
  }

  reverse(to, from);
}

void postorderMorrisTraversal(TreeNode *root) {
  TreeNode dump(0);
  dump.left = root;
  TreeNode *cur = &dump, *prev = NULL;
  while (cur) {
    if (cur->left == NULL) {
      cur = cur->right;
    } else {
      prev = cur->left;
      while (prev->right != NULL && prev->right != cur) prev = prev->right;

      if (prev->right == NULL) {
        prev->right = cur;
        cur = cur->left;
      } else {
        printReverse(cur->left, prev);  // call print
        prev->right = NULL;
        cur = cur->right;
      }
    }
  }
}