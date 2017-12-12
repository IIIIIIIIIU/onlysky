#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=12345678;
const int maxs=(1<<8)+1;
const int dx[9]={0,-1,-1,-1,0,1,1,1,0};
const int dy[9]={0,-1,0,1,1,1,0,-1,-1};

int n,m,Num,position[maxs],bit[15],px[15],py[15],Number,count[maxs];

char map[15][15];

ll ans[15],dp[29][maxs],Ans;

bool tmp_map[5][9];

inline bool cmp(int x,int y)
{
	for(int v=1;v<=8;v++)
		if(x+dx[v]>=1&&x+dx[v]<=n&&y+dy[v]<=m&&y+dy[v]>=1&&map[x+dx[v]][y+dy[v]]=='X')
			return false;
	return true;
}

void makeit(int s)
{
	memset(tmp_map,false,sizeof(tmp_map));
	count[s]=0;
	for(int i=1;i<=Number;i++)
		if(bit[i]&s)
		{
			tmp_map[px[i]][py[i]]=true;
			count[s]++;
		}
		else
		{
			for(int v=1;v<=8;v++)
				if(px[i]+dx[v]>0&&px[i]+dx[v]<=n&&py[i]+dy[v]>0&&py[i]+dy[v]<=m)
					tmp_map[px[i]+dx[v]][py[i]+dy[v]]=true;
			tmp_map[px[i]][py[i]]=true;
		}
	position[s]=0;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			if(!tmp_map[i][v])
				++position[s];
}

inline ll solve(int num)
{
	Number=0;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			if(map[i][v]=='X')
			{
				++Number;
				px[Number]=i;
				py[Number]=v;
			}
	for(int i=0;i<=(1<<num)-1;++i)
		makeit(i);
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(int i=0;i<n*m;i++)
		for(int s=0;s<(1<<num);++s)
		{
			if(position[s]-i+count[s]>0)
				(dp[i+1][s]+=dp[i][s]*(position[s]-i+count[s]))%=mod;
			for(int v=1;v<=num;v++)
				if(!(bit[v]&s))
					(dp[i+1][s|bit[v]]+=dp[i][s])%=mod;
		}
	return dp[n*m][(1<<num)-1];
}

void dfs(int x,int y,int num)
{
	if(x==n+1)
	{
		(ans[num]+=solve(num))%=mod;
		return;
	}
	if(map[x][y]=='X')
	{
		if(y==m)
			dfs(x+1,1,num+1);
		else
			dfs(x,y+1,num+1);
	}
	else if(cmp(x,y))
	{
		map[x][y]='X';
		if(y==m)
			dfs(x+1,1,num+1);
		else
			dfs(x,y+1,num+1);
		map[x][y]='.';
		if(y==m)
			dfs(x+1,1,num);
		else
			dfs(x,y+1,num);
	}
	else
	{
		if(y==m)
			dfs(x+1,1,num);
		else
			dfs(x,y+1,num);
	}
}

int main()
{
	bit[1]=1;
	for(int i=2;i<=15;i++)
		bit[i]=bit[i-1]<<1;
	std::cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",map[i]+1);
		for(int v=1;v<=m;v++)
			if(map[i][v]=='X')
				Num++;
	}
	dfs(1,1,0);
	for(int v=Num,e=1;v<=8;v++,e*=-1)
		(Ans+=ans[v]*e+mod)%=mod;
	std::cout<<(Ans+mod)%mod;
	return 0;
}
