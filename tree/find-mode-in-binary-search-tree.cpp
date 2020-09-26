// �����������������������¼��һ��ֵ������
// 501. �����������е�����
// ����һ������ֵͬ�Ķ�����������BST�����ҳ� BST
// �е���������������Ƶ����ߵ�Ԫ�أ���

// �ٶ� BST �����¶��壺

// �������������������ֵС�ڵ��ڵ�ǰ����ֵ
// �������������������ֵ���ڵ��ڵ�ǰ����ֵ
// �����������������Ƕ���������
// ���磺
// ���� BST [1,null,2,2],

//    1
//     \
//      2
//     /
//    2
// ����[2].

// ��ʾ�������������1�������迼�����˳��

// ���ף�����Բ�ʹ�ö���Ŀռ��𣿣������ɵݹ��������ʽ����ջ�Ŀ��������������ڣ�

// ��Դ�����ۣ�LeetCode��
// ���ӣ�https://leetcode-cn.com/problems/find-mode-in-binary-search-tree
// ����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������

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