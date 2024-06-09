/***********************************************
* @author:  ReLesEason
* @date:    2024/6/9 20:28
* @version: 1.0
* @description: interview question 16
************************************************/


/* Detailed Description
 * 题目：数值的整数次方
 */

#include <bits/stdc++.h>
using namespace std;


/*         a^(n/2)*a^(n/2)               n 为偶数
 * a^n  =  a^(n-1)/2 * a^(n-1)/2 * a     n 为奇数
 *
 * 这个方法只适合exponent 为正整数，如果为负数，右移就会出现问题
 * */
class Solution_1
{
public:

    double powerWithUnsignedExponent(double base,unsigned int exponent)
    {
        if(exponent == 0)
        {
            return 1;
        }
        if(exponent == 1)
        {
            return base;
        }
        double result = powerWithUnsignedExponent(base,exponent>>1);
        result *= result;
        if (exponent & 0x1 == 1)       // 等价于 exponent %2 == 1
        {
            result *= base;
        }
        return result;
    }

};



void test_1()
{
    cout<<"------------------------------------------------------test_1------------------------------------------------"<<endl;
    Solution_1 solution1;
    cout<<solution1.powerWithUnsignedExponent(2,5)<<endl;

    cout<<rand()%10<<endl;




}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    test_1();

    return 0;
}