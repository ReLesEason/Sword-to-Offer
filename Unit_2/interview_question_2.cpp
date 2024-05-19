/***********************************************
* @author:  ReLesEason
* @version: 1.0
* @description: Singleton learning
************************************************/


#include <bits/stdc++.h>
using namespace std;

/* 实现Singleton模式
 * 题目：设计一个类，我们只能生成该类的一个实例
 * 只能生成一个实例的类，是实现了Singleton(单例)模式的类型
 *
 * 单例模式(Singleton)是指内存中只会创建且仅创建一次对象的设计模式。
 * 为了防止频繁地创建对象使得内存飙升，单例模式让程序仅在内存中创建一个对象
 * 让所有需要调用地地方都共享这一个单例对象
 * 要想实现单例模式
 * 1、首先，确保跟初始化有关的构造函数以及析构函数是私有的，这样外部无法直接实例化对象，也无法释放单例对象
 * 2、其次，一个静态实例，这个静态实例与程序的生命周期一样
 * 3、线程安全
 *
 *
 * 主要分为懒汉式和饿汉式
 * 懒汉式：在第一次使用时才进行初始化，也称为延迟初始化
 * 饿汉式：程序刚开始运行时就立即进行初始化，也称为预初始化
 *
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
/* 解法二：多线程+加锁——懒汉式单例（线程安全-默认安全，实际并不安全）——效果不高
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
            /* 双重检查锁定（DCL,double-checked locking ）
             * 一次加锁和解锁，消耗较大，特别是对于大数据的操作，将直接称为程序性能的瓶颈
             * 双重检查锁定，即先检查对象是否为空，如果为空再上锁，避免重复上锁
             * 基本思想：获取单例实例之前，先检查实例是否已被初始化，如果没有，则加锁
             *         并再次判断是否已初始化，这是因为可能该线程执行到这时被挂起，而其他线程执行到这时进行了初始化
             *         等该线程重新载入后，如果直接初始化，则重复了，所以要再次判断一下
             *         然后，返回实例
             *
             * DCL 由于内存reoder可能导致线程并不安全(编译器的问题)
             * 因为这行代码：m_instance = new Singleton_2(); 被分成三个步骤执行：
             * 1、分配一个Singleton_2类型对象所需的内存
             * 2、在分配的内存初始化Singleton_2类型对象
             * 3、把分配的内存的地址赋给指针m_instance
             *
             * 这里步骤1是肯定最先执行的，由但于编译器的问题（C++98），可能会发生 new 操作指令内存reoder，导致步骤2和步骤3的顺序并不一定
             * 加入线程A的执行顺序是 1，3，2,在执行到步骤3时，此时m_instance不再为空（nullptr）,这是就切换到了线程B
             * 而由于m_instance不为空，所以线程B会直接返回m_instance，而不会再次创建实例,但这个Singleton_2类型对象并没有真正被构造
             * 所以，就出现了Bug
             *
             * 针对这个问题，java和C#中都提供了volatile关键字，在声明m_instance时加上volatile修饰
             * 编译器看到后，就知道这个地方不能reorder(一定按步骤1，2，3的顺序执行)
             *
             * 对于C++，在C++11标准中，提供了原子操作，即atomic：
             * std::atomic<Singleton_2*> Singleton_2::m_instance;
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


// ----------------------------------------------------------解法三------------------------------------------------------
/* 解法三：饿汉式单例（线程安全）
 * 程序刚开始运行时就立即进行初始化，也称为预初始化
 * 缺点：在程序运行时，会占用内存，影响程序性能
 * */
class Singleton_3
{
private:
    Singleton_3()
    {
        cout << "Singleton_3 created" << endl;
    }
    const static Singleton_3* m_instance;
public:
    // 如果这里一直调用，返回的一直是已经被初始化的静态实例，是同一个地址
    const static Singleton_3* getInstance()
    {
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
};
// 饿汉式单例的静态实例初始化，有主线程以单线程方式完成，所以不会出现线程安全问题
const Singleton_3* Singleton_3::m_instance = new Singleton_3();

void print_singleton_address_3()
{
    const Singleton_3* s = Singleton_3::getInstance();
    cout << "Singleton_3 address: " << s << endl;
}

void test_3_1()
{
    cout << "---------------------------------------------test_3_1 多线程测试--------------------------------------------" << endl;
    vector<std::thread> threads;
    // 10个线程进行创建单例实例，结果都指向同一个地址
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(print_singleton_address_3));
    }
    for (auto& thr : threads) {
        thr.join();
    }
}

