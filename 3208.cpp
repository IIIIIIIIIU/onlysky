#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=705;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};

int n,m,g[maxn][maxn],vis[maxn][maxn],f[maxn][maxn],tot;

bool tag[maxn][maxn];

inline void read(int now)
{
	char Cget;
	now=0;
	while(!isdigit(Cget=getchar()));
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

int dfs(int x,int y)
{
	if(vis[x][y]==tot)
		return f[x][y];
	f[x][y]=1;
	vis[x][y]=tot;
	for(int i=0,X,Y;i<4;i++)
	{
		X=x+dx[i];
		Y=y+dy[i];
		if(X>0&&X<=n&&Y>0&&Y<=n&&!tag[X][Y]&&g[X][Y]<g[x][y])
			f[x][y]=std::max(f[x][y],dfs(X,Y)+1);
	}
	return f[x][y];
}

int main()
{
	std::cin>>n;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			std::cin>>g[i][v];
	std::cin>>m;
	char op[3];
	int a,b,c,d;
	while(m--)
	{
		std::cin>>op;
		if(op[0]=='C')
		{
			std::cin>>a>>b>>c;
			g[a][b]=c;
		}
		else if(op[0]=='S')
		{
			std::cin>>a>>b>>c>>d;
			for(int i=a;i<=c;i++)
				for(int v=b;v<=d;v++)
					tag[i][v]=true;
		}
		else if(op[0]=='B')
		{
			std::cin>>a>>b>>c>>d;
			for(int i=a;i<=c;i++)
				for(int v=b;v<=d;v++)
					tag[i][v]=false;
		}
		else
		{
			++tot;
			int ans=0;
			for(int i=1;i<=n;i++)
				for(int v=1;v<=n;v++)
					if(!tag[i][v])
						ans=std::max(ans,dfs(i,v));
			std::cout<<ans<<std::endl;
		}
	}
	return 0;
}
