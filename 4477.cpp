#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=4e5+5;

int n,m,root[maxn],ch[maxn*11][26],tot,sum[maxn*11];
int head[maxn],E[maxn<<1],V[maxn<<1],W[maxn<<1],cnt,f[maxn];
int deep[maxn],size[maxn],lar[maxn],top[maxn],ins[maxn];

char str[maxn][10];

void insert(int now,int pre,char *p,int len)
{
	root[now]=++tot;
	now=root[now];
	for(int v=0;v<26;v++)
		ch[now][v]=ch[pre][v];
	for(int i=0,to,v;i<len;i++)
	{
		to=p[i]-'a';
		ch[now][to]=++tot;
		now=ch[now][to];
		pre=ch[pre][to];
		sum[now]=sum[pre]+1;
		for(v=0;v<26;v++)
			ch[now][v]=ch[pre][v];
	}
}

void dfs1(int now,int fa)
{
	if(ins[now])
		insert(now,root[fa],str[ins[now]],strlen(str[ins[now]]));
	f[now]=fa;
	size[now]=1;
	deep[now]=deep[fa]+1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			ins[V[i]]=W[i];
			dfs1(V[i],now);
			size[now]+=size[V[i]];
			if(size[V[i]]>size[lar[now]])
				lar[now]=V[i];
		}
}

void dfs2(int now,int chain)
{
	top[now]=chain;
	if(lar[now])
		dfs2(lar[now],chain);
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=f[now]&&V[i]!=lar[now])
			dfs2(V[i],V[i]);
}

int query(int now,int len,char *p)
{
	for(int i=0,to;i<len;i++)
	{
		to=p[i]-'a';
		now=ch[now][to];
	}
	return sum[now];
}

inline int getLca(int x,int y)
{
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]])
			x=f[top[x]];
		else
			y=f[top[y]];
	if(deep[x]>deep[y])
		return y;
	else
		return x;
}

inline void read(int &now)
{
	char Cget;
	now=0;
	while(!isdigit(Cget=getchar()));
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	for(int i=1,u,v;i<n;i++)
	{
		read(u);
		read(v);
		scanf("%s",str[i]);
		E[++cnt]=head[u];
		V[cnt]=v;
		W[cnt]=i;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		W[cnt]=i;
		head[v]=cnt;
	}
	dfs1(1,0);
	dfs2(1,1);
	char op[20];
	int q,x,y,lca,len;
	read(q);
	for(int i=1;i<=q;i++)
	{
		read(x);
		read(y);
		lca=getLca(x,y);
		scanf("%s",op);
		len=strlen(op);
		printf("%d\n",query(root[x],len,op)+query(root[y],len,op)-2*query(root[lca],len,op));
	}
	return 0;
}
