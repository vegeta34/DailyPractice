/*https://www.hackerrank.com/challenges/billboards*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE=100000;
//long long dp[MAX_SIZE];        //dp[i] means max profit from 0 to i
vector<long long> profit(MAX_SIZE);
long long get_max(int n, int k)
{
	vector<pair<int, long long> > max;
	max.push_back(pair<int, long long>(0,0));
	long long ret=0;
	for(int i=0;i<n;i++)
	{
		vector<pair<int, long long> > curmax;
		curmax.push_back(pair<int, long long>(0,ret));
		if(profit[i]!=0){
			for(int j=0;j<max.size();j++)
			{
				long long v = profit[i]+max[j].second;
				if(v > curmax[curmax.size()-1].second)
				{
					if(max[j].first + 1 < k)
						curmax.push_back(pair<int, long long>(max[j].first + 1, v));
					ret=v>ret?v:ret;
				}
			}
		}
		max=curmax;
	}
	return ret; 
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	int n,k;
	//cin>>n>>k;
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++)
		//cin>>profit[i];
		scanf("%I64d", &profit[i]);
	cout<<get_max(n,k);
    return 0;
}
