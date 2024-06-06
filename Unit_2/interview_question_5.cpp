/***********************************************
* @author:  ReLesEason
* @date:    2024/5/27 20:37
* @version: 1.0
* @description: interview question 5
************************************************/


/* Detailed Description
 * 字符串
 * 替换空格
 * 题目：请事先一个函数，把字符串中的每个空格替换成"%20"。
 * 例如，输入“We are happy.”，则输入"We%20are%20happy."
 */

#include <bits/stdc++.h>
using namespace std;

void test_1()
{
    cout<<"---------------------------------------------------test_1---------------------------------------------------"<<endl;

    /* 当用一个字符串常量去初始化一个数组和一个指针时，情况是不同的
     * */

    char str_1[] = "hello world";
    char str_2[] = "hello world";

    char *str_3 = "hello world";
    char *str_4 = "hello world";

    if(str_1 == str_2)
    {
        cout<<"str_1 and str_2 are the same"<<endl;
    }
    else
    {
        cout<<"str_1 and str_2 are not the same"<<endl;
    }

    if(str_3 == str_4)
    {
        cout<<"str_3 and str_4 are the same"<<endl;
    }
    else {
        cout << "str_3 and str_4 are not the same" << endl;
    }

    /* 结论：
     * 1、用于初始化数组时，会为它们分配两个长度相同的内存空间，并把字符串常量的内容分别复制到数组中，这是两个初始地址不同的数组
     * 2、用于初始化指针时，无需为指针分配内存空间以存储字符串内容，而是只把它们指向字符串常量的内存中的地址就可以了。因此，它们指向同一个地址。
     * */
}

void test_2()
{
    cout<<"---------------------------------------------------test_2---------------------------------------------------"<<endl;

    string str = "We are happy.";

    for(int i =0;i <str.length();i++)
    {
        if(str[i] ==' ')
        {
            str.replace(i,1,"%20");
        }
    }
    cout<<str<<endl;
}

class Solution
{
public:
    void replaceSpace(char str[],int length)
    {
        if(str == nullptr || length <= 0)
        {
            cerr<<"Invalid Input"<<endl;
            return;
        }

        int original_length = 0;
        int numberofBlank = 0;
        int i = 0;
        while(str[i] != '\0')
        {
            original_length++;
            if(str[i] == ' ')
            {
                numberofBlank++;
            }
            i++;
        }

        int new_length = original_length+ 2*numberofBlank;
        if(new_length > length)
        {
            cerr<<"Not Enough Space"<<endl;
            return;
        }


        int p1 = original_length;   // 这里不能减1，因为还有\0结束符也要包括，不然会出现乱码
        int p2 = new_length;
        while(p1 >= 0 && p2 > p1)
        {
            if(str[p1] == ' ')
            {
                str[p2--] = '0';
                str[p2--] = '2';
                str[p2--] = '%';
            }
            else
            {
                str[p2--] = str[p1];
            }
            p1--;
        }
    }
};

void test_3()
{
    cout<<"----------------------------------------------------test_3---------------------------------------------------"<<endl;

    char str[] = " we are happy.";

    Solution s;

    int length = sizeof(str)/sizeof(str[0]);
    cout<<length<<endl;

    cout<<str<<endl;

    s.replaceSpace(str,length*2);

    cout<<str<<endl;


}

int main() {
    test_1();
    test_2();
    test_3();

    return 0;
}