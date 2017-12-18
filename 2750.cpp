#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=1e9+7;
const int maxn=1e5+5;
const int INF=0x3f3f3f3f;
struct node
{
	int n,d;
	node(){}
	node(int n_,int d_)
	{
		n=n_;
		d=d_;
	}
	bool operator<(const node &tmp)const
	{
		return d>tmp.d;
	}
};
struct EdgeType
{
	int u,v,w;
};
struct EdgeType edge[maxn];
int n,m,head[maxn],E[maxn],V[maxn],W[maxn],cnt;
int V2[maxn],head2[maxn],E2[maxn],dis[maxn];
ll f[maxn],g[maxn],ans[maxn];
bool vis[maxn],visf[maxn],visg[maxn];
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
ll dfsf(int now)
{
	if(visf[now])
		return f[now];
	f[now]=0;
	visf[now]=true;
	for(int i=head2[now];i!=0;i=E2[i])
		if(dis[now]-W[i]==dis[V2[i]])
			(f[now]+=dfsf(V2[i]))%=mod;
	return f[now];
}
ll dfsg(int now)
{
	if(visg[now])
		return g[now];
	g[now]=1;
	visg[now]=true;
	for(int i=head[now];i!=0;i=E[i])
		if(dis[now]+W[i]==dis[V[i]])
			(g[now]+=dfsg(V[i]))%=mod;
	return g[now];
}
void solve(int s)
{
	std::priority_queue<node>que;
	for(int i=1;i<=n;i++)
	{
		dis[i]=INF;
		vis[i]=false;
		visf[i]=false;
		visg[i]=false;
	}
	dis[s]=0;
	que.push(node(s,0));
	node now;
	while(que.size()>0)
	{
		now=que.top();
		que.pop();
		if(vis[now.n])
			continue;
		vis[now.n]=true;
		for(int i=head[now.n];i!=0;i=E[i])
			if(dis[V[i]]>now.d+W[i])
			{
				dis[V[i]]=now.d+W[i];
				que.push(node(V[i],dis[V[i]]));
			}
	}
	f[s]=1;
	visf[s]=true;
	for(int i=1;i<=m;i++)
		if(dis[edge[i].u]+edge[i].w==dis[edge[i].v])
			(ans[i]+=dfsf(edge[i].u)*dfsg(edge[i].v)%mod)%=mod;
}
int main()
{
	//freopen("data.txt","r",stdin);
	read(n);
	read(m);
	for(int i=1,u,v,w;i<=m;i++)
	{
		read(u);
		read(v);
		read(w);
		edge[i].u=u;
		edge[i].v=v;
		edge[i].w=w;
		E[++cnt]=head[u];
		V[cnt]=v;
		W[cnt]=w;
		head[u]=cnt;
		E2[cnt]=head2[v];
		V2[cnt]=u;
		head2[v]=cnt;
	}
	for(int i=1;i<=n;i++)
		solve(i);
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