// ----------------------------------------------------------解法四------------------------------------------------------
/* 针对解法二的问题做一个优化：
 * atexit函数：在进程结束后调用回调函数来释放堆空间：
 * int atexit(void (*func)(void));
 * 利用这一特性，在进程结束时，atexit函数调用销毁函数，完成析构工作
 *
 * 针对new操作，导致内存指针reorder的问题，可以通过C++11的std::atomic来解决：
 * std::atomic<Singleton_4*> Singleton_4::m_instance;
 * .load()：用于从原子变量中读取数据，并且保证读取操作时原子性的，不会被其他线程打断
 * .store()：用于将一个值原子性地存储到原子变量中，保证在写入地过程中，不会有其他线程读取到不完整的值
 * 可见性：用load读取值，如果之前是另外一个线程用store设置的，则读取的值的可见的，即读取线程可以看到写入线程的更新
 *        用store写入值，根据所使用的内存序，保证对其他线程的可见性。
 *
 * 几种内存序：
 * 1、memory_order_seq_cst: 顺序一致性，既保证操作的顺序性，也保证数据的可见性，是最严格的内存序
 * 2、memory_order_acquire: 获取内存，用于读操作，保证读操作是原子的，并且读操作不会被其他线程打断，保证数据的可见性
 * 3、memory_order_release: 释放内存，用于写操作，保证写操作是原子的，并且写操作不会被其他线程打断，保证数据的可见性
 * 4、memory_order_relaxed: 放松顺序，不保证操作的顺序性
 *
 * 而std::atomic_thread_fence()函数，用于内存屏障(内存栅栏)，用于强制执行内存序，保证内存操作的顺序性
 * 内存屏障确保在该屏障前后的内存访问指令不会被便起义或处理器重排序，从而保证内存操作的顺序性
 * 可以搭配不能的内存序操作，来实现不同的内存屏障效果
 *
 * */

class Singleton_4
{
private:
    Singleton_4()
    {
        cout << "Singleton_4 created" << endl;
    }
    ~Singleton_4()
    {
        cout << "Singleton_4 destroyed" << endl;
    }
    // 禁止拷贝构造和赋值运算符
    Singleton_4(const Singleton_4&) = delete;
    Singleton_4& operator=(const Singleton_4&) = delete;
    // 禁止移动构造和移位赋值运算符
    Singleton_4(Singleton_4&&) = delete;
    Singleton_4& operator=(Singleton_4&&) = delete;

    static std::atomic<Singleton_4*> m_instance;
    static std::mutex m_mutex;

    static void destroyInstance()
    {
        if (m_instance != nullptr)
        {
            Singleton_4* tmp = m_instance.load(std::memory_order_acquire);
            if (tmp != nullptr)
            {
                delete tmp;
                tmp = nullptr;
                std::atomic_thread_fence(std::memory_order_release);
                m_instance.store(nullptr, std::memory_order_release);
            }
        }
    }

public:
    static Singleton_4* getInstance()
    {
        Singleton_4* tmp = m_instance.load(std::memory_order_relaxed);
        // 获取内存屏障
        std::atomic_thread_fence(std::memory_order_acquire);
        if (tmp == nullptr)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            tmp = m_instance.load(std::memory_order_relaxed);
            if (tmp == nullptr)
            {
                tmp = new Singleton_4();
                // 释放内存屏障
                std::atomic_thread_fence(std::memory_order_release);
                m_instance.store(tmp, std::memory_order_relaxed);
                atexit(destroyInstance);
            }
        }
        return tmp;
    }
};

std::atomic<Singleton_4*> Singleton_4::m_instance(nullptr);
std::mutex Singleton_4::m_mutex;

void print_singleton_address_4()
{
    Singleton_4* s = Singleton_4::getInstance();
    cout << "Singleton_4 address: " << s << endl;
}

void test_4_1()
{
    cout << "---------------------------------------------test_4_1 多线程测试--------------------------------------------" << endl;
    vector<std::thread> threads;
    // 10个线程进行创建单例实例，结果都指向同一个地址
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(print_singleton_address_4));
    }
    for (auto& thr : threads) {
        thr.join(); // 阻塞主线程，等待所有线程执行完毕
    }
}

