/*��������нڵ��������...
������ǰѶ���������һ��ͼ�����ӽڵ�֮������߿�����˫��ģ�
���ǹ��Ҷ���"����"Ϊ���ڵ�֮��ߵĸ�����
дһ������
��һ�ö������������Զ�������ڵ�֮��ľ���*/

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