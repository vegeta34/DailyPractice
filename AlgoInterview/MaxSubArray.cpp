/*求子数组的最大和（数组）
题目：
输入一个整形数组，数组里有正数也有负数。
数组中连续的一个或多个整数组成一个子数组，每个子数组都有一个和。
求所有子数组的和的最大值。要求时间复杂度为O(n)。
例如输入的数组为1, -2, 3, 10, -4, 7, 2, -5，和最大的子数组为3, 10, -4, 7, 2，
因此输出为该子数组的和18。*/
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