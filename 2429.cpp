#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e3+5;

struct EdgeType
{
	int u,v,w;
	
	bool operator<(const EdgeType &tmp)const
	{
		return w<tmp.w;
	}
};

struct EdgeType edge[maxn*maxn];

int n,m,ai[maxn],xi[maxn],yi[maxn],cnt,f[maxn],ans,Max;

inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')
		if(Cget=='-')
			if_z=-1;
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}

inline int find(int x)
{
	if(x==f[x])
		return x;
	return find(f[x]);
}

int main()
{
	read(m);
	for(int i=1;i<=m;i++)
		read(ai[i]);
	read(n);
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		read(xi[i]);
		read(yi[i]);
		for(int v=1;v<i;v++)
		{
			++cnt;
			edge[cnt].u=i;
			edge[cnt].v=v;
			edge[cnt].w=(xi[i]-xi[v])*(xi[i]-xi[v])+(yi[i]-yi[v])*(yi[i]-yi[v]);
		}
	}
	std::sort(edge+1,edge+cnt+1);
	for(int i=1,x,y;i<=cnt;i++)
	{
		x=find(edge[i].u);
		y=find(edge[i].v);
		if(x!=y)
		{
			Max=edge[i].w;
			f[x]=y;
		}
	}
	for(int i=1;i<=m;i++)
		if(ai[i]*ai[i]>=Max)
			++ans;
	std::cout<<ans;
	return 0;
}
