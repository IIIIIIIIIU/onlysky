#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=505;

struct NodeType
{
	int id,val;

	bool operator<(const NodeType &tmp)const
	{
		return val>tmp.val;
	}

	NodeType(int id_=0,int val_=0)
	{
		id=id_,val=val_;
	}
};

std::priority_queue<NodeType>que;

int n,id[maxn][maxn],E[maxn*maxn*8],V[maxn*maxn*8],W[maxn*maxn*8],cnt,head[maxn*maxn];
int s,t,dis[maxn*maxn];

bool vis[maxn*maxn];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

inline void edge_add(int u,int v,int w)
{
	E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
}

void dijkstra()
{
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;
	que.push(NodeType(s,0));
	NodeType now;
	while(!que.empty())
	{
		now=que.top(),que.pop();
		if(vis[now.id]) continue;
		vis[now.id]=true;
		for(int i=head[now.id];i;i=E[i])
			if(dis[V[i]]>dis[now.id]+W[i])
			{
				dis[V[i]]=dis[now.id]+W[i];
				que.push(NodeType(V[i],dis[V[i]]));
			}
	}
}

int main()
{
//	freopen("altitude.in","r",stdin);
//	freopen("altitude.out","w",stdout);
	read(n);
	int tmp=0;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++) id[i][v]=++tmp;
	t=++tmp;
	for(int i=1;i<=n;i++) id[0][i]=id[i][n+1]=s,id[i][0]=id[n+1][i]=t;
	for(int i=0;i<=n;i++)
		for(int v=1;v<=n;v++)
			read(tmp),edge_add(id[i][v],id[i+1][v],tmp);
	for(int i=1;i<=n;i++)
		for(int v=0;v<=n;v++)
			read(tmp),edge_add(id[i][v+1],id[i][v],tmp);
	for(int i=0;i<=n;i++)
		for(int v=1;v<=n;v++)
			read(tmp),edge_add(id[i+1][v],id[i][v],tmp);
	for(int i=1;i<=n;i++)
		for(int v=0;v<=n;v++)
			read(tmp),edge_add(id[i][v],id[i][v+1],tmp);
	dijkstra();
	std::cout<<dis[t];
	return 0;
}
