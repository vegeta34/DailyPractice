/*https://www.hackerrank.com/challenges/pairs*/

/* Enter your code here. Read input from STDIN. Print output to STDOUT */
#include <iostream>
using namespace std;

int partition(int *a, int b, int e)
{
	int r=a[e];
	int j=b;
	for(int i=b;i<e;i++)
	{
		if(a[i]<r)
		{
			int tmp=a[i];
			a[i]=a[j];
			a[j]=tmp;
			j++;
		}
	}
	a[e]=a[j];
	a[j]=r;
	return j;
}
void quick_sort(int *a, int b, int e)
{
	if(b>=e)
		return;
	int q=partition(a,b,e);
	quick_sort(a,b,q-1);
	quick_sort(a,q+1,e);
}

int SearchDiff(int *a, int len, int k)
{
	int ret=0;
	int begin=1;
	int end=len-1;
	int mid;
	for(int i=0;i<len;i++)
	{
		int tmp=a[i]+k;
		while(begin<=end)
		{
			mid=(begin+end)/2;
			if(tmp==a[mid])
				break;
			else if(tmp>a[mid])
				begin=mid+1;
			else
				end=mid-1;
		}
		if(tmp==a[mid])
		{
			ret++;
			begin=mid+1;
		}
		end=len-1;
	}
	return ret;
}

int main()
{
	int N,K;
	cin>>N>>K;
	int *arr=new int[N];
	for(int i=0;i<N;i++)
		cin>>arr[i];
	quick_sort(arr,0,N-1);
	cout<<SearchDiff(arr,N,K);
	return 0;
}
