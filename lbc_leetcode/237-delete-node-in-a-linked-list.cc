/*
题目大意：
删除链表中的一个节点。只给当前节点的指针。不够链表的头指针。

解题思路：
可以将本节点下个节点的值拷贝到本节点中，然后删除下一个节点。

遇到的问题：
一次通过。

再次阅读：
经典老题，没有问题。
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if(node == NULL)return;
        ListNode *next = node->next;
        node->next = next->next;
        node->val = next->val;
        delete next;
    }
};
/*
第二次做：
比较经典，还可以吧。
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        assert(node != NULL && node->next != NULL);

        auto del = node->next;
        node->val = del->val;
        node->next = del->next;
        delete del;
    }
};
/*
 * old and easy
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        swap(node->val, node->next->val);
        ListNode *next = node->next;
        node->next = next->next;
        delete next;
    }
};
