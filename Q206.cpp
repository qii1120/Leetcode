#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <string.h>
#include <set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* reverseList(ListNode* head) {
        if(!head) return nullptr;
        ListNode *cur=nullptr, *next = head->next;
        while(head->next!=nullptr)
        {
            head->next = cur;
            cur = head;
            head = next;
            next = head->next;
        }
        head->next = cur;
        return head;
}
int main()
{
    ListNode *head=new ListNode(0);
    for(int i=1; i<10; i++)
    {
        ListNode *tmp = new ListNode(i);
        ListNode *t = head;
        while(t && t->next) t = t->next;
        t->next = tmp;
    }
    ListNode *tmp = head;
    std::cout<<"tmp"<<endl;
    while(tmp)
    {
        std::cout<<tmp->val<<" ";
        tmp = tmp->next;
    }
    tmp = reverseList(head);
    cout<<tmp->next->val<<endl;
    std::cout<<"reversed"<<endl;
    for(int i=0; i<10; i++)
    {
        std::cout<<tmp->val<<" ";
        tmp = tmp->next;
    }
    std::cout<<endl;
    return 0;
}