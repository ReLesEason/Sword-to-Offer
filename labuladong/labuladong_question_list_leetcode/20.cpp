/***********************************************
* @author:  ReLesEason
* @date:    2024/5/15 21:46
* @version: 1.0
* @description: leetcode 20 有效的括号
************************************************/


#include <bits/stdc++.h>
using namespace std;

// 简单版本
class Solution
{
public:
    // 当前括号是右括号是，返回对应的左括号，方便与栈顶进行判断
    char current_char(char c)
    {
        if(c=='}')
        {
            return '{';
        }
        if(c==')')
        {
            return '(';
        }
        return '[';
    }

    bool isValid(string s)
    {
        // 栈
        stack<char> c;
        // 遍历字符串
        for (int i = 0; i < s.size(); i++)
        {
            // 如果是左括号，压栈
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            {
                c.push(s[i]);
            }
            else
            {
                // 如果是右括号，判断栈顶是否匹配
                if (!c.empty() && current_char(s[i]) == c.top())
                {
                    // 匹配，则将匹配的左括号处栈
                    c.pop();
                }else
                {
                    // 不匹配，返回false
                    return false;
                }
            }
        }
        // 最后，如果栈为空，则说明所有括号都匹配，返回true
        return c.empty();
    }
};

// 优化版本
class Solution2
{
public:
    bool isValid(string s)
    {
        int n = s.size();
        // 括号字符串长度为奇数，肯定不匹配
        if (n % 2 != 0)
        {
            return false;
        }

        // 用于辅助右括号关联对应的左括号的射影关键容器 第一个元素为键（key），第二个元素为值（value）
        unordered_map<char, char>pairs = {
                {')', '('},
                {']', '['},
                {'}', '{'}
        };

        stack<char> stk;

        for (auto i: s)
        {
            if (i == '(' || i == '[' || i == '{')
            {
                stk.push(i);
            }
            else
            {
                if (!stk.empty() && pairs[i] == stk.top())
                {
                    stk.pop();
                }
                else
                {
                    return false;
                }
            }
        }
        return stk.empty();
    }
};



void test()
{
    Solution s;
    string str = "()[]{}";
    bool res = s.isValid(str);
    cout << res << endl;
}

int main() {
    test();


    return 0;
}