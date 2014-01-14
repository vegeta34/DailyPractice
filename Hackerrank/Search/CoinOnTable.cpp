/*https://www.hackerrank.com/challenges/coin-on-the-table*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX=50;
const int MAX_K=1000;
const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, -1, 0, 1 };
const char ch[] = { 'D', 'L', 'U', 'R' };
int star_x,star_y;

struct node{
	char dir;
	int in_queue_flag;
	int cost,k;
}table[MAX][MAX];

struct position{
	int x,y,cost;
	friend bool operator < (const position a, const position b)
    {
		return a.cost > b.cost;
    }
};

struct NodeCmp  
{  
    bool operator()(const position &na, const position &nb)  
    {
		return table[na.x][na.y].cost >= table[nb.x][nb.y].cost;
    }  
};
int bfs_path(int n, int m, int k)
{
	priority_queue<position> q;
	table[0][0].cost=0;
	position tmp;
	tmp.x=tmp.y=tmp.cost=0;
	q.push(tmp);
	table[0][0].in_queue_flag=1;
	table[0][0].k=k;
	while(!q.empty())
	{
		position p=q.top();
		q.pop();
		if(p.cost<table[p.x][p.y].cost)
			table[p.x][p.y].cost=p.cost;
		if(p.x==star_x&&p.y==star_y&&table[p.x][p.y].k>=0)
		{
			return table[p.x][p.y].cost;
		}
		else if(table[p.x][p.y].k==0)
			continue;
		for(int i=0;i<4;i++)
		{
			int x=p.x+dx[i];
			int y=p.y+dy[i];
			if(x<0||x>=n||y<0||y>=m)
				continue;
			int cost=table[p.x][p.y].dir==ch[i]?0:1;
			if(cost+table[p.x][p.y].cost<table[x][y].cost)
			{
				table[x][y].cost=cost+table[p.x][p.y].cost;
				table[x][y].k=table[p.x][p.y].k-1;
				tmp.x=x;
				tmp.y=y;
				tmp.cost=table[x][y].cost;
				q.push(tmp);				
			}
		}
	}
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>table[i][j].dir;
			table[i][j].in_queue_flag=0;
			table[i][j].cost=MAX_K;
			if(table[i][j].dir=='*')
			{
				star_x=i;
				star_y=j;
			}
		}
	}
	if(star_x + star_y > k)
		cout<<-1;
	else
		cout<<bfs_path(n,m,k);
    return 0;
}

