/*�ڶ�Ԫ�����ҳ���Ϊĳһֵ������·��������
��Ŀ������һ��������һ�ö�Ԫ����
�����ĸ���㿪ʼ���·���һֱ��Ҷ��������������н���γ�һ��·����
��ӡ����������������ȵ�����·����
���� ��������22�����¶�Ԫ��
    10  
  /   /   
 5    12   
/ \     
4  7
���ӡ������·����10, 12��10, 5, 7*/

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