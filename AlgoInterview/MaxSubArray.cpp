/*������������ͣ����飩
��Ŀ��
����һ���������飬������������Ҳ�и�����
������������һ�������������һ�������飬ÿ�������鶼��һ���͡�
������������ĺ͵����ֵ��Ҫ��ʱ�临�Ӷ�ΪO(n)��
�������������Ϊ1, -2, 3, 10, -4, 7, 2, -5��������������Ϊ3, 10, -4, 7, 2��
������Ϊ��������ĺ�18��*/
#include <iostream>
#include <vector>
using namespace std;

int get_max_sub(vector<int> a)
{
	int ret=a[0],tmp=a[0];
	for(int i=1;i<a.size();i++)
	{
		if(tmp>=0)
			tmp+=a[i];
		else tmp=a[i];
		ret=ret>tmp?ret:tmp;
	}
	return ret;
}

int main()
{
	int n;
	cin>>n;
	vector<int> arr(n);
	for(int i=0;i<n;i++)
		cin>>arr[i];
	cout<<get_max_sub(arr)<<endl;
	return 0;
}