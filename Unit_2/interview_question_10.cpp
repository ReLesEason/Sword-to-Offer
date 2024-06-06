/***********************************************
* @author:  ReLesEason
* @date:    2024/6/6 19:59
* @version: 1.0
* @description: interview question 9
************************************************/


/* Detailed Description
 * 题目： 求斐波那契数列的第n项
 * 斐波那契数列的定义如下：
 *         0     n = 0
 * f(n) =  1     n = 1
 *         f(n-1) + f(n-2)
 *
 * 普通青蛙跳台阶（一次只能跳1个或者2个台阶），思路一致
 * 升级版青蛙跳台阶（一次可以跳1~n个台阶）
 */

#include <bits/stdc++.h>
using namespace std;


class Fibonacci
{
public:
    // 递归实现
    int func_1(int n)
    {
        if (n <= 0)
        {
            return 0;
        } else if (n == 1 || n == 2)
        {
            return 1;
        }
        else
        {
            return func_1(n-1)+func_1(n-2);
        }
    }

    // 循环实现-空间复杂度为O(n)
    int func_2(int n)
    {
        if (n == 1 || n == 2)
        {
            return 1;
        }
        vector<int> result(n);
        result[0] = 0;
        result[1] = 1;
        result[2] = 1;
        for(int i = 3;i <= n; i++)
        {
            result[i] = result[i-1]+result[i-2];
        }

        return result[n];
    }

    int func_3(int n)
    {
        if(n <= 1)
        {
            return 1;
        }

        int a = 1,b = 1,c;
        for(int i = 3;i<=n;i++)
        {
            c = a+b;
            a = b;
            b = c;
        }
        return b;
    }

    /* 变态版青蛙跳台阶：
     * 有n个台阶
     * 如果跳了1个，剩下跳法为f(n-1)
     * 如果跳了2个，剩下跳法为f(n-2)
     *
     * 所有，有
     * f(n) = f(n-1)+f(n-2)+...+f(1)
     * f(n-1) = f(n-2)+f(n-3)+...+f(1)
     *
     * 故： f(n) = 2f(n-1)
     * */

    // 递归实现
    int func_4(int n)
    {
        if(n == 1)
        {
            return n;
        }
        return 2* func_4(n-1);
    }

    // 循环实现
    int func_5(int n)
    {
        if(n == 1)
        {
            return n;
        }
        int a = 1,count = 1;
        for(int i = 2;i<=n;i++)
        {
            count = a*2;
            a = count;
        }
        return count;

    }

};

void test_1()
{
    cout<<"-------------------------------------------------test_1-----------------------------------------------------"<<endl;
    Fibonacci fibonacci;
    cout<<fibonacci.func_1(3)<<endl;
}

void test_2()
{
    cout<<"-------------------------------------------------test_2-----------------------------------------------------"<<endl;
    Fibonacci fibonacci;
    cout<<fibonacci.func_2(3)<<endl;
}

void test_3()
{
    cout<<"-------------------------------------------------test_3-----------------------------------------------------"<<endl;
    Fibonacci fibonacci;
    cout<<fibonacci.func_3(5)<<endl;
}

void test_4()
{
    cout<<"-------------------------------------------------test_4-----------------------------------------------------"<<endl;
    Fibonacci fibonacci;
    cout<<fibonacci.func_4(3)<<endl;

}

void test_5()
{
    cout<<"-------------------------------------------------test_5-----------------------------------------------------"<<endl;
    Fibonacci fibonacci;
    cout<<fibonacci.func_5(3)<<endl;

}

int main() {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();

    return 0;
}