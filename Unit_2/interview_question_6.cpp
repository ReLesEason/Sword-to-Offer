/***********************************************
* @author:  ReLesEason
* @date:    2024/6/4 18:32
* @version: 1.0
* @description: interview question 6
************************************************/


/* Detailed Description
 * 链表
 * 题目：从尾到头打印链表
 */

#include <bits/stdc++.h>
using namespace std;

/* 结点结构
 * */
struct ListNode
{
    int m_value;
    ListNode * m_next;

    ListNode(int x):m_value(x),m_next(nullptr){}
};


/* 列表类
 * */
class MyList
{
public:

    ListNode * listHead;

    MyList():listHead(nullptr){}

    ~MyList()
    {
        while(listHead!= nullptr)
        {
            ListNode * temp = listHead;

            listHead = listHead->m_next;

            delete temp;
        }
    }

    void addToHead(int value)
    {
        ListNode * p_new = new ListNode(value);
        p_new->m_next = this->listHead;
        listHead = p_new;
    }

    void addToTail(int value)
    {
        ListNode * p_new = new ListNode(value);
        p_new->m_next = nullptr;

        if (this->listHead == nullptr)
        {
            this->listHead = p_new;
        }
        else
        {
            ListNode * p_cur = this->listHead;
            while(p_cur->m_next != nullptr)
            {
                p_cur = p_cur->m_next;
            }
            p_cur->m_next = p_new;
        }
    }

    void deleteNode(int value)
    {
        if(this->listHead == nullptr)
        {
            cout<<" list is empty"<<endl;
            return;
        }
        ListNode * p_cur = this->listHead;
        while(p_cur->m_next->m_value != value)
        {
            p_cur = p_cur->m_next;
        }
        if (p_cur->m_next->m_value == value)
        {
            ListNode * p_delete = p_cur->m_next;
            p_cur->m_next = p_delete->m_next;
        }
    }

    void printList()
    {
        if (this->listHead == nullptr)
        {
            cout<<" list is empty"<<endl;
        }
        else
        {
            ListNode * p_cur = listHead;
            while(p_cur != nullptr)
            {
                cout<<p_cur->m_value<<" ";
                p_cur = p_cur->m_next;
            }
            cout<<endl;
        }
    }

    /* 从尾到头打印链表-用栈实现
     * */
    void ReversePrintListByStack()
    {
        stack<ListNode*> list_stack;
        ListNode * p_cur = this->listHead;
        while (p_cur != nullptr)
        {
            list_stack.push(p_cur);
            p_cur = p_cur->m_next;
        }
        while (!list_stack.empty())
        {
            cout<<list_stack.top()->m_value<<" ";
            list_stack.pop();
        }
        cout<<endl;
    }

    /* 从尾到头到打印链表-递归实现
     * */
    void ReversePrintListByRecursion(ListNode * listNode)
    {
        if (listNode != nullptr)
        {
            if (listNode->m_next != nullptr)
            {
                ReversePrintListByRecursion(listNode->m_next);
            }
            cout<<listNode->m_value<<" ";
        }
    }

    /* 从尾到头到打印链表-vector实现
     * */
    void ReversePrintListByVector()
    {
        vector<ListNode*> list_vector;
        ListNode * p_cur = this->listHead;
        while(p_cur != nullptr)
        {
            list_vector.push_back(p_cur);
            p_cur = p_cur->m_next;
        }

        reverse(list_vector.begin(),list_vector.end());
        for_each(list_vector.begin(),list_vector.end(),[](ListNode * list_node){cout<<list_node->m_value<<" ";});
        cout<<endl;
    }

    /* 从尾到头到打印链表-vector实现-直接逆序输出
    * */
    void ReversePrintListByVector2()
    {
        vector<ListNode*> list_vector;
        ListNode * p_cur = this->listHead;
        while(p_cur != nullptr)
        {
            list_vector.push_back(p_cur);
            p_cur = p_cur->m_next;
        }

        for_each(list_vector.rbegin(),list_vector.rend(),[](ListNode * list_node){cout<<list_node->m_value<<" ";});
    }

};

void test_1()
{
    cout<<"----------------------------------------------------test_1---------------------------------------------------"<<endl;
    MyList m_list;
//    m_list.addToHead(1);
//    m_list.addToHead(2);
//    m_list.addToHead(3);
    m_list.addToTail(4);
    m_list.addToTail(5);
    m_list.addToTail(6);
    m_list.printList();

    m_list.deleteNode(5);
    m_list.printList();
}

void test_2()
{
    cout<<"----------------------------------------------------test_2---------------------------------------------------"<<endl;
    MyList myList;
    myList.addToTail(1);
    myList.addToTail(2);
    myList.addToTail(3);
    myList.addToTail(4);
    myList.addToTail(5);

    myList.printList();

    myList.ReversePrintListByStack();
}

void test_3()
{
    cout<<"----------------------------------------------------test_3---------------------------------------------------"<<endl;
    MyList myList;
    myList.addToTail(10);
    myList.addToTail(20);
    myList.addToTail(30);
    myList.addToTail(40);
    myList.addToTail(50);

    myList.printList();

    myList.ReversePrintListByRecursion(myList.listHead);
    cout<<endl;
}

void test_4()
{
    cout<<"----------------------------------------------------test_4---------------------------------------------------"<<endl;
    MyList myList;
    myList.addToTail(100);
    myList.addToTail(200);
    myList.addToTail(300);
    myList.addToTail(400);
    myList.addToTail(500);

    myList.printList();

    myList.ReversePrintListByVector();
}

void test_5()
{
    cout<<"----------------------------------------------------test_5---------------------------------------------------"<<endl;
    MyList myList;
    myList.addToTail(1000);
    myList.addToTail(2000);
    myList.addToTail(3000);
    myList.addToTail(4000);
    myList.addToTail(5000);

    myList.printList();

    myList.ReversePrintListByVector2();
}



int main() {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();


    return 0;
}