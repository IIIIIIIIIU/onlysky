#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e2+5;

struct EdgeType
{
	int v;
	
	EdgeType *next;
	
	EdgeType(){}
	
	EdgeType(int v_,EdgeType *next_)
	{
		v=v_;
		next=next_;
	}
};

struct EdgeType *head[maxn],edge[maxn*2];

int n,tot,dp[maxn][2][2],f[2][maxn],g[2][maxn];

inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

void dfs(int now,int fa)
{
	dp[now][0][0]=dp[now][0][1]=123456;
	dp[now][1][0]=dp[now][1][1]=123456;
	bool DID=true;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->v!=fa)
		{
			DID=false;
			dfs(i->v,now);
		}
	if(DID)
	{
		dp[now][0][0]=0;
		dp[now][1][1]=1;
		return;
	}
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	int last=0,Now=1,size=1;
	f[0][0]=0;//0
	g[0][0]=0;//1
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->v!=fa)
		{
			memset(g[Now],0x3f,sizeof(g[Now]));
			memset(f[Now],0x3f,sizeof(f[Now]));
			size++;
			for(int v=0;v<=size;v++)
			{
				f[Now][v]=std::min(f[Now][v],f[last][v]+dp[i->v][0][0]);
				g[Now][v]=std::min(g[Now][v],g[last][v]+dp[i->v][0][1]);
				if(v)
				{
					f[Now][v]=std::min(f[Now][v],f[last][v-1]+dp[i->v][1][0]);
					g[Now][v]=std::min(g[Now][v],g[last][v-1]+dp[i->v][1][1]);
				}
			}
			Now^=1;
			last^=1;
		}
	for(int i=0;i<=size;i++)
		if(i%2)
		{
			dp[now][0][1]=std::min(dp[now][0][1],g[last][i]);
			dp[now][1][0]=std::min(dp[now][1][0],f[last][i]+1);
		}
		else
		{
			dp[now][0][0]=std::min(dp[now][0][0],g[last][i]);
			dp[now][1][1]=std::min(dp[now][1][1],f[last][i]+1);
		}
}

int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	while(scanf("%d",&n)&&n)
	{
		for(int i=1;i<=n;i++)
			head[i]=NULL;
		tot=0;
		for(int i=1,u,v;i<n;i++)
		{
			read(u);
			read(v);
			edge[++tot]=EdgeType(v,head[u]);
			head[u]=&edge[tot];
			edge[++tot]=EdgeType(u,head[v]);
			head[v]=&edge[tot];
		}
		dfs(1,0);
		printf("%d\n",std::min(dp[1][0][1],dp[1][1][1]));
	}
	return 0;
}