// ----------------------------------------------------------解法五------------------------------------------------------
/* 解法五: 解法四虽然安全，但写法和实现都比较复杂，可利用特定函数控制实例创建只执行一次
 *        比如Linux中的pthread_once()函数,和C++11的std::call_once()函数
 *
 * pthread_once()函数的原型如下：
 * pthread_once(pthread_once_t *once_control, void (*init_routine)(void));
 * 该函数的第一个参数once_control是一个指针，用于标识某个函数是否已经执行过，一般为PTHREAD_ONCE_INIT宏定义，表示未执行过
 * 第二个参数init_routine是一个函数指针，用于初始化某个函数, 即用于创建单例实例的初始化函数
 * pthread_once()函数保证init_routine只被执行一次，并且保证线程安全,但只在Linux环境中，无法跨平台

 * C++11的std::call_once()函数的原型如下：
 * template<class Callable, class... Args>
 * void call_once(std::once_flag& flag, Callable&& func, Args&&... args);
 * 该函数的第一个参数flag是一个std::once_flag类型，用于标识某个函数是否已经执行过，一般为std::once_flag()，表示未执行过
 * 第二个参数func是一个可调用对象，用于初始化某个函数, 即用于创建单例实例的初始化函数
 * 第三个参数args是可变参数，用于传递给func的参数
 * std::call_once()函数保证func只被执行一次，并且保证线程安全，可跨平台
 */

class Singleton_5
{
public:
    static Singleton_5* getInstance()
    {
        std::call_once(m_flag, []() {
            m_instance = new Singleton_5();
        });
        return m_instance;
    }

private:
    Singleton_5()
    {
        cout << "Singleton_5 created" << endl;
    }
    ~Singleton_5()
    {
        cout << "Singleton_5 destroyed" << endl;
    }
    // 禁止拷贝构造和赋值运算符
    Singleton_5(const Singleton_5&) = delete;
    Singleton_5& operator=(const Singleton_5&) = delete;
    // 禁止移动构造和移位赋值运算符
    Singleton_5(Singleton_5&&) = delete;
    Singleton_5& operator=(Singleton_5&&) = delete;

    static std::once_flag m_flag;
    static Singleton_5* m_instance;

};
Singleton_5* Singleton_5::m_instance = nullptr;
std::once_flag Singleton_5::m_flag;

void print_singleton_address_5()
{
    Singleton_5* s = Singleton_5::getInstance();
    cout << "Singleton_5 address: " << s << endl;
}

void test_5_1() {
    cout << "------------------------------------------------test_5_1 多线程测试-----------------------------------------"
         << endl;
    vector<std::thread> threads;
    // 10个线程进行创建单例实例，结果都指向同一个地址
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(print_singleton_address_5));
    }
    for (auto &thr: threads) {
        thr.join(); // 阻塞主线程，等待所有线程执行完毕
    }
}

// ----------------------------------------------------------解法六------------------------------------------------------
/* 解法六: 利用C++11的 magic static 特性，称为Meyers Singleton,即简单又安全的单例模式实现
 *        核心思想是：利用局部静态变量的特性，来保证单例的延迟初始化和线程安全
 *        静态局部变量，只有在首次定义定义它的函数时才被构造，之后的调用都直接跳过，返回同一实例
 *        C++11 标准规定，局部静态变量的初始化过程时线程安全的，这意味着在多线程下，局部静态变量的构造只会执行一次
 *        如果构造函数异常，局部静态的析构函数也会被执行，保证了单例的完整性
 *
 *        优点：
 *        延迟加载
 *        系统自动调用析构，回收内存
 *        没有加锁和new操作，实现简单，效率高
 *        线程安全
 *
 *        gcc4.0及之后的版本支持
 *        C++11及之后的标准支持
 * */
class Singleton_6
{
private:
    Singleton_6()
    {
        cout << "Singleton_6 created" << endl;
    }
    ~Singleton_6()
    {
        cout << "Singleton_6 destroyed" << endl;
    }
    // 禁止拷贝构造和赋值运算符
    Singleton_6(const Singleton_6&) = delete;
    Singleton_6& operator=(const Singleton_6&) = delete;

    // 禁止移动构造和移位赋值运算符
    Singleton_6(Singleton_6&&) = delete;
    Singleton_6& operator=(Singleton_6&&) = delete;

public:
    static Singleton_6& getInstance()
    {
        // 局部静态变量，只有在首次定义定义它的函数时才被构造，之后的调用都直接跳过，返回同一实例
        static Singleton_6 instance;
        return instance;
    }
};

void print_singleton_address_6()
{
    Singleton_6& s = Singleton_6::getInstance();
    cout << "Singleton_6 address: " << &s << endl;
}

void test_6_1() {
    cout << "---------------------------------------------test_6_1 多线程测试--------------------------------------------" << endl;
    vector<std::thread> threads;
    // 10个线程进行创建单例实例，结果都指向同一个地址
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(print_singleton_address_6));
    }
    for (auto &thr: threads) {
        thr.join(); // 阻塞主线程，等待所有线程执行完毕
    }
}

int main() {
    test_1_1();
    test_1_2();
    test_2_1();
    test_3_1();
    test_4_1();
    test_5_1();
    test_6_1();

    return 0;
}