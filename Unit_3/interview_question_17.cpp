/***********************************************
* @author:  ReLesEason
* @date:    2024/6/9 21:44
* @version: 1.0
* @description: interview question 17
************************************************/


/* Detailed Description
 * 题目：打印从1到最大的n位数
 * 输入数字n,按顺序打印出从1到最大的n位的十进制数。
 * 比如，输入3，则从打印1、2、3，一直到最大的3位数999
 */

#include <bits/stdc++.h>
using namespace std;

class Solution_1
{
public:
    void printMaxNNumber(int n)
    {
        if (n<=0)
        {
            return;
        }
        /* 给了n,则 10^n-1就是该n位最大的数了
         * */
        for(int i = 1;i<= pow(10,n)-1;i++)
        {
            cout<<i<<endl;
        }
    }
};

void test_1()
{
    Solution_1 solution1;
    solution1.printMaxNNumber(4);
}

int main() {
    test_1();

    return 0;
}