// 给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

// struct Node {
//   int val;
//   Node *left;
//   Node *right;
//   Node *next;
// }
// 填充它的每个 next
// 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next
// 指针设置为 NULL。

// 初始状态下，所有 next 指针都被设置为 NULL。

//  

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
// 方法一：BFS层次遍历；
// 方法二：
// 0、本层已经建立好链接，需要给下一层建立链接；
// 1、本层每个节点直接给对应的左右节点建立链接； node->left->next = node->right;
// 2、根据本层的最左侧作为链表头head； head->right->next = head->next ?
// head->next->left : nullptr;

class Solution {
 public:
  Node* connect(Node* root) {
    auto leftMost = root;
    while (leftMost) {
      auto head = leftMost;
      while (head && head->left) {
        head->left->next = head->right;
        head->right->next = head->next ? head->next->left : nullptr;
        head = head->next;
      }
      leftMost = leftMost->left;
    }
    return root;
  }
};