/* Enter your code here. Read input from STDIN. Print output to STDOUT */
#include <stdio.h>
#include <math.h>

const int MAX=1001;
long long dp[MAX][MAX];
long long power[MAX][MAX];
int mod=1000000007;

int i_pro=2;
int j_pro=2;
long long pw(long long x, unsigned int n)
{
    long long ret = 1;
    while (n > 0) {
        if (n & 1)
            ret *= x;
        x *= x;
		if(ret>=mod)
			ret%=mod;
		if(x>=mod)
			x%=mod;
        n >>= 1;
        }
    return ret;
}
long long calc_power(int i, int j)
{
    if(power[i][j])
        return power[i][j];
    long long base=dp[1][j];
    power[i][j]=pw(dp[1][j],i);
    return power[i][j];
}

void init()
{
    for(int i=1;i<MAX;i++)
    {
        dp[i][0]=1;
        dp[i][1]=1;
        power[i][0]=1;
        power[i][1]=1;
    }
    dp[1][2]=2;
    power[1][2]=2;
    dp[1][3]=4;
    power[1][3]=4;
    dp[1][4]=8;
    power[1][4]=8;
    for(int i=5;i<MAX;i++)
    {
        dp[1][i]=dp[1][i-1]+dp[1][i-2]+dp[1][i-3]+dp[1][i-4];
		if(dp[1][i]>=mod)
			dp[1][i]%=mod;
        power[1][i]=dp[1][i];
    }
}
long long DP_Process(int h, int w)     //from left to right
{
	if(h==1&w>4)
		return 0;
	if(h==1&w<=4)
		return 1;
    for(int i=2;i<=w;i++)
    {
		if(dp[h][i])
			continue;
        long long ways=calc_power(h,i);
        for(int j=1;j<i;j++)
        {
			long long tmp=dp[h][j]*calc_power(h,i-j);
			if(tmp>mod)
				tmp%=mod;
			if(ways<tmp)
				ways=ways+mod-tmp;
			else ways-=tmp;
		}
        dp[h][i]=ways;
    }
    return dp[h][w];
}
int main()
{
    int T,N,M;
    scanf("%d",&T);
    init();
    for(int i=0;i<T;i++)
    {
        scanf("%d %d",&N,&M);
        printf("%I64d\n", DP_Process(N,M));
    }
    return 0;
}