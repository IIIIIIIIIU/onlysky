#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e9+7;
const int maxn=5e5+5;
const int maxtree=maxn<<2|1;

int L[maxtree],R[maxtree],mid[maxtree],Min[maxtree],Max[maxtree];
int n,du[maxtree],bel[maxtree],col,stack[maxtree],top,tag,id[maxn];
int Min2[maxtree],Max2[maxtree],dfn[maxtree],low[maxtree],tl,tr;
int head[maxtree],E[maxtree*21],V[maxtree*21],cnt;
int que[maxtree];

ll xi[maxn],ri[maxn],ans;

void build(int now,int l,int r)
{
	Min[now]=L[now]=l;
	Max[now]=R[now]=r;
	if(l==r)
	{
		id[l]=now;
		Min[now]=std::lower_bound(xi+1,xi+n+1,xi[l]-ri[l])-xi;
		Max[now]=std::upper_bound(xi+1,xi+n+1,xi[l]+ri[l])-xi-1;
		return;
	}
	mid[now]=(l+r)>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
}

void tarjan(int now);

void find(int now,int u)
{
	if(L[now]>=Min[u]&&R[now]<=Max[u])
	{
		if(!bel[now])
		{
			if(dfn[now])
				low[u]=std::min(low[u],dfn[now]);
			else
			{
				tarjan(now);
				low[u]=std::min(low[u],low[now]);
			}
		}
		return;
	}
	if(Min[u]<=mid[now])
		find(now<<1,u);
	if(Max[u]>mid[now])
		find(now<<1|1,u);
}

void tarjan(int now)
{
	stack[++top]=now;
	dfn[now]=low[now]=++tag;
	if(L[now]!=R[now])
	{
		if(!bel[now<<1])
		{
			if(dfn[now<<1])
				low[now]=std::min(low[now],dfn[now<<1]);
			else
			{
				tarjan(now<<1);
				low[now]=std::min(low[now],low[now<<1]);
			}
		}
		if(!bel[now<<1|1])
		{
			if(dfn[now<<1|1])
				low[now]=std::min(low[now],dfn[now<<1|1]);
			else
			{
				tarjan(now<<1|1);
				low[now]=std::min(low[now],low[now<<1|1]);
			}
		}
	}
	else
		find(1,now);
	if(low[now]==dfn[now])
	{
		col++;
		Min2[col]=Min[now];
		Max2[col]=Max[now];
		while(stack[top]!=now)
		{
			bel[stack[top]]=col;
			if(Min[stack[top]]<Min2[col])
				Min2[col]=Min[stack[top]];
			if(Max[stack[top]]>Max2[col])
				Max2[col]=Max[stack[top]];
			top--;
		}
		bel[now]=col;
		top--;
	}
}

void Tarjan(int now)
{
	if(!dfn[now])
		tarjan(now);
	if(L[now]==R[now])
		return;
	Tarjan(now<<1);
	Tarjan(now<<1|1);
}

inline void edge_add(int u,int v)
{
	if(bel[u]!=bel[v])
	{
		u=bel[u];
		v=bel[v];
		du[v]++;
		E[++cnt]=head[u];
		V[cnt]=v;
		head[u]=cnt;
	}
}

void Build2(int now,int u)
{
	if(L[now]>=Min[u]&&R[now]<=Max[u])
	{
		edge_add(now,u);
		return;
	}
	if(Min[u]<=mid[now])
		Build2(now<<1,u);
	if(Max[u]>mid[now])
		Build2(now<<1|1,u);
}

void Build(int now)
{
	if(L[now]==R[now])
	{
		Build2(1,now);
		return;
	}
	edge_add(now<<1,now);
	edge_add(now<<1|1,now);
	Build(now<<1);
	Build(now<<1|1);
}

inline void read(ll &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while(!isdigit(Cget=getchar()))
		if(Cget=='-')
			if_z=-1;
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}

int main()
{
//	freopen("data.txt","r",stdin);
//	freopen("ans1.txt","w",stdout);
//	scanf("%d",&n);
	std::cin>>n;
	for(int i=1;i<=n;i++)
	{
		read(xi[i]);
		read(ri[i]);
	}
//		scanf("%lld%lld",&xi[i],&ri[i]);
	build(1,1,n);
	Tarjan(1);
	Build(1);
	int h=0,tail=0,now;
	for(int i=1;i<=col;i++)
		if(!du[i])
			que[tail++]=i;
	while(h<tail)
	{
		now=que[h++];
		for(int i=head[now];i!=0;i=E[i])
		{
			Min2[V[i]]=std::min(Min2[V[i]],Min2[now]);
			Max2[V[i]]=std::max(Max2[V[i]],Max2[now]);
			if(!(--du[V[i]]))
				que[tail++]=V[i];
		}
	}
	for(int i=1;i<=n;i++)
		(ans+=1LL*i*(Max2[bel[id[i]]]-Min2[bel[id[i]]]+1)%mod)%=mod;
	std::cout<<ans<<std::endl;
	return 0;
}
