/*https://www.hackerrank.com/challenges/task-scheduling*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
//#include <fstream>
using namespace std;

const int MAX_SIZE=100001;
int bit[MAX_SIZE]={0}, flag[MAX_SIZE];
int max_over=0, max_index=0, max_d=0;
void update(int idx, int val)
{
	while (idx < MAX_SIZE){
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
void get_min_max(int d, int m)
{
	update(d,m);
	if(!max_index)
	{
		max_over=m-d;
		max_index=d;
		return;
	}
	if(max_index>d)
	{
		int sum=get_sum(d);
		if(sum-d>max_over+m)
		{
			max_over=sum-d;
			max_index=d;
		}
		else
			max_over+=m;
		
	}
	else{
		for(int i=d;i<MAX_SIZE;i++)
		{
			if(!flag[i])
				continue;
			int _sum=get_sum(i);
			if(_sum-i>=max_over)
			{
				max_over=_sum-i;
				max_index=i;
			}
		}
	}
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	int t;
	cin>>t;
	//vector<int> ret;
	//ofstream outfile;
	//outfile.open("result.txt",ios::out);
	int tmp_d,tmp_m;
	for(int i=0;i<t;i++)
	{
		cin>>tmp_d>>tmp_m;
		flag[tmp_d]=1;
		get_min_max(tmp_d,tmp_m);
		cout<<(max_over>0?max_over:0)<<endl;
		//outfile<<(max_over>0?max_over:0)<<endl;
	}
	//outfile.close();
    return 0;
}
