/*��ư���min������ջ��ջ��
����ջ�����ݽṹ��Ҫ�����һ��min�������ܹ��õ�ջ����СԪ�ء�
Ҫ����min��push�Լ�pop��ʱ�临�Ӷȶ���O(1)��*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class stack{
	vector<int> data;
	vector<int> min;
public:
	stack(){};
	~stack(){data.clear();};
	void push(int i)
	{
		if(!is_empty()&&i>top())
			min.push_back(top());
		else min.push_back(i);
		data.push_back(i);
	}
	void pop()
	{
		if(!is_empty())
		{
			data.pop_back();
			min.pop_back();
		}
	}
	int top()
	{
		return data[data.size()-1];
	}
	bool is_empty()
	{
		if(!data.size())
			return true;
		else return false;
	}
	int get_min()
	{
		return min[min.size()-1];
	}
};
int main()
{
	int n,tmp;
	string op;
	stack s;
	cin>>n;
	while(n--)
	{
		cin>>op;
		if(op=="pop")
			s.pop();
		else if(op=="push")
		{
			cin>>tmp;
			s.push(tmp);
		}
		cout<<"min is "<<s.get_min()<<endl;
	}
	return 0;
}