//
// Created by ReLesEason on 2024/5/15.
//


#include <bits/stdc++.h>
using namespace std;

/* 实现Singleton模式
 * 题目：设计一个类，我们只能生成该类的一个实例
 * 只能生成一个实例的类，是实现了Singleton(单例)模式的类型
 * */

// ----------------------------------------------------------解法一------------------------------------------------------
/* 解法一：单线程解法————基本懒汉式单例（非线程安全）
 * 由于要求只生成一个实例，因此必须把构造函数设为私有函数，以禁止他人创建实例
 * 可以定义一个静态的实例，在需要的时候创建该实例
 * 缺点：多线程情况下，不同线程可能创建出不同的Singleton实例
 * */
class Singleton_1
{
public:
    //
    static Singleton_1* getInstance()
    {
        // 判断是否为空，为空则创建实例
        if (m_instance == nullptr)
        {
            m_instance = new Singleton_1();
        }
        return m_instance;
    }

    static void destroyInstance()
    {
        if (m_instance!= nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }
private:
    // 将构造函数私有化
    Singleton_1()
    {
        cout << "Singleton_1 created" << endl;
    }
    // 定义一个静态的实例
    static Singleton_1* m_instance;
};
// Singleton_1的静态实例初始化
Singleton_1* Singleton_1::m_instance = nullptr;

// 单线程测试
void test_1_1()
{
    cout<<"----------------------------------------------test_1_1 单线程测试----------------------------------------"<<endl;
    // 因为getInstance()是静态函数，它不属于某个特定对象，而属于类本身，所以可以通过类名直接调用
    Singleton_1* s1 = Singleton_1::getInstance();
    cout << "s1: " << s1 << endl;            // s1: 0x80005a890

    Singleton_1* s2 = Singleton_1::getInstance();
    cout << "s2: " << s2 << endl;            // s2: 0x80005a890

    if (s1 == s2)
    {
        cout << "s1 == s2" << endl;         // s1 == s2
        cout << "test_1_1 passed" << endl;
    }
    else
    {
        cout << "s1 != s2" << endl;
        cout << "test_1_1 failed" << endl;
    }

    /* 两个实际指针指向的地址相同
     * */
}
// 多线程测试
void test_1_2()
{
    cout << "---------------------------------------------test_1_2 多线程测试-----------------------------------------------" << endl;
    // []()是 lambda表达式，它是一个匿名函数对象
    // 通常形式为：[捕获列表](参数列表)->返回类型{函数体}
    // 当没有参数列表和返回类型时，可以简化为：[捕获列表]{函数体}
    std::thread t1([]()
    {
        Singleton_1* s1 = Singleton_1::getInstance();
        std::cout << "Thread 1: Singleton_1 address: " << s1 << std::endl;
    });
    std::thread t2([]()
    {
        Singleton_1* s2 = Singleton_1::getInstance();
        std::cout << "Thread 2: Singleton_1 address: " << s2 << std::endl;
    });
    t1.join();
    t2.join();

    Singleton_1::destroyInstance();// 清理单例
}

// ----------------------------------------------------------解法二------------------------------------------------------
/* 解法二：多线程+加锁——懒汉式单例（线程安全）——效果不高
 * 通过加一个同步锁来保证线程安全
 * 缺点：加锁是一个非常耗时的操作，会影响效率
 * */
class Singleton_2
{
public:
    static Singleton_2* getInstance()
    {
        // 自动加锁
//        std::lock_guard<std::mutex> lock(m_mutex);  // 类模板实例，用于管理一个互斥锁
        // 在构造lock时，对m_mutex进行加锁，当lock离开其作用域时，析构被调用，从而解锁m_mutex

        // 判断是否为空，为空则创建实例
        if(m_instance == nullptr)
        {
            // 手动上锁
            m_mutex.lock();
            /* 双重检查锁定（DCLP,double-checked locking pattern）
             * 一次加锁和解锁，消耗较大，特别是对于大数据的操作，将直接称为程序性能的瓶颈
             * 双重检查锁定，即先检查对象是否为空，如果为空再上锁，避免重复上锁
             * 基本思想：获取单例实例之前，先检查实例是否已被初始化，如果没有，则加锁
             *         并再次判断是否已初始化，这是因为可能该线程执行到这时被挂起，而其他线程执行到这时进行了初始化
             *         等该线程重新载入后，如果直接初始化，则重复了，所以要再次判断一下
             *         然后，返回实例
             * */
            if (m_instance == nullptr)
            {
                m_instance = new Singleton_2();
            }
            // 手动解锁
            m_mutex.unlock();
        }
        return m_instance;
    }

    static void destroyInstance()
    {
        if (m_instance != nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }
private:
    Singleton_2()
    {
        cout << "Singleton_2 created" << endl;
    };
    static Singleton_2* m_instance;
    static std::mutex m_mutex;
};

Singleton_2* Singleton_2::m_instance = nullptr;
std::mutex Singleton_2::m_mutex;

// 多线程测试
void print_singleton_address()
{
    Singleton_2* s = Singleton_2::getInstance();
    cout << "Singleton_2 address: " << s << endl;
}
void test_2_1()
{
    cout << "---------------------------------------------test_2_1 多线程测试--------------------------------------------" << endl;
    vector<std::thread> threads;
    // 10个线程进行创建单例实例，结果都指向同一个地址
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(print_singleton_address));
    }
    for (auto& thr : threads) {
        thr.join();
    }
}

int main() {
    test_1_1();
    test_1_2();
    test_2_1();

    return 0;
}