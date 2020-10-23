// 给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
// 将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…

// 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

// 示例 1:

// 给定链表 1->2->3->4, 重新排列为 1->4->2->3.
// 示例 2:

// 给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/reorder-list
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// 方法一：
// 递归返回时，将尾部个节点，穿插到头部，并移动头指针；
// 方法二：
// 找到链表中间节点并翻转后半部分；
// 将前半部分和后半部分， 穿插链接；

class Solution {
   public:
    ListNode *head;
    bool finished;
    void reorderListInner(ListNode *pre, ListNode *node) {
        if (!node) {
            return;
        }

        reorderListInner(node, node->next);
        if (pre == head || node == head) {
            finished = true;
        }
        if (finished) {
            return;
        }

        node->next = head->next;
        head->next = node;
        pre->next = nullptr;
        if (head->next) {
            head = head->next->next;
        }
    }
    void reorderList(ListNode *headIn) {
        auto dummyHead = new ListNode(0, headIn);
        head = headIn;
        finished = false;
        reorderListInner(dummyHead, headIn);
        delete dummyHead;
    }
};
//====================方法二=============
ListNode *findMidNode(ListNode *head) {
    auto slow = head;
    auto fast = head ? head->next : nullptr;
    while (fast) {
        fast = fast->next;
        if (!fast) {
            break;
        }
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

ListNode *reverseList(ListNode *node) {
    if (!node || !node->next) {
        return node;
    }
    auto head = reverseList(node->next);
    node->next->next = node;
    node->next = nullptr;
    return head;
}
void printList(ListNode *node) {
    while (node) {
        cout << node->val << "->";
    }
    cout << endl;
}
void reorderList(ListNode *headIn) {
    auto head = headIn;
    auto midNode = findMidNode(headIn);
    midNode = revserseList(midNode);

    while (midNode && head && (head != midNode)) {
        auto tmp = midNode->next;
        midNode->next = head->next;
        head->next = midNode;

        head = head->next->next;
        midNode = tmp;
    }
}