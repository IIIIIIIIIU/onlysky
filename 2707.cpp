#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef double real;
typedef long long ll;
const int maxn=1e4+5;
const int maxm=1e6+5;
const real eps=1e-10;
struct EdgeType2
{
	int u,v;
};
struct EdgeType2 edge[maxm];
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
struct EdgeType *head[maxn],*headscc[maxn],*head2[maxn];
int n,m,dfn[maxn],low[maxn],tag,stack[maxn],top,bel[maxn];
int seq[maxn],id[maxn],num,du[maxn],vis[maxn],S,T;
int count1,count2,col,que[maxn],size[maxn];
real dp[maxn],out[maxn],f[205][205];
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
void dfs(int now)
{
	vis[now]=1;
	count1++;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(!vis[i->v])
			dfs(i->v);
}
void dfs2(int now)
{
	vis[now]=2;
	count2++;
	for(EdgeType *i=head2[now];i!=NULL;i=i->next)
		if(vis[i->v]==1)
			dfs2(i->v);
}
void tarjan(int now)
{
	dfn[now]=++tag;
	low[now]=tag;
	stack[++top]=now;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(!bel[i->v])
			if(dfn[i->v])
				low[now]=std::min(low[now],dfn[i->v]);
			else
			{
				tarjan(i->v);
				low[now]=std::min(low[now],low[i->v]);
			}
	if(low[now]==dfn[now])
	{
		++col;
		size[col]++;
		while(stack[top]!=now)
		{
			bel[stack[top]]=col;
			headscc[col]=new EdgeType(stack[top],headscc[col]);
			top--;
			size[col]++;
		}
		bel[now]=col;
		headscc[col]=new EdgeType(now,headscc[col]);
		top--;
	}
}
void guass()
{
	for(int i=1;i<=num;i++)
	{
		int tmp=i;
		for(int v=i+1;v<=num;v++)
			if(std::fabs(f[tmp][i])+eps<std::fabs(f[v][i]))
				tmp=v;
		if(tmp!=i)
			std::swap(f[tmp],f[i]);
		for(int v=i+1;v<=num;v++)
			if(std::fabs(f[v][i])>eps)
			{
				real G=f[v][i]/f[i][i];
				for(int e=1;e<=num+1;e++)
					f[v][e]-=f[i][e]*G;
			}
	}
	for(int i=num;i>=1;i--)
	{
		for(int v=i+1;v<=num;v++)
			f[i][num+1]-=f[i][v]*f[v][v];
		f[i][i]=f[i][num+1]/f[i][i];
	}
}
int main()
{
	//freopen("data.txt","r",stdin);
	read(n);
	read(m);
	read(S);
	read(T);
	for(int i=1;i<=n;i++)
	{
		head[i]=NULL;
		head2[i]=NULL;
		headscc[i]=NULL;
	}
	for(int i=1,u,v;i<=m;i++)
	{
		read(u);
		read(v);
		out[u]+=1;
		edge[i].u=u;
		edge[i].v=v;
		head[u]=new EdgeType(v,head[u]);
		head2[v]=new EdgeType(u,head2[v]);
	}
	dfs(S);
	if(vis[S])
		dfs2(T);
	if(count2!=count1)
	{
		puts("INF");
		return 0;
	}
	tarjan(S);
	for(int i=1,u,v;i<=m;i++)
	{
		u=edge[i].u;
		v=edge[i].v;
		if(!bel[u]||!bel[v])
			continue;
		if(bel[u]!=bel[v])
			du[bel[u]]++;
	}
	int h=0,tail=1,now;
	que[h]=bel[T];
	while(h<tail)
	{
		now=que[h++];
		num=0;
		for(EdgeType *i=headscc[now];i!=NULL;i=i->next)
		{
			seq[++num]=i->v;
			id[i->v]=num;
		}
		for(int i=1;i<=num;i++)
			for(int v=1;v<=num+1;v++)
				f[i][v]=0;
		for(EdgeType *i=headscc[now];i!=NULL;i=i->next)
		{
			f[id[i->v]][id[i->v]]=1;
			f[id[i->v]][num+1]=dp[i->v];
			if(i->v==T)
				continue;
			for(EdgeType *v=head[i->v];v!=NULL;v=v->next)
				if(bel[v->v]==now)
				{
					f[id[i->v]][id[v->v]]-=1/out[i->v];
					f[id[i->v]][num+1]+=1/out[i->v];
				}
		}
		guass();
		for(int i=1;i<=num;i++)
			dp[seq[i]]=f[i][i];
		for(EdgeType *i=headscc[now];i!=NULL;i=i->next)
			for(EdgeType *v=head2[i->v];v!=NULL;v=v->next)
				if(bel[v->v]!=now)
				{
					dp[v->v]+=(dp[i->v]+1)/out[v->v];
					if(!(--du[bel[v->v]]))
						que[tail++]=bel[v->v];
				}
	}
	printf("%.3lf",dp[S]);
	return 0;
}
