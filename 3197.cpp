#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef unsigned long long ll;

const int mod=1e9+7;
const int maxn=1e5+5;
const int INF=0x3f3f3f3f;

int n,head[maxn],E[maxn<<1|1],V[maxn<<1|1],f[maxn];
int cnt,root,f1[maxn],f2[maxn],size[maxn],lar[maxn],num;
int Root[maxn],seq[maxn],deep[maxn],F[maxn<<1|1];
int W[maxn<<1|1],dp[705][705],que[maxn],pre[maxn];
int HEAD[maxn],E2[maxn<<1|1],V2[maxn<<1|1],s,t;
int dis[maxn];

ll Hash[maxn];

bool vis[maxn];

void findRoot(int now,int fa)
{
	size[now]=1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			findRoot(V[i],now);
			if(size[V[i]]>lar[now])
				lar[now]=size[V[i]];
			size[now]+=size[V[i]];
		}
	if(n-size[now]>lar[now])
		lar[now]=n-size[now];
	if(lar[now]<lar[root])
	{
		root=now;
		Root[num=1]=root;
	}
	else if(lar[now]==lar[root])
		Root[++num]=now;
}

void dfs(int now,int fa)
{
	if(!f[now])
		f[now]=fa;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			dfs(V[i],now);
}

inline bool cmp(const int &a,const int &b)
{
	return Hash[a]<Hash[b];
}

void dfsHash(int now,int fa)
{
	Hash[now]=233;
	deep[now]=deep[fa]+1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			dfsHash(V[i],now);
	num=0;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			seq[++num]=V[i];
	std::sort(seq+1,seq+num+1,cmp);
	for(int i=1;i<=num;i++)
		Hash[now]=Hash[now]*mod+Hash[seq[i]];
}

inline bool cmp1(const int &a,const int &b)
{
	if(deep[a]==deep[b])
		return Hash[a]<Hash[b];
	return deep[a]>deep[b];
}

inline void edge_add(int u,int v,int w,int f)
{
	E2[++cnt]=HEAD[u];
	V2[cnt]=v;
	W[cnt]=w;
	F[cnt]=f;
	HEAD[u]=cnt;
	E2[++cnt]=HEAD[v];
	V2[cnt]=u;
	W[cnt]=-w;
	F[cnt]=0;
	HEAD[v]=cnt;
}

bool spfa()
{
	for(int i=s;i<=t;i++)
	{
		pre[i]=-1;
		dis[i]=INF;
		vis[i]=false;
	}
	int h=0,tail=1,now;
	que[h]=s;
	dis[s]=0;
	vis[s]=true;
	while(h<tail)
	{
		now=que[h++];
		vis[now]=false;
		for(int i=HEAD[now];i!=0;i=E2[i])
			if(F[i]&&dis[V2[i]]>dis[now]+W[i])
			{
				pre[V2[i]]=i;
				dis[V2[i]]=dis[now]+W[i];
				if(!vis[V2[i]])
				{
					vis[V2[i]]=true;
					que[tail++]=V2[i];
				}
			}
	}
	return dis[t]!=INF;
}

int solve(int x,int y)
{
	int tmp=0;
	for(int i=head[x];i!=0;i=E[i])
		if(V[i]!=f[x])
			++tmp;
	s=0;
	t=tmp*2+1;
	for(int i=s;i<=t;i++)
		HEAD[i]=0;
	cnt=1;
	for(int i=head[x],t1=1;i!=0;i=E[i],t1++)
		if(V[i]!=f[x])
		{
			for(int e=head[y],t2=1;e!=0;e=E[e],t2++)
				if(V[e]!=f[y])
				{
					if(dp[V[i]][V[e]]>=0&&Hash[V[i]]==Hash[V[e]])
						edge_add(t1,t2+tmp,dp[V[i]][V[e]],1);
				}
				else
					t2--;
		}
		else
			t1--;
	for(int i=1;i<=tmp;i++)
	{
		edge_add(s,i,0,1);
		edge_add(i+tmp,t,0,1);
	}
	int resf=0,resw=0;
	while(spfa())
	{
		resf++;
		resw+=dis[t];
		int now=t;
		while(pre[now]!=-1)
		{
			F[pre[now]]--;
			F[pre[now]^1]++;
			now=V2[pre[now]^1];
		}
	}
	if(resf==tmp)
		return (f1[x]!=f2[y])+resw;
	else
		return -1;
}

int main()
{
	lar[0]=INF;
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		E[++cnt]=head[u];
		V[cnt]=v;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		head[v]=cnt;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&f1[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&f2[i]);
	findRoot(1,0);
	if(num>1)
	{
		n++;
		for(int i=1;i<=num;i++)
			f[Root[i]]=n;
	}
	dfs(root,0);
	for(int i=1;i<=n;i++)
		head[i]=0;
	cnt=1;
	for(int i=1,u,v;i<=n;i++)
	{
		if(!f[i])
			continue;
		u=i;
		v=f[i];
		E[++cnt]=head[u];
		V[cnt]=v;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		head[v]=cnt;
	}
	if(num>1)
		root=n;
	dfsHash(root,0);
	for(int i=1;i<=n;i++)
		seq[i]=i;
	std::sort(seq+1,seq+n+1,cmp1);
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			if(Hash[seq[i]]==Hash[seq[v]])
				dp[seq[i]][seq[v]]=solve(seq[i],seq[v]);
	std::cout<<dp[root][root]<<std::endl;
	return 0;
}
