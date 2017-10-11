#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef unsigned long long ll;

const ll maxn=100005;

ll n,m,head[maxn],E[maxn<<2],V[maxn<<2],W[maxn<<2],cnt,dis[maxn],ai[maxn<<2],ins[maxn<<2],tot;

bool vis[maxn];

inline void read(ll &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

inline void edge_add(ll u,ll v,ll w)
{
	E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
	E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
}

void dfs(int now,int fa)
{
	vis[now]=true;
	for(int i=head[now];i;i=E[i])
		if(V[i]!=fa)
		{
			if(vis[V[i]]) ai[++tot]=dis[now]^dis[V[i]]^W[i];
			else dis[V[i]]=dis[now]^W[i],dfs(V[i],now);
		}
}

ll solve()
{
	for(ll i=1;i<=tot;i++)
		for(ll v=63;~v;v--)
			if((ai[i]>>v)&1)
				if(!ins[v])
				{
					ins[v]=ai[i];
					break;
				}
				else ai[i]^=ins[v];
	ll res=dis[n];
	for(ll i=63;~i;i--)
		if((res^ins[i])>res) res^=ins[i];
	return res;
}

int main()
{
	read(n),read(m);
	ll u,v,w;
	for(ll i=1;i<=m;i++)
	{
		read(u),read(v),read(w);
		edge_add(u,v,w);
	}
	dfs(1,0);
	std::cout<<solve();
	return 0;
}
