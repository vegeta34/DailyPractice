/*查找最小的k个元素（数组）
题目：输入n个整数，输出其中最小的k个。
例如输入1，2，3，4，5，6，7和8这8个数字，则最小的4个数字为1，2，3和4*/

#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &a, int begin, int end)
{
	int r=a[end];
	int j=begin;
	for(int i=begin;i<=end;i++)
	{
		if(a[i]<r)
		{
			int tmp=a[i];
			a[i]=a[j];
			a[j++]=tmp;
		}
	}
	a[end]=a[j];
	a[j]=r;
	return j;
}
void FindMinK(vector<int> &a, int begin, int end, int k)
{
	if(begin>=end)
		return;
	int q=partition(a,begin,end);
	if(k>q)
		FindMinK(a,q+1,end,k);
	else if(k<q-1)
		FindMinK(a,begin,q-1,k);
	else return;
}

int main()
{
	int n,k;
	cin>>n>>k;
	vector<int> arr(n);
	for(int i=0;i<n;i++)
		cin>>arr[i];
	FindMinK(arr,0,n-1,k);
	for(int i=0;i<k;i++)
		cout<<arr[i]<<' ';
	return 0;
}