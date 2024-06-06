/***********************************************
* @author:  ReLesEason
* @date:    2024/6/6 19:17
* @version: 1.0
* @description: interview question 8
************************************************/


/* Detailed Description
 * ��Ŀ��������ջʵ��һ�����У���ʵ�ֶ��е���������appendTail��DeleteHead
 * ���ڶ�β�����㣬�ڶ�ͷɾ�����
 *
 * ������ջʵ�֣�һ����ջ��һ������ջ
 */

#include <bits/stdc++.h>
using namespace std;


class Myqueue
{
public:
    void appendTail(int val)
    {
        this->s1.push(val);
    }

    int deleteHead()
    {
        if (s2.empty())
        {
            while(!this->s1.empty())
            {
                this->s2.push(s1.top());
                s1.pop();
            }
        }
        if (s2.empty())
        {
            throw runtime_error("queue is empty");
        }

        int topvalue = s2.top();

        s2.pop();

        return topvalue;

    }

private:
    stack<int> s1;
    stack<int> s2;

};

void test_1()
{
    Myqueue myqueue;
    for (int i = 0; i < 10; ++i) {
        myqueue.appendTail(i);
    }
    try{
        for (int i = 0; i < 100; ++i) {
            cout<<myqueue.deleteHead()<<endl;
        }
    }catch (const exception& e)
    {
        cerr<<"Caught exception : "<<e.what()<<endl;
    }

}


int main() {
    test_1();

    return 0;
}