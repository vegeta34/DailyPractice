#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE=1000001;
const int mod=1000000007;
vector<long long> dp;

long long ways(int m,int n)
{
	long long ret=1;
	long long ad=m-1;
	for(int i=1;i<n;i++)
	{
		ret+=ad++;
		if(ret>=mod)
			ret%=mod;
	}
	return ret;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	int t,m,n;
	cin>>t;
	while(t--)
	{
		cin>>m>>n;
		cout<<ways(m,n)<<endl;
	}
    return 0;
}
