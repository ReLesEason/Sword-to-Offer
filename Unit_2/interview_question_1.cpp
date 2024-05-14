//
// Created by User on 2024/5/14.
//


#include <bits/stdc++.h>
using namespace std;

/* 赋值运算符函数
 * 题目：如下为类型CMyString的声明，请为该类型添加赋值运算符函数
 * */
class CMyString
{
public:
    // 默认的构造函数
    CMyString(char* m_pData = nullptr);
    // 拷贝构造函数
    CMyString(const CMyString& str);
    // 析构函数
    ~CMyString(void);

    // 初级解法：
    CMyString& operator=(const CMyString& str);

    void print();

private:
    // 字符串的指针
    char* m_pData;  // c 语言的字符串定义风格
};

// 构造函数
CMyString::CMyString(char* pData)
{
    if (pData == nullptr)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int length = strlen(pData);
        m_pData = new char[length + 1];
        strcpy(m_pData, pData);
    }
}

// 拷贝构造函数
CMyString::CMyString(const CMyString& str)
{
    if (str.m_pData == nullptr)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int length = strlen(str.m_pData);
        m_pData = new char[length + 1];
        strcpy(m_pData, str.m_pData);
    }
}

// 析构函数
CMyString::~CMyString()
{
        delete[] m_pData;
        m_pData = nullptr;
}

/* 初级解法：
 * 值得注意的几个点：
 * 1、返回值的类型为该类型的引用，并在函数结束前返回实力自身的引用（*this）,以支持链式赋值操作
 * 2、检查传入的对象是否是自身，如果是直接返回当前对象的引用，这样可以避免无谓的消耗，同时避免释放自身内存后，再找不到所要赋值的内容了
 * 3、释放当前对象的内存，并重新申请内存，不然会出现内存泄漏。之后，再将传入对象的内容到新申请的内存中
 * */
CMyString& CMyString::operator=(const CMyString& str)
{
    // 检查传入的对象是否是自身，如果是直接返回当前对象的引用
    if (this == &str)
        return *this;

    // 这里要用delete[]，因为m_pDate是一个指向C语言风格的字符串数组指针
    // 如果用delete，只会释放指针指向的首地址元素，而不会释放字符串的其他元素
    delete[] m_pData;

    m_pData = nullptr;

    // strlen()用于计算以\0结尾的字符串长度，但不包含\0本身
    // 这里 + 1 的目的是为了后面拷贝时结尾仍然是\0
    m_pData = new char[strlen(str.m_pData) + 1];
    // 这里的strcpy()函数用于拷贝字符串，会自动将\0也拷贝到新申请的内存中
    strcpy(m_pData, str.m_pData);

    // 返回当前对象的引用
    return *this;

    /* 这里在分配内存之前先释放了实例 m_pData的内存，如果此时内存不足，将导致 new char 抛出异常
     * 此时，m_pData 已经指向了无效的内存，导致程序崩溃。
     * 因此，在分配内存之前，应该先检查是否有足够的内存，以避免出现这种问题。
     * */
}


/* 高级解法:
 * 1、先申请新内存，再释放已有的内容，这样当内存分配失败时，可以确保CMyString的实力不会被修改
 * 2、先创建一个临时实例，再交换临时实例和原来的实例
 * */
//CMyString& CMyString::operator=(const CMyString& str)
//{
//   if (this != &str)
//   {
//       // 拷贝构造函数
//       CMyString temp(str); // 临时实例——局部变量
//
//       // 交换临时实例和原来的实例，临时实例在该赋值函数结束后就会被释放
//       char * pTemp = temp.m_pData; // 临时指针
//       temp.m_pData = m_pData;
//       m_pData = pTemp;
//   }
//   return *this;
//}

void CMyString::print()
{
    cout << m_pData << endl;
}

/* =================================== 测试======================================= */
// 测试赋值运算符——如果不定义，直接赋值会报错：undefined reference to `CMyString::operator=(CMyString const&)'
void test_1()
{
    cout<<"test_1"<<endl;

    char* text = "Hello World";

    // 构造函数
    CMyString str1(text);

    // 赋值运算符函数
    CMyString str2;
    str2 = str1;  // 如果没有赋值运算符函数，则会报错：undefined reference to `CMyString::operator=(CMyString const&)'

    str2.print();
}

// 测试赋值给自己
void test_2()
{
    cout<<"test_2"<<endl;

    char* text = "Hello World";

    // 构造函数
    CMyString str1(text);

    str1 = str1;  // 赋值给自己

    str1.print();
}

// 测试链式赋值
void test_3() {
    cout << "test_3" << endl;

    char *text = "Hello World";

    // 构造函数
    CMyString str1(text);

    // 赋值运算符函数
    CMyString str2,str3;
    str3 = str2 = str1;

    str1.print();
    str2.print();
    str3.print();
}



int main() {

    test_1();
    test_2();
    test_3();

    return 0;
}