/*判断整数序列是不是二元查找树的后序遍历结果
题目：输入一个整数数组，判断该数组是不是某二元查找树的后序遍历的结果。
如果是返回true，否则返回false。
例如输入5、7、6、9、11、10、8，由于这一整数序列是如下树的后序遍历结果：
         8
      /  /
     6    10
    / /  / /
   5  7 9  11
因此返回true。
如果输入7、4、6、5，没有哪棵树的后序遍历的结果是这个序列，因此返回false*/

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