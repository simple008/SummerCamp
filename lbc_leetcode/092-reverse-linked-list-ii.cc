/*
题目大意：
给定一链表。翻转其中m到n的一段。

解题思路：
找到这一段，翻转。

遇到的问题：
一次通过。

再次阅读：
这次看到这个题目的时候，第一个想法就是用这种原地的处理链表的方式来处理的。
看来读代码读多了还是有好处的啊。
我大概脑补了一下代码：但是感觉还是没有人家写的好：
 ListNode *reverseBetween(ListNode *head, int m, int n) {
    if(m==n)return head;
    n-=m;
    ListNode prehead(0);
    prehead.next=head;
    ListNode* pre=&prehead;
    while(--m)pre=pre->next;
    ListNode* pstart=pre->next;
    while(n--)
    {
        ListNode *p=pstart->next;
        pstart->next=p->next;
        p->next=pre->next;
        pre->next=p;
    }
    return prehead.next;
}
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *last = NULL;
        ListNode *left = NULL, *right = NULL;
        ListNode *next = NULL;
        left = head;
        for(int i = 0; i < m-1; ++i){
            last = left;
            left = left->next;
        }
        right = left;
        for(int i = 0; i < n-m; ++i){
            right = right->next;
        }
        next = right->next;
        right->next = NULL;
        left = reverse(left);
        if(last == NULL){
            head = left;
        }else{
            last->next = left;
        }
        while(left->next != NULL){
            left = left->next;
        }
        left->next = next;
        return head;
    }

    ListNode *reverse(ListNode *head){
        ListNode *cur = head;
        ListNode *last = NULL;
        while(cur != NULL){
            ListNode *tmp = cur->next;
            cur->next = last;
            last = cur;
            cur = tmp;
        }
        return last;
    }
};
/*
第二次做：
比较顺利，只是其中一个变量写错了。
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
private:
    ListNode *reverse(ListNode *head) {
        ListNode *ret = NULL;
        while (head) {
            ListNode *next = head->next;
            head->next = ret;
            ret = head;
            head = next;
        }
        return ret;
    }

public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (head == NULL || m == n) return head;

        ListNode prehead(0), *phead = &prehead, *leftTail, *midHead, *midTail;

        phead->next = head;
        for (int i = 0; i < m; ++i) {
            leftTail = phead;
            phead = phead->next;
        }

        midHead = phead;
        for (int i = 0; i < n-m+1; ++i) {
            midTail = phead;
            phead = phead->next;
        }

        midTail->next = NULL;
        reverse(midHead);
        leftTail->next = midTail;
        midHead->next = phead;

        return prehead.next;
    }
};
/*
 * just so so
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
private:
    ListNode * reverse(ListNode *head) {
        ListNode *ret = NULL;
        while (head) {
            ListNode *next = head->next;
            head->next = ret;
            ret = head;
            head = next;
        }
        return ret;
    }

public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode tmp(0), *pre = &tmp;
        pre->next = head;

        for (int i = 1; i < m; ++i) pre = pre->next;
        ListNode *last = pre;
        for (int i = 0; i <= n-m; ++i) pre = pre->next;

        head = pre;
        pre = pre->next;
        head->next = NULL;

        head = last->next;
        last->next = reverse(last->next);
        head->next = pre;

        return tmp.next;
    }
};
