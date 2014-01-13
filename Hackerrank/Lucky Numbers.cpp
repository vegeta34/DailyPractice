/*problem site: https://www.hackerrank.com/challenges/lucky-numbers 
solution: http://stackoverflow.com/questions/9018614/algorithm-to-find-lucky-numbers */
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string.h>
using namespace std;
/* Head ends here */
const int MAX_LENGTH = 18;
int squares[10]={0,1,4,9,16,25,36,49,64,81};
bool prime[1500]={0};
long long dp[18][18*9+1][18*81+1]={0};
long long dp_count[18][10][18*9+1][18*81+1]={0};
vector<int> squ_pos[18][18*9+1];

void InitPrime()
{
	prime[2]=true;
	prime[3]=true;
	vector<int> plist;
	plist.push_back(2);
	plist.push_back(3);
	for(int i=5;i<81*18;i+=2)
	{
		int flag=0;
		for(int j=1;j<plist.size();j++)
		{
			if(i%plist[j]==0)
			{
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			prime[i]=true;
			plist.push_back(i);
		}
	}
}
void InitDptable()
{
	dp[0][0][0]=1;
	for(int i=0;i<MAX_LENGTH-1;i++){
		for(int j=0;j<=i*9;j++){
			for(int k=0;k<=i*81;k++){
				for(int l=0;l<10;l++)
					dp[i+1][j+l][k+squares[l]]+=dp[i][j][k];
			}
		}
	}
}
void InitSquPos()
{
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<18*9+1;j++)
		{
			for(int k=0;k<18*81+1;k++)
				if(dp[i][j][k])
					squ_pos[i][j].push_back(k);
		}
	}
}
long long CountMax(long long max)
{
	long long ret=0;
	vector<int> all_bits;
	while(max){
		all_bits.push_back(max%10);
		max/=10;
	}
	int sum=0, square_sum=0;
	for(int i=all_bits.size()-1;i>=0;i--)
	{
		for(int bit=0;bit<all_bits[i];bit++)
		{
			if(dp_count[i][bit][sum][square_sum]!=0)
			{
				ret+=dp_count[i][bit][sum][square_sum];
				continue;
			}
			int _sum=sum+bit, _square_sum=square_sum+squares[bit];
			for(int j=0;j<=9*i;j++)
			{
				if(prime[_sum+j])
				{
					for(int k=0;k<squ_pos[i][j].size();k++)
					{
						int tmp=squ_pos[i][j][k];
						if(prime[_square_sum+tmp])
						{
							ret+=dp[i][j][tmp];
							dp_count[i][bit][sum][square_sum]+=dp[i][j][tmp];
						}
					}
				}
			}
		}
		sum+=all_bits[i];
		square_sum+=squares[all_bits[i]];
	}
	if(prime[sum]&&prime[square_sum])
		ret++;
	return ret;
}

int main() {
	InitPrime();
	InitDptable();
	InitSquPos();
    int _cases,_a_i;
    long long _a,_b;
    scanf("%d", &_cases);
    for(_a_i = 0; _a_i < _cases; _a_i++) { 
        scanf("%lld %lld", &_a,&_b);
		if(_b==1000000000000000000ll)
			_b--;
		printf("%lld\n", CountMax(_b)-CountMax(_a-1));
    }
    return 0;
}

