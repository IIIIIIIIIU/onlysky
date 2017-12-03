#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const int maxn=1e5+5;

struct BaseEdgeType
{
	int u,v;
};

struct BaseEdgeType edge[maxn*3];

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

struct EdgeType *head[maxn];

int n,m,size[maxn],tag,dfn[maxn],low[maxn],bel[maxn];
int Stack[maxn],top,col,du[maxn],du2[maxn];

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

void tarjan(int now)
{
	dfn[now]=++tag;
	low[now]=tag;
	Stack[++top]=now;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(!bel[i->v])
			if(dfn[i->v])
				low[now]=std::min(low[now],dfn[i->v]);
			else
			{
				tarjan(i->v);
				low[now]=std::min(low[now],low[i->v]);
			}
	if(dfn[now]==low[now])
	{
		col++;
		while(Stack[top]!=now)
		{
			bel[Stack[top]]=col;
			size[col]++;
			top--;
		}
		top--;
		bel[now]=col;
		size[col]++;
	}
}

int main()
{
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
		head[i]=NULL;
	for(int i=1,u,v;i<=m;i++)
	{
		read(u);
		read(v);
		edge[i].u=u;
		edge[i].v=v;
		head[u]=new EdgeType(v,head[u]);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1,u,v;i<=m;i++)
	{
		u=edge[i].u;
		v=edge[i].v;
		if(bel[u]!=bel[v])
			du[bel[v]]++;
	}
	for(int i=1,u,v;i<=m;i++)
	{
		u=edge[i].u;
		v=edge[i].v;
		if(bel[u]!=bel[v])
			if(du[bel[v]]<=1)
				du2[bel[u]]++;
	}
	int ans=n;
	for(int i=1;i<=col;i++)
		if(!du[i])
			ans--;
	for(int i=1;i<=col;i++)
		if(!du[i]&&!du2[i]&&size[i]==1)
		{
			ans++;
			break;
		}
	printf("%.6lf\n",(real)ans/n);
	return 0;
}
