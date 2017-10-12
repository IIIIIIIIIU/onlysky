#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=10005;

struct EdgeType
{
	int v;

	EdgeType *next;

	EdgeType(int v_=0,EdgeType *next_=NULL)
	{
		v=v_,next=next_;
	}
};

struct EdgeType *head[maxn];

int n,m,cnt,bel[maxn],low[maxn],dfn[maxn],tag,Stack[maxn],top,col;

using std::map;
using std::string;

map<string,int>Map;

string tmp1,tmp2;

void tarjan(int now)
{
	dfn[now]=low[now]=++tag,Stack[++top]=now;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(!bel[i->v])
			if(dfn[i->v]) low[now]=std::min(low[now],dfn[i->v]);
			else tarjan(i->v),low[now]=std::min(low[now],low[i->v]);
	if(dfn[now]==low[now])
	{
		col++;
		while(Stack[top]!=now) bel[Stack[top--]]=col;
		bel[now]=col,top--;
	}
}

int main()
{
//	freopen("marriage.in","r",stdin);
//	freopen("marriage.out","w",stdout);
	std::cin>>n;
	int u,v;
	for(int i=1;i<=n;i++)
	{
		std::cin>>tmp1>>tmp2;
		Map[tmp1]=++cnt,Map[tmp2]=++cnt;
		head[cnt-1]=head[cnt]=NULL;
		u=cnt-1,v=cnt;
		head[u]=new EdgeType(v,head[u]);
	}
	std::cin>>m;
	for(int i=1;i<=m;i++)
	{
		std::cin>>tmp1>>tmp2;
		v=Map[tmp1],u=Map[tmp2];
		head[u]=new EdgeType(v,head[u]);
	}
	for(int i=1;i<=cnt;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=cnt;i+=2)
		puts(bel[i]==bel[i+1]?"Unsafe":"Safe");
	return 0;
}
