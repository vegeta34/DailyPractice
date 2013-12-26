/*在二元树中找出和为某一值的所有路径（树）
题目：输入一个整数和一棵二元树。
从树的根结点开始往下访问一直到叶结点所经过的所有结点形成一条路径。
打印出和与输入整数相等的所有路径。
例如 输入整数22和如下二元树
    10  
  /   /   
 5    12   
/ \     
4  7
则打印出两条路径：10, 12和10, 5, 7*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> path;

struct BinaryTreeNode // a node in the binary tree
{
	int data; // value of node
	BinaryTreeNode *left; // left child of node
	BinaryTreeNode *right; // right child of node
};

void AddNewNode(BinaryTreeNode *&root, BinaryTreeNode *p)
{
	if(root==nullptr)
		root=p;
	else{
		BinaryTreeNode *q=root;
		while(1)
		{
			if(p->data<q->data)
			{
				if(q->left==nullptr)
				{
					q->left=p;
					break;
				}
				else q=q->left;
			}
			else{
				if(q->right==nullptr)
				{
					q->right=p;
					break;
				}
				else q=q->right;
			}
		}
	}
}
void SetupTree(BinaryTreeNode *&root)
{
	int n;
	cin>>n;
	while(n--)
	{
		BinaryTreeNode *p=new BinaryTreeNode;
		cin>>p->data;
		p->left=p->right=nullptr;
		AddNewNode(root,p);
	}
}
void FindPath(BinaryTreeNode *root, int value)
{
	if(value==root->data)
	{
		for(int i=0;i<path.size();i++)
			cout<<path[i]<<" ";
		cout<<root->data<<endl;
		return;
	}
	else if(value<root->data)
		return;
	path.push_back(root->data);
	if(root->left)
		FindPath(root->left,value-root->data);
	if(root->right)
		FindPath(root->right,value-root->data);
	path.pop_back();
}

int main()
{
	BinaryTreeNode *root=nullptr;
	SetupTree(root);
	int value;
	cin>>value;
	FindPath(root,value);
	return 0;
}