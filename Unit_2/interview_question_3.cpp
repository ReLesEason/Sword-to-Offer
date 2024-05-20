/***********************************************
* @author:  ReLesEason
* @date:    2024/5/20 19:44
* @version: 1.0
* @description: 数组中重复的数字
************************************************/


/* Detailed Description
 * 在一个长度为n的数组nums中，所有数字都在0到n-1的范围内，找出数组中重复的数字。
 * 例如，给定数组[2, 3, 1, 0, 2, 5, 3]，返回[2, 3]。
 *
 * 注意要检查边界，提高程序的鲁棒性
 */

#include <bits/stdc++.h>
using namespace std;

// 解法一：
/* 思路：
 * 1. 先检查边界
 * 2. 使用排序，然后遍历，
 * 3. 如果相邻的两个数相等，则说明有重复的数字
 * 4. 时间复杂度O(nlogn)，空间复杂度O(1)
 * */
class Solution_1 {
public:
    void findRepeatNumber(std::vector<int>& nums) {
        // 先检查边界
//        if (nums.size() == 0) {
        if (nums.empty()) {
            cerr<<"Input array is empty!"<<endl;
            return;
        }
        // 检查数组中的元素是否在0到n-1的范围内
        for(auto num:nums)
        {
            if(num<0 || num>=nums.size())
            {
                cerr<<"an element exceeds the range of the array!"<<endl;
            }
        }
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] == nums[i + 1]) {
                cout << nums[i] << " ";
            }
        }
        cout << endl;
    }

};

void test_1()
{
    cout << "Test 1: " << endl;
    Solution_1 s1;
    std::vector<int> nums = {2, 3, 1, 0, 2, 5, 3};
    s1.findRepeatNumber(nums);
}

// 解法二：
/* 思路：
 * 1. 先检查边界
 * 2. 使用哈希表，遍历数组
 * 3. 如果哈希表中没有该元素，则插入，否则说明有重复的数字
 * 4. 时间复杂度O(n)，空间复杂度O(n)
 * */
class Solution_2 {
public:
    void findRepeatNumber(std::vector<int> &nums) {
        // 先检查边界
        if(nums.empty()){
            cerr<<"Input array is empty!"<<endl;
            return;
        }
        // 检查数组中的元素是否在0到n-1的范围内
        for(auto num:nums)
        {
            if(num<0 || num>=nums.size())
            {
                cerr<<"an element exceeds the range of the array!"<<endl;
            }
        }
//        std::unordered_set<int> set;
//        for (int i = 0; i < nums.size(); i++) {
//            if (set.count(nums[i]) == 0) {
//                set.insert(nums[i]);
//            }
//            else
//            {
//                cout << nums[i] << endl;
//            }
//        }
        // 关联式容器
        std::unordered_map<int,int> map;
        // 结果容器
        for(auto num:nums)
        {
            map[num]++;
            if(map[num]>1)
            {
                cout<<num<<" ";
            }
        }
        cout<<endl;
    }
};
void test_2()
{
    cout<<"Test 2: "<<endl;
    Solution_2 s2;
    std::vector<int> nums = {2};
    std::vector<int> nums2 = {};
    s2.findRepeatNumber(nums2);
}

// 解法三：
/* 思路：
 * 1. 先检查边界
 * 2. 从头到尾烧苗这个数组中的每个数字
 * 3. 当扫描到下标为i的数字时，首先比较这个数字(用m表示)是不是等于i
 * 4. 如果m等于i，继续扫描下一个数字；如果不是，则拿它和第m个数字进行比较
 * 5. 如果它和第m个数字相等，则说明有重复的数字，输出这个数字，结束程序；如果不相等，则将第i个数字和第m个数字进行交换。
 * 6. 重复这个比较和交换的过程，知道我们发现一个重复的数字或者扫描完整个数组。
 * 7. 时间复杂度O(n)，空间复杂度O(1)
 * */
class Solution_3 {
public:
    void findRepeatNumber(std::vector<int> &nums) {
        // 先检查边界
        if(nums.empty()){
            cerr<<"Input arrat is empty!"<<endl;
            return;
        }
        // 检查数组中的元素是否在0到n-1的范围内
        for(auto num:nums)
        {
            if(num<0 || num>=nums.size())
            {
                cerr<<"an element exceeds the range of the array!"<<endl;
            }
        }
        int i = 0;
        while(true)
        {
                if(i == nums[i])
                {
                    i++;
                    continue;
                }
                else
                {
                    if(nums[i] == nums[nums[i]])
                    {
                        cout<<nums[i]<<endl;
                        break;
                    }
                    else
                    {
                        swap(nums[i],nums[nums[i]]);
                    }

                }
        }
    }
    void swap(int& a,int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

};

void test_3()
{
    cout<<"Test 3: "<<endl;
    Solution_3 s3;
    std::vector<int> nums = {2,1,3,3,4,5,5,6,6,7};
    s3.findRepeatNumber(nums);
}

int main() {
    test_1();
    test_2();
    test_3();

    return 0;
}