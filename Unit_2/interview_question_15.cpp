/***********************************************
* @author:  ReLesEason
* @date:    2024/6/9 16:54
* @version: 1.0
* @description: interview question 15
************************************************/


/* Detailed Description
 * 二进制计算：涉及原码、反码和补码
 * 包括，正整数、负整数、正浮点数和负浮点数的二进制表示
 *
 * 1、 +5 = 2^2 + 2^0
 * 原码： 0000 0101
 * 反码： 0000 0101
 * 补码： 0000 0101
 * 正整数的原码、反码和补码相同，符号位为0
 *
 * 2、 -5
 * 原码： 1000 0101
 * 反码： 1111 1010
 * 补码： 1111 1011
 * 负整数的原码，在其绝对值原码的基础上，将符号位置为1
 * 负整数的反码, 在其原码的基础上，除了符号位外，其余的取反
 * 负整数的补码，在其反码的基础上，加 1
 *
 * 浮点数在计算中使用IEEE 754标准表示，包括三部分：符号位、指数位 和 尾数位
 * 32位的浮点数，符号位（1位，0表整数，1表负数），指数位（8位，使用移码表示指数，偏移量为127），尾数位（23位，存储尾数的有效位，即小数点后的，不包括小数点前一个1）
 *
 * 小数转二进制的过程：不断乘以2，记录每次整数部分的值，当小数部分为.0时结束
 * 例如：0.375
 *     步骤                 整数部分           小数部分
 * 1）0.375 * 2               0                .75
 * 2）0.75  * 2               1                .50
 * 3）0.5   * 2               1                .0
 *
 * 因此 0.375的二进制数为 ： 0.011(每次乘2过程中，结果的整数部分)
 *
 *
 *
 * 3、 12.375    (12 + 0.375 = 8+4 + 0.375)
 * 整数部分二进制： 1100
 * 小数部分二进制： 0.011
 *
 * 整体二进制数：  1100.011
 * 换成科学计数法：1.100011 * 2^3（表示小数点右移3位）
 *
 * 符号位： 0
 * 指数位： 3 + 127 = 130    （10000010）
 * 尾数位： 10001100000000000000000
 *
 * 因此，浮点数在计算机中的表示位：
 * 0 10000010 10001100000000000000000
 *
 * 4、 -12.375
 * 跟正浮点数差不多，区别就是符号位不同
 * 1 10000010 10001100000000000000000
 */

#include <bits/stdc++.h>
using namespace std;


/* 题目：二进制中1的个数
 * 请实现一个函数，输入一个整数，输出该数二进制表示中1的个数。
 * */

/* 布莱恩-克尼根算法
 * */
class Solution_1
{
public:
    int getOneNum(int val)
    {
        int countOne = 0;
        while(val)
        {
            countOne++;
            val = val&(val-1);
        }
        return countOne;
    }
};

void test_1()
{
    cout<<"--------------------------------------------------test_1----------------------------------------------------"<<endl;
    Solution_1 solution1;
    cout<<solution1.getOneNum(-6)<<endl;

    cout<<bitset<32>(-5)<<endl;
    cout<<bitset<32>(-5).count()<<endl;

    string string1 = bitset<32>(-6).to_string();
    cout<< string1<<endl;

    int count = 0;
    for(auto item : string1)
    {
        if (item == '0')
        {
            count++;
        }
    }
    cout<<count<<endl;

}

/* 这种方法只能计算正整数二进制中1的个数
 * 对于负数，在右移后，符号位仍是1，如果一直右移，这32位全变成了1，就会陷入死循环
 * */
class Solution_2
{
public:
    int getOneNum(int val)
    {
        int count = 0;
        while(val)
        {
            if(val & 1)
            {
                count++;
            }
            val = val >> 1;
        }
        return count;
    }
};

void test_2()
{
    cout<<"--------------------------------------------------test_2----------------------------------------------------"<<endl;
    Solution_2 solution2;
    cout<<solution2.getOneNum(-5)<<endl;

}

class Solution_3
{
public:
    int getOneNum(int val)
    {
        int count = 0;
        int flag = 1;
        while(flag)
        {
            if(val & flag)
            {
                count++;
            }
            flag = flag << 1;
        }
        return count;
    }
};

void test_3()
{
    cout<<"--------------------------------------------------test_3----------------------------------------------------"<<endl;
    Solution_3 solution3;
    cout<<solution3.getOneNum(-5)<<endl;

}


int main() {
    test_1();
    test_2();
    test_3();
    return 0;
}