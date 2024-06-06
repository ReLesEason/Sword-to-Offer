/***********************************************
* @author:  ReLesEason
* @date:    2024/6/6 21:32
* @version: 1.0
* @description: interview question 8
************************************************/


/* Detailed Description
 * 题目：旋转数组中的最小数字
 *
 * 1、遍历法
 * 2、二分法
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // 遍历法
    int func_1(const vector<int>& v)
    {
        if (v.empty())
        {
            return 0;
        }
        for (int i = 1; i < v.size(); ++i)
        {
            if(v[i-1]>v[i])
            {
                return v[i];
            }
        }
        return v[0];

    }

    // 二分法
    int func_2(const vector<int> &v)
    {
        if(v.empty())
        {
            return 0;
        }
        int low = 0;
        int high = v.size()-1;
        int mid = low;
        while(v[low] >= v[high])
        {
            if(high-low == 1)
            {
                mid = high;
                break;
            }
            mid = (high-low)/2 + low;
            if(v[mid] >= v[low])
            {
                low = mid;
            }
            else if(v[mid] <= v[high])
            {
                high = mid;
            }
        }
        return v[mid];
    }
};


void test_1()
{
    cout<<"------------------------------------------------------test_1-------------------------------------------------"<<endl;
    vector<int> v{3,4,5,1,2};
    Solution solution;
    cout<<solution.func_1(v)<<endl;

}

void test_2()
{
    cout<<"------------------------------------------------------test_2-------------------------------------------------"<<endl;
    vector<int> v{3,4,5,6,7};
    Solution solution;
    cout<<solution.func_1(v)<<endl;

}

void test_3()
{
    cout<<"------------------------------------------------------test_3-------------------------------------------------"<<endl;
    vector<int> v{3,4,5,1,2};
    Solution solution;
    cout<<solution.func_2(v)<<endl;

}

void test_4()
{
    cout<<"------------------------------------------------------test_4-------------------------------------------------"<<endl;
    vector<int> v{3,4,5,6,7};
    Solution solution;
    cout<<solution.func_2(v)<<endl;

}

int main() {
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}