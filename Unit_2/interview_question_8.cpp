/***********************************************
* @author:  ReLesEason
* @date:    2024/6/8 15:07
* @version: 1.0
* @description: interview question 8
************************************************/


/* Detailed Description
 * 题目：给定一颗二叉树和其中的一个结点，如果找出中序遍历序列的下一个结点？
 * 树中的节点除了有两个分别指向左、右子节点的指针，还有一个指向父节点的指针
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode * parent;
    TreeNode * left;
    TreeNode * right;

    TreeNode(int val):val(val),parent(nullptr),left(nullptr),right(nullptr){}
};

/* 多重条件判断
 * */
class Solution_1
{
public:
    TreeNode* func(TreeNode * node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->right!= nullptr)
        {
            TreeNode * temp = node->right;
            while(temp->left != nullptr)
            {
                temp = temp->left;
            }
            return temp;
        }

        if(node == node->parent->left && node->right == nullptr)
        {
            return node->parent;
        }
        if(node == node->parent->right && node->left == nullptr && node->right == nullptr)
        {
            TreeNode * temp = node;
            while(temp->parent!= nullptr)
            {
                temp = temp->parent;
            }
            return temp;

        }
        if(node == node->parent->right && node->right == nullptr)
        {
            cout<<"中序遍历的最后一个元素,没有下个结点"<<endl;
            return nullptr;
        }
    }
};

void test_1()
{
    cout<<"---------------------------------------------------test_1----------------------------------------------------"<<endl;
    TreeNode * root = new TreeNode(1);
    TreeNode * root_left= new TreeNode(2);
    TreeNode * root_left_left= new TreeNode(4);
    TreeNode * root_left_right= new TreeNode(5);

    TreeNode * root_right= new TreeNode(3);
    TreeNode * root_right_left= new TreeNode(6);
    TreeNode * root_right_left_left= new TreeNode(7);

    root->parent = nullptr;
    root->left = root_left;
    root->left->left = root_left_left;
    root->left->right = root_left_right;

    root->right = root_right;
    root->right->left = root_right_left;
    root->right->left->left = root_right_left_left;

    root_left->parent =root;
    root_left->left = root->left->left;
    root_left->right = root_left_right;

    root_left_left->parent = root_left;
    root_left_right->parent = root_left;

    root_right->parent = root;
    root_right->left = root_right_left;

    root_right_left->parent = root_right;
    root_right_left->left = root_right_left_left;

    root_right_left_left->parent = root_right_left;

    Solution_1 solution1;
    TreeNode * findNode = root_right_left   ;
    if (solution1.func(findNode))
    {
        cout<<solution1.func(findNode)->val<<endl;
    }

}

/* 根据中序遍历的特性进行判断
 * */
class Solution_2
{
public:
    TreeNode * func(TreeNode * node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        TreeNode * resultNode = nullptr;

        // 如果该结点有右子树，则后一个结点要不是该右结点，要不是右子树的最左下角结点
        if(node->right != nullptr)
        {
            TreeNode * temp = node->right;
            while(temp->left!= nullptr)
            {
                temp = temp->left;
            }
            resultNode = temp;
        }


        // 如果该结点没有右子树，但存在双亲结点,将该结点往上变，当变父结点的左结点时，此时的父结点就是下个结点
        if(node->parent != nullptr)
        {
            TreeNode * curNode = node;
            TreeNode * parNode = node->parent;
            while(parNode!= nullptr && curNode == parNode->right)
            {
                curNode = parNode;
                parNode = parNode->parent;
            }
            resultNode = parNode;
        }
    }
};
void test_2()
{
    cout<<"---------------------------------------------------test_2----------------------------------------------------"<<endl;
    TreeNode * root = new TreeNode(1);
    TreeNode * root_left= new TreeNode(2);
    TreeNode * root_left_left= new TreeNode(4);
    TreeNode * root_left_right= new TreeNode(5);

    TreeNode * root_right= new TreeNode(3);
    TreeNode * root_right_left= new TreeNode(6);
    TreeNode * root_right_left_left= new TreeNode(7);

    root->parent = nullptr;
    root->left = root_left;
    root->right = root_right;

    root_left->parent = root;
    root_left->left = root_left_left;
    root_left->right = root_left_right;

    root_left_left->parent = root_left;
    root_left_right->parent = root_left;

    root_right->parent = root;
    root_right->left = root_right_left;

    root_right_left->parent = root_right;
    root_right_left->left = root_right_left_left;

    root_right_left_left->parent = root_right_left;

    Solution_1 solution2;
    TreeNode * findNode = root_left_left   ;
    if (solution2.func(findNode))
    {
        cout<<solution2.func(findNode)->val<<endl;
    }

}

int main() {
    test_1();
    test_2();

    return 0;
}