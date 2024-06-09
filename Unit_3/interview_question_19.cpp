/***********************************************
* @author:  ReLesEason
* @date:    2024/6/9 22:40
* @version: 1.0
* @description: interview question 19
************************************************/


/* Detailed Description
 * 题目：正则表达式匹配
 * 请实现一个函数用于匹配包含'.'和'*'的正则表达式。
 * 模式中的字符 '.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次(含0次)
 * 匹配，是指字符串的所有字符可以匹配整个模式
 * 例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配
 * 但与"aa.a"和"ab*a"不匹配，因为，"aa.a"是四个字符，而"aaa"是三个
 */

#include <bits/stdc++.h>
using namespace std;

class Solution_1
{
public:
    bool isMatch(string& text,string& pattern)
    {
        if(text.size() == 0 && (pattern.size() !=0 || pattern.size()==0) )
        {
            return true;
        }
        if (text.size()!=0 && pattern.size()==0)
        {
            return false;
        }

        return isMatchCore(text,pattern,0,0);
    }

    bool isMatchCore(string & text,string & pattern,int i,int j)
    {
        if (j == pattern.size())
        {
            return i == text.size();
        }

        // 检查当前字符是否匹配
        bool cur_match = (i < text.size() && (pattern[j] == text[i] || pattern[j]=='.'));

        if(j+1 < pattern.size() && pattern[j+1] == '*')
        {
            // 两种情况： 不使用'*' || 匹配一次当前字符,并看当前字符的下一个字符是否也匹配
            return (isMatchCore(text,pattern,i,j+2) || (cur_match && isMatchCore(text,pattern,i+1,j)));
        }
        else
        {
            // 当前字符匹配，则递归检测下一个字符是否匹配
            return cur_match && isMatchCore(text,pattern,i+1,j+1);
        }

    }
};

void test_1()
{
    cout<<"-----------------------------------------------------test_1--------------------------------------------------"<<endl;

    string text = "aaa";
    string pattern = "ab*ac*a";

    Solution_1 solution1;
    cout<<solution1.isMatch(text,pattern)<<endl;
}

int main() {
    test_1();

    return 0;
}