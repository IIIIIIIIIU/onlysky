#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=500005;

struct node
{
	int id,dis;

	bool operator<(const node &tmp)const
	{
		return dis>tmp.dis;
	}

	node(int id_=0,int dis_=0)
	{
		id=id_,dis=dis_;
	}
};

int n,ai[maxn],mod,head[maxn],E[maxn<<5],V[maxn<<5],W[maxn<<5];
int cnt;

bool vis[maxn];

ll Bmin,Bmax,dis[maxn];

std::priority_queue<node>que;

void dijkstra()
{
	que.push(node(0,0));
	for(int i=2;i<=n;i++)
		if(ai[i]&&ai[i]<mod)
			que.push(node(ai[i],0)),dis[ai[i]]=0;
	node now;
	while(!que.empty())
	{
		now=que.top(),que.pop();
		if(vis[now.id]) continue;
		vis[now.id]=true;
		for(int i=head[now.id];i;i=E[i])
			if(dis[V[i]]>dis[now.id]+W[i])
			{
				dis[V[i]]=dis[now.id]+W[i];
				que.push(node(V[i],dis[V[i]]));
			}
	}
}

ll Calc(ll lit)
{
	ll res=0;
	for(int i=0;i<mod;i++)
		res+=std::max(0LL,lit/mod+(lit%mod>=i)-dis[i]);
	return res;
}

int main()
{
	std::cin>>n>>Bmin>>Bmax;
	for(int i=1;i<=n;i++) std::cin>>ai[i];
	std::sort(ai+1,ai+n+1);
	std::swap(ai[1],ai[n]);
	if(!ai[1])
	{
		std::cout<<0;
		return 0;
	}
	mod=ai[1];
	memset(dis,0x7f,sizeof(dis));
	dis[0]=0;
	int u,v,w;
	for(int i=0;i<mod;i++)
		for(int e=1;e<=n;e++)
		{
			if(!ai[e]) continue;
			w=(i+ai[e])/mod;
			v=(i+ai[e])%mod;
			u=i;
			E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
		}
	dijkstra();
	std::cout<<Calc(Bmax)-Calc(Bmin-1);
	return 0;
}
