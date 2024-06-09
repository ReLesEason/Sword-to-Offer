/***********************************************
* @author:  ReLesEason
* @date:    2024/6/9 21:56
* @version: 1.0
* @description: interview question 18
************************************************/


/* Detailed Description
 * 题目：删除链表的结点
 * 在O（1）时间内删除链表结点
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode * Next;
    ListNode(int val):val(val),Next(nullptr){}
};

class Solution_1
{
public:
    ListNode * deleteListNode(ListNode *  ListHead,ListNode * ToBeDeleteNode)
    {
        if (ListHead == nullptr || ToBeDeleteNode == nullptr ||ToBeDeleteNode->Next == nullptr)
        {
            return ListHead;
        }

        ToBeDeleteNode->val = ToBeDeleteNode->Next->val;

        ListNode * temp = new ListNode(0);
        temp = ToBeDeleteNode->Next;

        ToBeDeleteNode->Next = ToBeDeleteNode->Next->Next;

        delete temp;

        // 要不开辟出来的指针置空，否则会出现指针悬空的情况
//        temp = nullptr;
    }
};
void test_1()
{
    cout<<"--------------------------------------------------test_1----------------------------------------------------"<<endl;
    Solution_1 solution1;
    ListNode * ListHead = new ListNode(1);

    ListHead->Next = new ListNode(2);

    ListHead->Next->Next = new ListNode(3);

    ListHead->Next->Next->Next = new ListNode(4);



//    solution1.deleteListNode(ListHead,ListHead->Next->Next);
//    solution1.deleteListNode(ListHead, nullptr);
    solution1.deleteListNode(ListHead,ListHead->Next->Next->Next->Next);


    ListNode *  curNode = ListHead;
    while (curNode != nullptr)
    {
        cout<<curNode->val<<endl;
        curNode = curNode->Next;
    }
}

int main() {
    test_1();


    return 0;
}