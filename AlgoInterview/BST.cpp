/*�ж����������ǲ��Ƕ�Ԫ�������ĺ���������
��Ŀ������һ���������飬�жϸ������ǲ���ĳ��Ԫ�������ĺ�������Ľ����
����Ƿ���true�����򷵻�false��
��������5��7��6��9��11��10��8��������һ�����������������ĺ�����������
         8
      /  /
     6    10
    / /  / /
   5  7 9  11
��˷���true��
�������7��4��6��5��û���Ŀ����ĺ�������Ľ����������У���˷���false*/

#include <iostream>
#include <vector>
using namespace std;

bool check(vector<int> a, int begin, int end)
{
	if(begin>=end)
		return true;
	int i;
	for(i=begin;i<end;i++)
	{
		if(a[i]>a[end])
			break;
	}
	int j=i;
	while(j<end)
	{
		if(a[j++]<a[end])
			return false;
	}
	if(check(a,begin,i-1)&&check(a,i,end-1))
		return true;
	else return false;
}
int main()
{
	int n;
	cin>>n;
	vector<int> arr(n);
	for(int i=0;i<n;i++)
		cin>>arr[i];
	cout<<check(arr,0,n-1);
	return 0;
}