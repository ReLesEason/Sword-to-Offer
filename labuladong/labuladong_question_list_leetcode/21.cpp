/***********************************************
* @author:  ReLesEason
* @date:    2024/6/1 20:30
* @version: 1.0
* @description: 21 合并两个有序链表
************************************************/


/* Detailed Description
 * 将两个升序链表合并为一个新的升序链表并返回
 * 1、迭代法
 * 2、递归法
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode * next;
    ListNode():val(0),next(nullptr){}
    ListNode(int x):val(x),next(nullptr){}
    ListNode(int x,ListNode * next):val(x),next(next){}
};

/* 普通迭代方法
 * */
class  Solution_1
{
public:
    ListNode * mergeTwoLists(ListNode * list1,ListNode * list2)
    {
        if(list1 == nullptr && list2 != nullptr)
        {
            return list2;
        }
        else if(list1 != nullptr && list2 == nullptr)
        {
            return list1;
        }
        else if(list1 == nullptr && list2 == nullptr)
        {
            return nullptr;
        }
        ListNode * cur_1 = list1;
        ListNode * cur_2 = list2;

        ListNode * start = new ListNode;

        ListNode * dummy = new ListNode;

        dummy = start;

        while(list1 != nullptr && list2!= nullptr)
        {
            if(list1->val <= list2->val)
            {
                start->next = list1;
//                start = start->next;
                list1 = list1->next;
            }
            else
            {
                start->next = list2;
//                start = start->next;
                list2 = list2->next;
            }
            start = start->next;
        }
        if (list1 != nullptr)
        {
            start->next = list1;
        }
        if(list2 != nullptr)
        {
            start->next = list2;
        }
        return dummy->next;
    }
};

void test_1()
{
    cout<<"-----------------------------------------------------test_1-------------------------------------------------"<<endl;
    Solution_1 s1;
    ListNode * list1 = new ListNode(1,new ListNode(2,new ListNode(3)));


    ListNode * list2 = new ListNode(1,new ListNode(3,new ListNode(4)));


    ListNode * result = s1.mergeTwoLists(list1,list2);

    while(result != nullptr)
    {
        cout<<result->val<<" ";
        result = result->next;
    }
    cout<<endl;

}

/* 递归方法:两个链表头部较小的一个结点与剩下元素的 merge 操作结果合并
 * | list1[0] = merge(list1[1:],list2)       list[0] < list2[0]
 * | list2[0] = merge(list1,list2[1:])       otherwise
 * */
class Solution_2
{
public:
    ListNode * mergeTwoLists(ListNode* l1,ListNode * l2)
    {
        if(l1 == nullptr && l2 != nullptr)
        {
            return l2;
        }
        else if(l1 != nullptr && l2 == nullptr)
        {
            return l1;
        }
        else if(l1->val <= l2->val)
        {
            l1->next = mergeTwoLists(l1->next,l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1,l2->next);
            return l2;
        }
    }
};

void test_2()
{
    cout<<"-----------------------------------------------test_2--------------------------------------------------------"<<endl;
    Solution_1 s1;
    ListNode * list1 = new ListNode(1,new ListNode(2,new ListNode(3)));
    ListNode * list2 = new ListNode(1,new ListNode(3,new ListNode(4)));

    ListNode * result = s1.mergeTwoLists(list1,list2);

    while(result != nullptr)
    {
        cout<<result->val<<" ";
        result = result->next;
    }
    cout<<endl;

}

int main() {
    test_1();
    test_2();

    return 0;
}