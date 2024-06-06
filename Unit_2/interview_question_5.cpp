/***********************************************
* @author:  ReLesEason
* @date:    2024/5/27 20:37
* @version: 1.0
* @description: interview question 5
************************************************/


/* Detailed Description
 * �ַ���
 * �滻�ո�
 * ��Ŀ��������һ�����������ַ����е�ÿ���ո��滻��"%20"��
 * ���磬���롰We are happy.����������"We%20are%20happy."
 */

#include <bits/stdc++.h>
using namespace std;

void test_1()
{
    cout<<"---------------------------------------------------test_1---------------------------------------------------"<<endl;

    /* ����һ���ַ�������ȥ��ʼ��һ�������һ��ָ��ʱ������ǲ�ͬ��
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

    /* ���ۣ�
     * 1�����ڳ�ʼ������ʱ����Ϊ���Ƿ�������������ͬ���ڴ�ռ䣬�����ַ������������ݷֱ��Ƶ������У�����������ʼ��ַ��ͬ������
     * 2�����ڳ�ʼ��ָ��ʱ������Ϊָ������ڴ�ռ��Դ洢�ַ������ݣ�����ֻ������ָ���ַ����������ڴ��еĵ�ַ�Ϳ����ˡ���ˣ�����ָ��ͬһ����ַ��
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


        int p1 = original_length;   // ���ﲻ�ܼ�1����Ϊ����\0������ҲҪ��������Ȼ���������
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