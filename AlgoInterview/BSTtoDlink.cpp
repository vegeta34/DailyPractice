/*输入一棵二元查找树，将该二元查找树转换成一个排序的双向链表。
要求不能创建任何新的结点，只调整指针的指向。
   10
  / /
  6  14
  / / / /
  4  8 12 16
  转换成双向链表
  4=6=8=10=12=14=16。
  link:http://blog.csdn.net/v_JULY_v/article/details/6057286 */
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
void Convert(BSTNode *root, BSTNode *&head, BSTNode *&tail)
{
	BSTNode *left_tail=nullptr, *right_head=nullptr;
	if(root->left==nullptr)
		head=root;
	else Convert(root->left,head,left_tail);
	if(root->right==nullptr)
		tail=root;
	else Convert(root->right,right_head,tail);
	if(left_tail)
	{
		left_tail->right=root;
		root->left=left_tail;
	}
	if(right_head)
	{
		right_head->left=root;
		root->right=right_head;
	}
}
int main()
{
	BSTNode *root=nullptr, *head, *tail;
	SetupTree(root);
	Convert(root,head,tail);
	BSTNode *p=head;
	cout<<"From head to tail: ";
	while(p)
	{
		cout<<p->data<<' ';
		p=p->right;
	}
	cout<<endl;
	p=tail;
	cout<<"From tail to head: ";
	while(p)
	{
		cout<<p->data;
		p=p->left;
	}
	return 0;
}
