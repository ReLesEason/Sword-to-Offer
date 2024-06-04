/***********************************************
* @author:  ReLesEason
* @date:    2024/5/21 20:26
* @version: 1.0
* @description: interview question 3
************************************************/


/* Detailed Description
 * 不修改数组的情况下，找出重复的数字
 * 在一个长度为n+1的数组里的所有数字都在1~n的范围内，所以数组中至少有一个数字是重复的。
 * 请找出数组中任意一个重复的数字，但不能修改输入的数组。
 */

#include <bits/stdc++.h>
using namespace std;

/* 解法一
 * 用一个临时数组接收，逐一将原数组中的数字复制到该辅助数组中
 * 如果被赋值的数字是m,则将它复制到辅助数组下标为m的位置
 * 时间复杂度O(n)，空间复杂度O(n)
 */
class Solution_1
{
public:
    int getDuplicateNumber(int nums[],int length)
    {
        if(nums == nullptr || length <= 0)
        {
            cerr<<"Invalid Input"<<endl;
            return -1;
        }
        int * temp = new int[length];
        for(int i = 0; i < length; i++)
        {
            if(temp[nums[i]]==1)
            {
                return nums[i];
            }
            else
            {
                temp[nums[i]] = 1;
            }
        }
    }
};

void test_1()
{
    Solution_1 s;
    int nums[10] = {2, 3, 1, 0, 2, 5, 3};
    int length = sizeof(nums)/sizeof(nums[0]);
    // 即使传入了是数组，也会自动退化成指针
    cout<<s.getDuplicateNumber(nums,length)<<endl;
}

/* 解法二：
 * 用二分法思想：
 * 对一个1~n数组，从1~n中间的数字m分为两部分，前面一部分为1~m,后一部分为m+1~n
 * 如果1~m的数字超过m,那么这部分一定有重复数字
 * 否则另一半的m+1~n区间里一定有重复数字
 * 然后继续把m+1~n分为两部分，直到找到重复数字
 * 时间复杂度O(nlogn)，空间复杂度O(1)
 * */
class Solution_2
{
public:
    int getDuplicateNumber(int nums[],int length)
    {
        if(nums == nullptr || length <= 0)
        {
            cerr<<"Invalid Input"<<endl;
            return -1;
        }
        // 这里的start 和 end 并不做为索引下标，而是数组元素中的元素范围
        int start = 1;
        int end = length - 1;

        while(start <= end)
        {
            // >> 表示右移，相当于除以2，它通过位操作实现，在某些情况下，运算速度比除法快
            // 求一个中间值，在二分排序和快速排序中比较常用
            int mid = ((end-start)>>1) + start;       // 相对于start的偏移量
            int count = getNumCount(nums,length,start,mid);
            if(end==start)
            {
                if(count > 1)
                {
                    return start;
                }
                else
                {
                    break;
                }
            }
            if(count > mid - start + 1)
            {
                end = mid;
            }
            else
            {
                start = mid + 1;
            }
        }
    }
    int getNumCount(int nums[],int length,int start,int end)
    {
        if(nums == nullptr || length == 0)
        {
            cerr<<"Invalid Input"<<endl;
            return 0;
        }
        int count = 0;
        for(int i = 0; i < length; i++)
        {
            if(nums[i] >= start && nums[i] <= end)
            {
                count++;
            }
        }
        return count;
    }
};

void test_2()
{
    Solution_2 s;
    int nums[10] = {2, 3, 5, 4, 3, 2, 6,7};
    int length = sizeof(nums)/sizeof(nums[0]);
    cout<<s.getDuplicateNumber(nums,length)<<endl;
}


int main() {
    test_1();
    test_2();

    return 0;
}