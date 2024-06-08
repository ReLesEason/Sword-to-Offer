/***********************************************
* @author:  ReLesEason
* @date:    2024/6/8 18:55
* @version: 1.0
* @description: interview question 12
************************************************/


/* Detailed Description
 * 题目：矩阵中的路径
 * 请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径
 */

#include <bits/stdc++.h>
using namespace std;

class Solution_1
{
public:
    bool hasPath(vector<vector<char>> & matrix,const string & target)
    {
        if(matrix.size() == 0)
        {
            return false;
        }
        // 初始化访问标记矩阵
        vector<vector<bool>> visited(matrix.size(),vector<bool>(matrix[0].size(), false));
        for(int i =0;i < matrix.size();i++)
        {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (dfs(matrix,target,i,j,0,visited))
                {
                    return true;
                }

            }
        }
        return false;
    }

    bool dfs(vector<vector<char>> & matrix,const string& traget,int x,int y, int index,vector<vector<bool>>&visited)
    {
        if(index == traget.size())
        {
            return true;
        }
        // 出界，或者已经被访问过，或者不匹配都返回false
        if (x < 0 || x>= matrix[0].size() || y < 0 || y >= matrix.size() || visited[x][y] || matrix[x][y] != traget[index])
        {
            return false;
        }
        // 先将该点置为已访问
        visited[x][y] = true;

        // 分别从四个方向探索是否存在目标路径，有一个方向或者多个方向存在即可
        bool found = dfs(matrix,traget,x-1,y,index+1,visited) ||
                     dfs(matrix,traget,x+1,y,index+1,visited) ||
                     dfs(matrix,traget,x,y-1,index+1,visited) ||
                     dfs(matrix,traget,x,y+1,index+1,visited);
        // 如果这个结点不存在目标路径，则回溯到上个状态，方便其他结点探索时可以继续访问
        visited[x][y] = false;

        return found;
    }

};

void test_1()
{
    cout<<"--------------------------------------------------test_1-----------------------------------------------------"<<endl;
    vector<vector<char>> v{{'a','b','c','d'},
                           {'e','f','g','h'},
                           {'i','j','k','l'},
                           {'m','n','o','p'}};

    vector<vector<char>> v2{{'a','b','c','d'},
                           {'e','f','g','h'},
                           {'i','j','k','l'}};
    cout<<v2[0].size()<<" "<< v2.size()<<endl;
    string target = "abcgkopq";

    Solution_1 solution1;
    cout<<solution1.hasPath(v,target)<<endl;
}

int main() {
    test_1();

    return 0;
}