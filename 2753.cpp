#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e5+5;
const int maxm=2e6+5;
int hi[maxn];
struct EdgeType
{
	int u,v,w;
	bool operator<(const EdgeType &tmp)const
	{
		if(hi[v]==hi[tmp.v])
			return w<tmp.w;
		return hi[v]>hi[tmp.v];
	}
};
struct EdgeType edge[maxm];
int n,m,head[maxn],E[maxm],V[maxm],cnt,que[maxn],f[maxn];
bool vis[maxn];
ll ans;
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
inline void edge_add(int u,int v,int w)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	head[v]=cnt;
}
inline void bfs()
{
	vis[1]=true;
	int h=0,tail=1,now;
	que[h]=1;
	while(h<tail)
		for(int i=head[now=que[h++]];i!=0;i=E[i])
			if(hi[now]>=hi[V[i]]&&!vis[V[i]])
			{
				vis[V[i]]=true;
				que[tail++]=V[i];
			}
}
inline int find(int x)
{
	if(x==f[x])
		return x;
	return f[x]=find(f[x]);
}
int main()
{
	//freopen("data.txt","r",stdin);
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
		read(hi[i]);
	int num=0;
	for(int i=1,u,v,w;i<=m;i++)
	{
		read(u);
		read(v);
		read(w);
		edge_add(u,v,w);
		edge[++num].u=u;
		edge[num].v=v;
		edge[num].w=w;
		edge[++num].u=v;
		edge[num].v=u;
		edge[num].w=w;
	}
	std::sort(edge+1,edge+num+1);
	bfs();
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1,u,v;i<=num;i++)
	{
		if(hi[edge[i].u]<hi[edge[i].v]||!vis[edge[i].u]||!vis[edge[i].v])
			continue;
		u=edge[i].u;
		v=edge[i].v;
		u=find(u);
		v=find(v);
		if(u!=v)
		{
			f[u]=v;
			ans+=edge[i].w;
		}
	}
	int ans2=0;
	for(int i=1;i<=n;i++)
		if(vis[i])
			ans2++;
	printf("%d %lld",ans2,ans);
	return 0;
}
