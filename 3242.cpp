#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll INF=1e18;
const ll maxn=1e5+5;

ll n,m,E[maxn<<1|1],V[maxn<<1|1],W[maxn<<1|1],cnt;
ll f[maxn],wi[maxn],dfn[maxn],tag,seq[maxn],num,Link;
ll head[maxn];

ll dis[maxn],ans1,ans2=INF,dp[maxn][2],pre[maxn],suf[maxn];
ll preVal[maxn],sufVal[maxn];

bool vis[maxn];

void tarjan(ll now)
{
	dfn[now]=++tag;
	for(ll i=head[now];i!=0;i=E[i])
		if(!dfn[V[i]])
		{
			f[V[i]]=now;
			wi[V[i]]=W[i];
			tarjan(V[i]);
		}
		else if(dfn[V[i]]>dfn[now])
		{
			ll t=V[i];
			while(t!=now)
			{
				seq[++num]=t;
				dis[num+1]=dis[num]+wi[t];
				t=f[t];
			}
			seq[++num]=now;
			Link=W[i];
		}
}

void dfs(ll now,ll fa)
{
	for(ll i=head[now];i!=0;i=E[i])
		if(!vis[V[i]]&&V[i]!=fa)
		{
			dfs(V[i],now);
			if(dp[V[i]][1]+W[i]>=dp[now][1])
			{
				dp[now][0]=dp[now][1];
				dp[now][1]=dp[V[i]][1]+W[i];
			}
			else if(dp[V[i]][1]+W[i]>dp[now][0])
				dp[now][0]=dp[V[i]][1]+W[i];
		}
	ans1=std::max(ans1,dp[now][1]+dp[now][0]);
}

int main()
{
//	freopen("foodshop.in","r",stdin);
//	freopen("foodshop.out","w",stdout);
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	std::cin>>n;
	for(ll i=1,u,v,w;i<=n;i++)
	{
		std::cin>>u>>v>>w;
		E[++cnt]=head[u];
		V[cnt]=v;
		W[cnt]=w;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		W[cnt]=w;
		head[v]=cnt;
	}
	tarjan(1);
	for(ll i=1;i<=num;i++)
		vis[seq[i]]=true;
	for(ll i=1;i<=num;i++)
		dfs(seq[i],0);
	pre[1]=dp[seq[1]][1];
	for(ll i=2;i<=num;i++)
		pre[i]=std::max(pre[i-1],dp[seq[i]][1]+dis[i]);
	suf[num]=dp[seq[num]][1];
	for(ll i=num-1;i>=1;i--)
		suf[i]=std::max(suf[i+1],dp[seq[i]][1]+dis[num]-dis[i]);
	preVal[1]=-INF;
	ll tmp=dp[seq[1]][1];
	for(ll i=2;i<=num;i++)
	{
		preVal[i]=std::max(preVal[i-1],tmp+dp[seq[i]][1]+dis[i]);
		tmp=std::max(tmp,dp[seq[i]][1]-dis[i]);
	}
	sufVal[num]=-INF;
	tmp=dp[seq[num]][1];
	for(ll i=num-1;i>=1;i--)
	{
		sufVal[i]=std::max(sufVal[i+1],tmp+dp[seq[i]][1]+dis[num]-dis[i]);
		tmp=std::max(tmp,dp[seq[i]][1]-dis[num]+dis[i]);
	}
	ans2=preVal[num];
	for(ll i=1;i<num;i++)
		ans2=std::min(ans2,std::max(pre[i]+suf[i+1]+Link,std::max(preVal[i],sufVal[i+1])));
	printf("%.1lf\n",std::max(ans1,ans2)/2.0);
	return 0;
}
