/***********************************************
* @author:  ReLesEason
* @date:    2024/6/4 20:09
* @version: 1.0
* @description: interview question 7
************************************************/


/* Detailed Description
 * 树
 * 通常为二叉树，在二叉树中最重要的莫过于遍历
 * 先序遍历(深度)
 * 中序遍历
 * 后序遍历
 *
 * 层次遍历（广度）
 *
 * 题目：重建二叉树
 */

#include <bits/stdc++.h>
using namespace std;

struct BinaryTreeNode
{
    int m_value;
    BinaryTreeNode * m_left;
    BinaryTreeNode * m_right;

    BinaryTreeNode(int value):m_value(value),m_left(nullptr),m_right(nullptr) {}
};

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);

/* 剑指offer 解法
 * */
class MyBinaryTree
{
public:

    BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
    {
        if(preorder == nullptr || inorder == nullptr || length <= 0)
            return nullptr;

        return ConstructCore(preorder, preorder + length - 1,
                             inorder, inorder + length - 1);
    }

    BinaryTreeNode* ConstructCore
            (
                    int* startPreorder, int* endPreorder,
                    int* startInorder, int* endInorder
            )
    {
        // 前序遍历序列的第一个数字是根结点的值
        int rootValue = startPreorder[0];
        BinaryTreeNode* root = new BinaryTreeNode(rootValue);


        // 划分成一个结点时
        if(startPreorder == endPreorder)
        {
            if(startInorder == endInorder && *startPreorder == *startInorder)
                return root;
            else
                cout<<"Invalid Input"<<endl;
        }

        // 在中序遍历中找到根结点的值
        int* rootInorder = startInorder;
        while(rootInorder <= endInorder && *rootInorder != rootValue)
            ++ rootInorder;

        // 在中序遍历中没找到根节点的值
        if(rootInorder == endInorder && *rootInorder != rootValue)
            cout<<"Invalid Input"<<endl;

        // 找到了，计算根节点左子树的长度
        int leftLength = rootInorder - startInorder;
        int* leftPreorderEnd = startPreorder + leftLength;
        if(leftLength > 0)
        {
            // 构建左子树
            root->m_left = ConstructCore(startPreorder + 1, leftPreorderEnd,
                                          startInorder, rootInorder - 1);
        }
        if(leftLength < endPreorder - startPreorder)
        {
            // 构建右子树
            root->m_right = ConstructCore(leftPreorderEnd + 1, endPreorder,
                                           rootInorder + 1, endInorder);
        }
        return root;
    }
};

void test_1()
{
    cout<<"------------------------------------------------------test_1------------------------------------------------"<<endl;
    const int length = 5;
    int preorder[length] = {1, 2, 3, 4, 5};
    int inorder[length] = {1, 2, 3, 4, 5};

    MyBinaryTree myBinaryTree;
    BinaryTreeNode * root = myBinaryTree.Construct(preorder,inorder,length);

    cout<<root<<endl;

    BinaryTreeNode * p_cur = root;
    while(p_cur != nullptr)
    {
        cout<<p_cur->m_value<<endl;
        p_cur = p_cur->m_right;
    }
}


struct TreeNode
{
    int val;
    TreeNode * left;
    TreeNode * right;

    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
    TreeNode(int x, TreeNode * left,TreeNode * right):val(x),left(left),right(right){}
};

/* 用hash表实现
 * */
class Solution
{
public:
    unordered_map<int,int> m;
    TreeNode * buildTree(vector<int> preorder,vector<int> inorder)
    {
        for(int i =0;i<inorder.size();i++)
        {
           m[inorder[i]] = i;
        }
        return build(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
    }
    TreeNode * build(vector<int> preorder, int preStart,int preEnd,vector<int>& inorder,int inStart,int inEnd)
    {
        if(preStart > preEnd)
        {
            return nullptr;
        }
        int rootVal = preorder[preStart];

        auto index = m.find(rootVal)->second;

        int leftSize = index - inStart;
        cout<<leftSize<<endl;

        TreeNode * root = new TreeNode(rootVal);

        root->left = build(preorder,preStart+1,preStart+leftSize,inorder,inStart,index-1);

        root->right = build(preorder,preStart+leftSize+1,preEnd,inorder,index+1,inEnd);

        return root;
    }

};

void test_2()
{
    cout<<"------------------------------------------------------test_2------------------------------------------------"<<endl;
    vector<int> preorder{1,2,3,4,5};
    vector<int> inorder{1,2,3,4,5};

    Solution solution;
    TreeNode * root = solution.buildTree(preorder,inorder);
    cout<<root<<endl;
    TreeNode * p_cur = root;
    while(p_cur != nullptr)
    {
        cout<<p_cur->val<<endl;
        p_cur = p_cur->right;
    }
}

/* 用vevtor实现
 * */
class Solution_2
{
public:
    TreeNode * build(vector<int>preorder,vector<int>inorder)
    {
        if(preorder.size() == 0 || inorder.size() ==0)
        {
            return nullptr;
        }
        TreeNode * root = new TreeNode(preorder[0]);

        int index = distance(inorder.begin(), find(inorder.begin(),inorder.end(),preorder[0]));

        vector<int>left_pre(preorder.begin()+1,preorder.begin()+index+1);
        vector<int>right_pre(preorder.begin()+index+1,preorder.end());
        vector<int>left_in(inorder.begin(),inorder.begin()+index);
        vector<int>right_in(inorder.begin()+index+1,inorder.end());

        root->left = build(left_pre,left_in);
        root->right = build(right_pre,right_in);

        return root;
    }


};

void test_3()
{
    cout<<"------------------------------------------------------test_3------------------------------------------------"<<endl;
    vector<int> preorder{1,2,3,4,5};
    vector<int> inorder{1,2,3,4,5};
    Solution_2 solution2;

    TreeNode * root = solution2.build(preorder,inorder);
    cout<<root<<endl;
    TreeNode * p_cur = root;
    while(p_cur != nullptr)
    {
        cout<<p_cur->val<<endl;
        p_cur = p_cur->right;
    }

}



int main() {
    test_1();
    test_2();
    test_3();


    return 0;
}