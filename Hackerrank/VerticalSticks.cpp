/*Problem: https://www.hackerrank.com/challenges/vertical-sticks
solution:Imagine a different problem: if you had to place k sticks of equal heights in n slots then the expected distance between sticks (and the expected distance between the first stick and a notional slot 0, and the expected distance between the last stick and a notional slot n+1) is (n+1)/(k+1) since there are k+1 gaps to fit in a length n+1.

Returning to this problem, a particular stick is interested in how many sticks (including itself) as as high or higher. If this is k, then the expected gap before it is also (n+1)/(k+1).
*/
#include <stdio.h>
#include <string.h>
const int MAX_LENGTH = 1000;
int arr[MAX_LENGTH+1];

double get_sum_perm(int n)
{
	double sum=0;
	int less_num=0;
	for(int i=1;i<=MAX_LENGTH;i++)
	{
		if(!arr[i])continue;
		int more_num=n-less_num;
        sum+=(double)(n+1)/(more_num+1)*arr[i];
        less_num+=arr[i];
	}
	return sum;
}

int main()
{
	int T;
	scanf("%d\n", &T);
	while(T--)
	{
		memset(arr,0,sizeof(int)*(MAX_LENGTH+1));
		int n,tmp;
		scanf("%d\n", &n);
		for(int i=0;i<n;i++)
		{
			scanf("%d", &tmp);
			arr[tmp]++;
		}
		printf("%.2f\n", get_sum_perm(n));
	}
	return 0;
}
