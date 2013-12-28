/*给你10分钟时间，根据上排给出十个数，在其下排填出对应的十个数 
要求下排每个数都是先前上排那十个数在下排出现的次数。 
上排的十个数如下： 
【0，1，2，3，4，5，6，7，8，9】
举一个例子， 
数值: 0,1,2,3,4,5,6,7,8,9 
分配: 6,2,1,0,0,0,1,0,0,0 
0在下排出现了6次，1在下排出现了2次， 
2在下排出现了1次，3在下排出现了0次.... 
以此类推..*/

#include <iostream>
#include <vector>
using namespace std;

void GenerateArray2(vector<int> a1, vector<int> &a2)
{
	for(int i=0;i<a2.size();i++)
		a2[i]=0;
	bool success=false;
	while(!success)
	{
		success=true;
		for(int i=0;i<a1.size();i++)
		{
			int freq=0;
			for(int j=0;j<a2.size();j++)
			{
				if(a2[j]==a1[i])
					freq++;
			}
			if(freq!=a2[i])
			{
				a2[i]=freq;
				success=false;
			}
		}
	}
}

int main()
{
	int n;
	cin>>n;
	vector<int> arr1(n), arr2(n);
	for(int i=0;i<n;i++)
		arr1[i]=i;
	GenerateArray2(arr1,arr2);
	for(int i=0;i<n;i++)
		cout<<arr2[i]<<' ';
	return 0;
}