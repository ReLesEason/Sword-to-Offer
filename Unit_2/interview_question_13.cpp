/***********************************************
* @author:  ReLesEason
* @date:    2024/6/8 19:27
* @version: 1.0
* @description: interview question 13
************************************************/


/* Detailed Description
 * 题目：机器人的运动范围
 * 地上有一个 m 行 n 列的方格。一个机器人从坐标(0,0)的各自开始移动
 * 它每次可以向左、右、上和下移动一个，但不能进入行坐标和列坐标的数位之和大于k的格子。
 */

#include <bits/stdc++.h>
using namespace std;

class Solution_1
{
public:
    int getGridNum(int m,int n,int k)
    {
        if(k <= 0 || m < 0 || n < 0)
        {
            return 0;
        }

        vector<vector<bool>> visited(m,vector<bool>(n, false));


        return getGridNumCore(0,0,m,n,k,visited);
    }

    // 判断该点是否有效
    bool check(int x,int y,int m,int n,int k,vector<vector<bool>>& visited)
    {
        return x >=0 && x < m && y >=0 && y < n && (getDigitSum(x)+getDigitSum(y) <= k) && !visited[x][y];
    }

    // 获取数位和
    int getDigitSum(int val)
    {
        int valDigitSum = 0;
        while(val > 0)
        {
            valDigitSum += val%10;
            val /=10;
        }
        return valDigitSum;
    }

    int getGridNumCore(int x,int y,int m,int n,int k,vector<vector<bool>>&visited)
    {
        int count = 0;
        if(check(x,y,m,n,k,visited))
        {
            visited[x][y] = true;
            count  = 1 + getGridNumCore(x-1,y,m,n,k,visited)
                       + getGridNumCore(x+1,y,m,n,k,visited)
                       + getGridNumCore(x,y-1,m,n,k,visited)
                       + getGridNumCore(x,y+1,m,n,k,visited);
        }
        return count;
    }
};

void test_1()
{
    cout<<"------------------------------------------------------test_1-------------------------------------------------"<<endl;

    Solution_1 solution1;

    cout<<solution1.getGridNum(4,4,2)<<endl;
}

int main() {
    test_1();


    return 0;
}