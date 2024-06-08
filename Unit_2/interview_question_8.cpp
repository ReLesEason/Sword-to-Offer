/***********************************************
* @author:  ReLesEason
* @date:    2024/6/8 15:07
* @version: 1.0
* @description: interview question 8
************************************************/


/* Detailed Description
 * ��Ŀ������һ�Ŷ����������е�һ����㣬����ҳ�����������е���һ����㣿
 * ���еĽڵ�����������ֱ�ָ�������ӽڵ��ָ�룬����һ��ָ�򸸽ڵ��ָ��
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

/* ���������ж�
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
            cout<<"������������һ��Ԫ��,û���¸����"<<endl;
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

/* ����������������Խ����ж�
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

        // ����ý���������������һ�����Ҫ���Ǹ��ҽ�㣬Ҫ�����������������½ǽ��
        if(node->right != nullptr)
        {
            TreeNode * temp = node->right;
            while(temp->left!= nullptr)
            {
                temp = temp->left;
            }
            resultNode = temp;
        }


        // ����ý��û����������������˫�׽��,���ý�����ϱ䣬���丸��������ʱ����ʱ�ĸ��������¸����
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