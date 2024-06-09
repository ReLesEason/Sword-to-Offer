/***********************************************
* @author:  ReLesEason
* @date:    2024/6/9 15:09
* @version: 1.0
* @description: interview question 14
************************************************/


/* Detailed Description
 * 题目：剪绳子
 * 给你一根长度为n的绳子，请把绳子剪成 m 段（m,n都是大于1的整数）
 * 每段绳子的长度记为k[0],k[1],...,k[m-1]。
 * 请问k[0] * k[1] * ... * k[m-1]可能的最大乘积为多少。
 */

#include <bits/stdc++.h>

using namespace std;


/* 动态规划算法
 * 动态规划的基本思想是通过将问题拆分成子问题来解决。
 * 对于剪绳子问题，设定一个数组 dp, dp[i] 表示长度为i的绳子剪成若干段后的最大乘积
 * 对于每个长度 i 的绳子，我们尝试将其剪成两段，长度分别为 j 和 i-j，其中 j 从 1 到 i/2，因为这是从两头剪是对称的
 * dp[i]：当前长度为 i 的绳子的最大乘积。
 * dp[j]：长度为 j 的绳子的最大乘积。
 * dp[i - j]：长度为 i - j 的绳子的最大乘积。
 *
 * 通过剪一刀，长度为 i 的绳子被分成了两段：j 和 i - j，我们需要比较以下两种情况来更新 dp[i]：
 * 当前 dp[i] 的值（之前已经计算的最大值，比如i<=4）。
 * 将 j 和 i - j 这两段的最大乘积相乘后的结果，即 dp[j] * dp[i - j]。
 * 最终 dp[i] 会记录长度为 i 的绳子的最大乘积。
 * */
class Solution_1 {
public:
    int cutRope(int n) {
        if (n <= 4) {
            return n;
        }
        vector<int> dp(n + 1, 0);

        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;
        dp[4] = 4;

        for (int i = 5; i <= n; i++) {
            for (int j = 1; j <= i / 2; j++) {
                dp[i] = max(dp[i], dp[j] * dp[i - j]);
            }
        }
        return dp[n];
    }

};

void test_1() {
    cout
            << "----------------------------------------------------test_1--------------------------------------------------"
            << endl;
    Solution_1 solution1;
    cout << solution1.cutRope(6) << endl;

}

/* 贪婪算法
 * 与动态规划不同，贪婪算法的每一步都做出一个贪婪的选择
 * 以该题为例，如果绳子长度大于等于5，则每次都应该剪出一个长度为3的绳子
 * 直到最后绳子长度小于5
 *
 * 根据均值不等式： (n1+n2+...+nm)/m >= pow(n1*n2*...*nm,1/m);
 * 等号当且仅当 n1 = n2 = ... = nm 时成立，因此，要时乘机最大，应该以相等的长度分成多段、
 *
 * 将长度为n的绳子分成每段为x的m段，则 n = mx,乘积为 pow(x,m), 有 pow(x,m) = pow(x,n/x) = pow(pow(x,1/x),n)
 * 当 pow(x,1/x)最大时，乘积最大，通过求导和求极值得到，当驻点为 e 时，即将每段分成e ,乘积最大
 * 但要求分成整数段，所以只有2和3，二者带入公式，发现3的乘积最大
 * 因此，贪心算法就是每一步都尽可能的取到最优值，即每段都分成 3，结果就会最大
 *
 * */
class Solution_2 {
public:
    int cutRope(int n) {
        if (n <= 4) {
            return n;
        }
        int result = 1;
        while (n >= 5) {
            result *= 3;
            n -= 3;
        }
        result = result * n;


        return result;
    }

};

void test_2() {
    cout
            << "----------------------------------------------------test_2--------------------------------------------------"
            << endl;
    Solution_2 solution2;
    cout << solution2.cutRope(7) << endl;

}

/* 数学规律法
 * n              m             max          分析
 * 3              3              3            2^0 * 3^1
 * 4              2+2            4            2^2 * 3^0
 * 5              2+3            6            2^1 * 3^1
 * 6              3+3            9            2^0 * 3^3
 * 7              3+4            12           2^2 * 3^1
 * 8              3+3+2          18           2^1 * 3^2
 * 9              3+3+3          27           2^0 * 3^3
 *
 * n              n%3==0                      2^0 * 3^(n/3)
 * /              n%3==1                      2^2 * 3^(n/3-1)
 * /              n%3==2                      2^1 * 3^(n/3)
 *
 * */
class Solution_3 {
public:
    int cutRope(int n) {
        if (n <= 0) {
            return n;
        }
        if (n % 3 == 0) {
            return pow(3, n / 3);
        }
        if (n % 3 == 1) {
            return 4 * pow(3, n / 3 - 1);
        }
        if (n % 3 == 2) {
            return 2 * pow(3, n / 3);
        }

    }

};

void test_3() {
    cout
            << "----------------------------------------------------test_3--------------------------------------------------"
            << endl;
    Solution_3 solution3;
    cout << solution3.cutRope(0) << endl;

}

int main() {
    test_1();
    test_2();
    test_3();

    return 0;
}