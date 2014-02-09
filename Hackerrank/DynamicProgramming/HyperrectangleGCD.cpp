#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX_K=500;
const int MAX_N=100001;
const int mod=1000000007;
vector<int> nk;
vector<long long> log_num(MAX_N);
long long get_all_gcd()
{
	long long ret=0;
	for(int i=nk[0];i>=1;i--)
	{
		long long multi=1;
		for(int j=0;j<nk.size();j++)
		{
			multi*=(long long)(nk[j]/i);
			if(multi>=mod)
				multi%=mod;
		}
		for(int j=i+i;j<=nk[0];j+=i)
		{
			if(multi<log_num[j])
				multi=multi+mod-log_num[j];
			else multi-=log_num[j];
		}
		log_num[i]=multi;
		multi*=(long long)i;
		if(multi>=mod)
			multi%=mod;
		ret+=multi;
		if(ret>=mod)
			ret%=mod;
	}
	return ret;
}
int main()
{
	int t,k;
	cin>>t;
	while(t--)
	{
		cin>>k;
		int tmp;
		for(int i=0;i<k;i++)
		{
			cin>>tmp;
			nk.push_back(tmp);
		}
		sort(nk.begin(),nk.end());
		cout<<get_all_gcd()<<endl;
		nk.clear();
		log_num.clear();
	}
	return 0;
}