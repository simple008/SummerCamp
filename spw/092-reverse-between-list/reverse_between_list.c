#include <stdio.h>
#include <stdlib.h>

#define N 1000
/**
 ** Definition for singly-linked list.
 */

struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode *convert_to_list(int arr[], int n);
void free_list(struct ListNode *head);
void print_list(struct ListNode *head);

/**
 * Problem: resvese the nodes of an linked list whose position start from m and end of n
 * Solve: ues three pointer: pre, from, tail
 * Tips: handle tail carefully, more details see comments below
 */
struct ListNode* reverseBetween(struct ListNode* head, int m, int n) {

	struct ListNode* from = head;
	struct ListNode* pre = head;

	int m1 = m;
	while (--m1) {
		pre = from;
		from = from->next;
	}

	struct ListNode *tail = from;
	int t = n - m;
	// variable 'tail' points to the next of the node of position 'n'
	// if we let it point to node 'n', the tail->next will change
	while (t-- >= 0) {
		tail = tail->next;
	}

	struct ListNode *temp = from->next;
	from->next = tail;
	while (temp != tail) {
		struct ListNode* now = temp;
		temp = temp->next;

		now->next = from;
		from = now;
	}

	if (m > 1) {
		pre->next = from;
		return head;
	} else {
		return from;
	}
}

int main()
{
	int n, a, b;
	int arr[N];
	while (~scanf("%d %d %d", &n, &a, &b)) {
		int i;
		for (i = 0; i < n; ++i) {
			scanf("%d", &arr[i]);
		}

		struct ListNode * head = convert_to_list(arr, n);
		print_list(head);
		head = reverseBetween(head, a, b);
		print_list(head);
		free_list(head);
	}
}

struct ListNode *convert_to_list(int arr[], int n)
{
	int i;

	struct ListNode *head = malloc(sizeof(struct ListNode));
	head->next = NULL;
	struct ListNode *tail = head;

	for (i = 0; i < n; ++i) {
		struct ListNode *temp = malloc(sizeof(struct ListNode));
		temp->val = arr[i];
		temp->next = NULL;

		tail->next = temp;
		tail = tail->next;
	}

	tail = head;
	head = head->next;
	free(tail);

	return head;
}

void free_list(struct ListNode *head)
{
	while (head) {
		struct ListNode* now = head;
		head = head->next;
		free(now);
	}
}
void print_list(struct ListNode *head)
{
	while (head) {
		printf("%d->", head->val);
		head = head->next;
	}
	printf("NULL\n");
}


ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode h(0);
        h.next = head;

        ListNode *it = &h;
        n = n - m + 1;
        while (--m) it = it->next;

        ListNode *left = it, *th = NULL, *right = it->next;
        it = it->next;
        while (n--) {
            ListNode *tmp = it;
            it = it->next;

            tmp->next = th;
            th = tmp;
        }

        left->next = th;
        right->next = it;

        return h.next;
    }
