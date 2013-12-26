/*https://www.hackerrank.com/challenges/insertion-sort*/

#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_INT=1000000;
int bit[MAX_INT+1];
int max_num=0;

void update(int idx, int val)
{
	while (idx <= max_num){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}
int get_sum(int idx){
	int sum = 0;
	while (idx > 0){
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}
long long calc(vector<int> a)
{
	long long ret=0;
	for(int i=0;i<a.size();i++)
	{
		update(a[i],1);
		ret+=(long long)(i+1-get_sum(a[i]));
	}
	return ret;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	int t,n;
	cin>>t;
	vector<int> a;
	vector<long long>result;
	for(int i=0;i<t;i++)
	{
		cin>>n;
		max_num=0;
		for(int j=1;j<=n;j++)
		{
			int tmp;
			cin>>tmp;
			a.push_back(tmp);
			if(tmp>max_num)
				max_num=tmp;
		}
		memset(bit,0,sizeof(int)*(MAX_INT+1));
		result.push_back(calc(a));
		a.clear();
	}
	for(int i=0;i<t;i++)
		cout<<result[i]<<endl;
    return 0;
}

