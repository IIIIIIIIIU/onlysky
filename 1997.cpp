#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2005,maxm=10005;

struct ee
{
	int to,next;
};

struct ee e[maxm*100];

int T,n,m,timer,top,cnt,scc,u[maxm],v[maxm],c[maxn],pos[maxn],head[maxn];
int dfn[maxn],low[maxn],s[maxn],bel[maxn],ss[maxn];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

void ins(int u,int v)
{
	e[++cnt].to=v,e[cnt].next=head[u],head[u]=cnt;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++timer,s[++top]=x,ss[x]=1;
	for(int i=head[x];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v]) tarjan(v),low[x]=std::min(low[x],low[v]);
		else if(ss[v]) low[x]=std::min(low[x],dfn[v]);
	}
	if(dfn[x]==low[x])
	{
		int t=-1;scc++;
		while(t!=x) t=s[top--],bel[t]=scc,ss[t]=0;
	}
}

bool judge()
{
	for(int i=1;i<=m;i++)
		if(bel[i<<1]==bel[(i<<1)-1]) return false;
	return true;
}

int main()
{
	read(T);
	while(T--)
	{
		memset(head,0,sizeof(head)),cnt=0;
		scc=cnt=timer=top=0;
		memset(low,0,sizeof(low));
		memset(dfn,0,sizeof(dfn));
		read(n),read(m);
		for(int i=1;i<=m;i++) read(u[i]),read(v[i]);
		for(int i=1;i<=n;i++) read(c[i]);
		for(int i=1;i<=n;i++) pos[c[i]]=i;
		if(m>3*n-6)
		{
			puts("NO");
			continue;
		}
		for(int i=1;i<=m;i++)
		{
			u[i]=pos[u[i]],v[i]=pos[v[i]];
			if(u[i]>v[i]) std::swap(u[i],v[i]);
			if(v[i]-u[i]==1||(u[i]==1&&v[i]==n)) continue;
			u[++top]=u[i],v[top]=v[i];
		}
		m=top,top=0;
		for(int i=1;i<=m;i++)
			for(int j=i+1;j<=m;j++)
				if((u[i]<u[j]&&v[i]<v[j]&&v[i]>u[j])||u[j]<u[i]&&v[i]>v[j]&&v[j]>u[i])
					ins(2*i-1,2*j),ins(2*j-1,2*i),ins(2*j,2*i-1),ins(2*i,2*j-1);
		for(int i=1;i<=(m<<1);i++)
			if(!dfn[i]) tarjan(i);
		if(judge()) puts("YES");
		else puts("NO");
	}
	return 0;
}
