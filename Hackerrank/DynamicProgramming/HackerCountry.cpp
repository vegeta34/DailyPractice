#include <iostream>
#include <vector>
using namespace std;
const int MAX_N=501, MAX_DIST=200;
const int INF=100005;
int map[MAX_N][MAX_N];
int dist[MAX_N][MAX_N][MAX_N];
int roads[MAX_N][MAX_N];
vector<int> prime;

void init_prime(int upper)
{
    vector<bool> arr(upper+1);
    for(int i=0;i<=upper;i++)
        arr[i]=true;
    for(int i=2;i*i<=upper;i++)
    {
        if(arr[i])
        {
            for(int j=i*i;j<=upper;j+=i)
                arr[j]=false;
        }
    }
    for(int i=2;i<=upper;i++)
    {
        if(arr[i])
            prime.push_back(i);
    }
}
void floyd_dp(int n)
{    
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			dist[i][j][0]=map[i][j];
			if(!dist[i][j][0])
				dist[i][j][0]=INF;
			else roads[i][j]=1;
		}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(i==j)
					continue;
				dist[i][j][k]=dist[i][j][k-1];
				if(dist[i][k][k-1]+dist[k][j][k-1]<dist[i][j][k])
				{
					dist[i][j][k]=dist[i][k][k-1]+dist[k][j][k-1];
					roads[i][j]=k+1;
				}
			}
}
int m_dist,m_roads;
void travel_country(int n)
{
	double min_avg=200;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			m_dist=dist[i][j][n]+dist[j][i][n];
			m_roads=roads[i][j]+roads[j][i];
			double tmp=(double)m_dist/(double)m_roads;
			if(tmp<min_avg)
				tmp=min_avg;
		}
	}
	vector<int> p_num(prime.size());
	for(int i=0;i<prime.size()&&prime[i]<=m_roads;i++)
	{
		while(m_roads%prime[i]==0&&m_roads>1)
		{
			m_roads/=prime[i];
			p_num[i]++;
		}
	}
	for(int i=0;i<prime.size()&&prime[i]<=m_dist;i++)
	{
		while(m_dist%prime[i]==0&&m_dist>1&&p_num[i])
		{
			m_dist/=prime[i];
			p_num[i]--;
		}
	}
	for(int i=0;i<prime.size();i++)
	{
		while(p_num[i])
		{
			m_roads*=prime[i];
			p_num[i]--;
		}
	}
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>map[i][j];
	init_prime(MAX_DIST);
	floyd_dp(n);
	travel_country(n);
	cout<<m_dist<<'/'<<m_roads<<endl;
	return 0;
}