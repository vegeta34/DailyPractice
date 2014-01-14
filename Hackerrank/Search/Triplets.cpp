/*https://www.hackerrank.com/challenges/triplets*/

#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE=100001;
struct node{
	int val,pos;
    bool operator <(const node &a)const{
        return val<a.val;
    }
}a[MAX_SIZE];
int bit[MAX_SIZE], new_pos[MAX_SIZE],less_num[MAX_SIZE],larger_num[MAX_SIZE];

void bit_update(int idx, int val, int size)
{
	while (idx <= size){
		bit[idx] += val;
		idx += (idx & -idx);
	}
}
int bit_get_sum(int idx){
	int sum = 0;
	while (idx > 0){
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
	{
		cin>>a[i].val;
		a[i].pos=i;
	}
	a[0].val=-1;
	////////////////////////////////////////////////
    stable_sort(a+1,a+1+n);  //must use stable sort
	///////////////////////////////////////////////
    for(int i=1;i<=n;i++)
		new_pos[a[i].pos]=i;   //set new position
	//////////count nums less than a[new_pos[i]].val
	for(int i=1;i<=n;i++)
	{
		if(a[new_pos[i]].val!=a[new_pos[i]-1].val)
			bit_update(new_pos[i],1,n);
		less_num[i]=bit_get_sum(new_pos[i])-1;
		if(a[new_pos[i]].val==a[new_pos[i]-1].val)
			less_num[i]-=less_num[a[new_pos[i]-1].pos];    //remove duplicate from less
	}
	memset(bit,0,sizeof(int)*MAX_SIZE);
	//////////count nums larger than a[new_pos[i]].val
	larger_num[n]=0;
	bit_update(new_pos[n],1,n);
	for(int i=n-1;i>0;i--)
	{
		if(a[new_pos[i]].val!=a[new_pos[i]+1].val)
			bit_update(new_pos[i],1,n);
		larger_num[i]=bit_get_sum(n)-(a[new_pos[i]].val == a[new_pos[i]+1].val?bit_get_sum(new_pos[i]+1):bit_get_sum(new_pos[i]));
	}
	long long count=0;
	for(int i=2;i<n;i++)
	{
		count+=less_num[i]*larger_num[i];
	}
	cout<<count;
    return 0;
}
