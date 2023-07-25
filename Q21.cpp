#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    if (!list1 && !list2)
        return nullptr;
    else if (!list1)
        return list2;
    else if (!list2)
        return list1;
    ListNode *list = list1->val <= list2->val ? list1 : list2, *head = list;
    if (list1->val <= list2->val)
        list1 = list1->next;
    else
        list2 = list2->next;
    while (list != nullptr)
    {
        if (!list1 && list2)
        {
            list->next = list2;
            break;
        }
        else if (!list2 && list1)
        {
            list->next = list1;
            break;
        }
        if (list1->val > list2->val)
        {
            list->next = list2;
            list2 = list2->next;
        }
        else
        {
            list->next = list1;
            list1 = list1->next;
        }
        list = list->next;
    }
    return head;
}

int main()
{
    ListNode *node13 = new ListNode(4);
    ListNode *node12 = new ListNode(2, node13);
    ListNode *node11 = new ListNode(1, node12);
    ListNode *node24 = new ListNode(1);
    ListNode *node23 = new ListNode(4);
    ListNode *node22 = new ListNode(3, node23);
    ListNode *node21 = new ListNode(1, node22);
    ListNode *list = mergeTwoLists(node23, node24);
    while (list)
    {
        cout << list->val << endl;
        list = list->next;
    }
    return 0;
}