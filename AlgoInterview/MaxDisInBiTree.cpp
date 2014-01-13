/*求二叉树中节点的最大距离...
如果我们把二叉树看成一个图，父子节点之间的连线看成是双向的，
我们姑且定义"距离"为两节点之间边的个数。
写一个程序，
求一棵二叉树中相距最远的两个节点之间的距离*/

#include <iostream>
using namespace std;

struct BSTNode{
	int data;
	BSTNode *left, *right;
};

void AddNewNode(BSTNode *&root, BSTNode *p)
{
	if(root==nullptr)
		root=p;
	else{
		BSTNode *q=root;
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
void SetupTree(BSTNode *&root)
{
	int n;
	cin>>n;
	while(n--)
	{
		BSTNode *p=new BSTNode;
		cin>>p->data;
		p->left=p->right=nullptr;
		AddNewNode(root,p);
	}
}

int max_dist=0;

int MaxDist(BSTNode *root)
{
	if(root==nullptr)
		return 0;
	int left_max=MaxDist(root->left);
	int right_max=MaxDist(root->right);
	if(left_max+right_max>max_dist)
		max_dist=left_max+right_max;
	return (left_max>right_max?left_max:right_max)+1;
}

int main()
{
	BSTNode *root=nullptr;
	SetupTree(root);
	MaxDist(root);
	cout<<max_dist<<endl;
	return 0;
}