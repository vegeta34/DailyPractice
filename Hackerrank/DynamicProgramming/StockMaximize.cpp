#include <iostream>
#include <vector>
#include <stack>
using namespace std;

long long max_stock(vector<long long> pac)
{
	stack<int> s;
	long long sum=0;
	s.push(0);
	for(int i=1;i<pac.size();i++)
	{
		while(!s.empty()&&pac[s.top()]<pac[i])
		{
			int last_max=s.top();
			s.pop();
			if(s.empty())
				sum+=(long long)(last_max+1)*(pac[i]-pac[last_max]);
			else sum+=(long long)(last_max-s.top())*(pac[i]-pac[last_max]);
		}
		s.push(i);
	}
	return sum;
}

int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		vector<long long> packages(n);
		for(int i=0;i<n;i++)
			cin>>packages[i];
		cout<<max_stock(packages)<<endl;
	}
	return 0;
}