/***********************************************
* @author:  ReLesEason
* @date:    2024/5/22 20:28
* @version: 1.0
* @description: interview question 4
************************************************/


/* Detailed Description
 * 二维数组中的查找
 * 描述：在一个 n*m 的二维数组中，每一行都按照从左到右递增的顺序排序，
 * 每一列都按照从上到下递增的顺序排序。请完成一个函数，
 * 输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 *
 * 例如：
 * 1 2 8 9
 * 2 4 9 12
 * 4 7 10 13
 * 6 8 11 15
 *
 * 我们要找到数字
 *
 * 解题思路：
 * 对于数字7，如果当前数小于7，则需要在当前数的右边和下边中找，如果当前数大于7，则需要在当前数的左边和上边中找。
 * 假设当前数小于要找的数：
 * 1、首先从数组的右上角的数字9开始。由于9大于7，而9是这列的最小值，因此7不可能在该列中，故先剔除该列，剩下：
 * 1 2 8
 * 2 4 9
 * 4 7 10
 * 6 8 11
 *
 * 2、在剩下的矩阵中，位于右上角的数字是8，同样将该列剔除,剩下：
 * 1 2
 * 2 4
 * 4 7
 * 6 8
 *
 * 3、在剩下的矩阵中，位于右上角的数字是2，2小于7，因此7不可能出现在2的右边，只能出现在下边，因此将2这行进行剔除，剩下：
 * 2 4
 * 4 7
 * 6 8
 *
 * 4、在剩下的矩阵中，位于右上角的数字是4，同样将该行剔除，剩下：
 * 4 7
 * 6 8
 *
 * 5、在剩下的矩阵中，位于右上角的数字是7，7等于要找的数，因此返回true。
 *
 * 两种方式：STL中的嵌套vector表示二维数组 和 C++中原生的二维数组
 * 对于原生中的二维数组，int arr[M][N]
 * arr 虽然表示二维数组的地址，但是作为函数参数时，类型是int [][N],列数是要确定的
 * 或者会隐式转换为 int * [N]的类型，表示指向int数组的指针 并不代表第一行的地址
 *
 * 但是我们需要用指针的方式访问二维数组时，需要的是第一行的地址
 * arr[0] 和 &arr[0][0] 都可以表示第一行的地址
 *
 */

#include <bits/stdc++.h>
using namespace std;

// vector
class Solution_1 {
public:
    bool findNumberIn2DVector(vector<vector<int>>& arr,int rows,int cols,int target)
    {
        if(arr.empty() || arr[0].empty())
            return false;

        bool result = false;
        int row =0 ;
        int col = cols-1;

        while(row<rows && col>=0)
        {
            if(arr[row][col] == target)
            {
                result = true;
                break;
            }
            else if(arr[row][col] > target)
            {
                col--;
            }
            else
            {
                row++;
            }
        }
        return result;
    }
};

void test_1()
{
    cout<<"------------------------------------------------test_1------------------------------------------------------"<<endl;
    vector<vector<int>> v = {
            {1,2,8,9},
            {2,4,9,12},
            {4,7,10,13},
            {6,8,11,15}
    };
    int rows = v.size();
    int cols = v[0].size();
    cout<<"rows: "<<rows<<" cols: "<<cols<<endl;
    int target = 7;
    Solution_1 s;
    bool result = s.findNumberIn2DVector(v,rows,cols,target);
    if(result)
        cout<<"Target number found in 2D vector"<<endl;
    else
        cout<<"Target number not found in 2D vector"<<endl;
}
void test_2()
{
    cout<<"------------------------------------------------test_2------------------------------------------------------"<<endl;
    vector<vector<int>> v = {
            {0}
    };
    int rows = v.size();
    int cols = v[0].size();
    cout<<"rows: "<<rows<<" cols: "<<cols<<endl;
    int target = 7;
    Solution_1 s;
    bool result = s.findNumberIn2DVector(v,rows,cols,target);
    if(result)
        cout<<"Target number found in 2D array"<<endl;
    else
        cout<<"Target number not found in 2D array"<<endl;
}

// array_ptr
class Solution_2 {
public:
    bool findNumberIn2DArray(int arr[], int rows, int cols, int target)
    {
        if(arr == nullptr || rows == 0 || cols == 0)
            return false;

        bool result = false;
        int row = 0;
        int col = cols-1;

        while(row<rows && col>=0)
        {
            if(arr[row*cols+col] == target)
            {
                result = true;
                break;
            }
            else if(arr[row*cols+col] > target)
            {
                col--;
            } else{
                row++;
            }
        }
        return result;
    }
};
void test_3()
{
    cout<<"------------------------------------------------test_3------------------------------------------------------"<<endl;

    int arr[4][6] = {
            {1,2,3,4,5,6},
            {7,8,9,10,11,12},
            {13,14,15,16,17,18},
            {19,20,21,22,23,24}
    };
    int rows = sizeof(arr)/sizeof(arr[0]);
    int cols = sizeof(arr[0])/sizeof(arr[0][0]);
    cout<<"rows: "<<rows<<" cols: "<<cols<<endl;
    int target = 27;
    Solution_2 s;

//    bool result = s.findNumberIn2DArray(arr,rows,cols,target);     // arr 类型为 int* [M]  指向int数组的指针

    bool result_1 = s.findNumberIn2DArray(arr[0],rows,cols,target);   // arr[0]  类型为 int*   指向int元素的指针
    bool result_2 = s.findNumberIn2DArray(&arr[0][0],rows,cols,target);   // &arr[0][0]  类型为 int*    指向int元素的指针
    if(result_1)
    {
        cout<<"Target number found in 2D array"<<endl;
    }
    else
    {
        cout<<"Target number not found in 2D array"<<endl;
    }
}

// array
class Solution_3 {
public:
    // 二维数组作为参数时，需要确定列数
    bool findNumberIn2DArray(int arr[][6], int rows, int cols, int target)
    {
        if(arr == nullptr || rows == 0 || cols == 0)
            return false;

        bool result = false;
        int row = 0;
        int col = cols-1;

        while(row<rows && col>=0)
        {
            if(arr[row][col] == target)
            {
                result = true;
                break;
            }
            else if(arr[row][col] > target)
            {
                col--;
            } else{
                row++;
            }
        }
        return result;
    }
};
void test_4()
{
    cout<<"------------------------------------------------test_4------------------------------------------------------"<<endl;

    int arr[4][6] = {
            {1,2,3,4,5,6},
            {7,8,9,10,11,12},
            {13,14,15,16,17,18},
            {19,20,21,22,23,24}
    };
    int rows = sizeof(arr)/sizeof(arr[0]);
    int cols = sizeof(arr[0])/sizeof(arr[0][0]);
    cout<<"rows: "<<rows<<" cols: "<<cols<<endl;
    int target = 7;
    Solution_3 s;

    int arr_1[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    bool result_ori = s.findNumberIn2DArray(arr,rows,cols,target);     // arr 类型为 int* [M]  指向int数组的指针

    bool result_test = s.findNumberIn2DArray((int(*)[6])arr_1,rows,cols,target);     // arr 类型为 int* [M]  指向int数组的指针
    if(result_test)
    {
        cout<<"Target number found in 2D array"<<endl;
    }
    else
    {
        cout<<"Target number not found in 2D array"<<endl;
    }
}

void test_5()
{
    cout<<"------------------------------------------------test_5------------------------------------------------------"<<endl;

    Solution_2 s;
    cout<<s.findNumberIn2DArray(nullptr,0,0,0)<<endl;
}

int main() {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();

    return 0;
}