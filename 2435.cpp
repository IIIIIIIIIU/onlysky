#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef unsigned long long ll;

const int maxn=1e6+5;

struct EdgeType
{
	int v,w;
	
	EdgeType *next;
	
	EdgeType(){}
	
	EdgeType(int v_,int w_,EdgeType *next_)
	{
		v=v_;
		w=w_;
		next=next_;
	}
};

struct EdgeType *head[maxn],*si[maxn];

int n,size[maxn],sn[maxn],sf[maxn];

ll ans,C=1;

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
/*
void dfs(int now,int fa)
{
	size[now]=1;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->v!=fa)
		{
			dfs(i->v,now);
			size[now]+=size[i->v];
			ans+=C*i->w*std::abs(n-2*size[i->v]);
		}
}
*/
void dfs(int snow,int sfa)
{
	int now=1;
	sn[now]=1;
	sf[now]=0;
	FLAG1:;
	size[sn[now]]=1;
	for(si[now]=head[sn[now]];si[now]!=NULL;si[now]=si[now]->next)
		if(si[now]->v!=sf[now])
		{
			now++;
			sn[now]=si[now-1]->v;
			sf[now]=sn[now-1];
			goto FLAG1;
			FLAG2:;
			size[sn[now]]+=size[si[now]->v];
			ans+=C*si[now]->w*abs(n-2*size[si[now]->v]);
		}
	if(now==1)
		return;
	now--;
	goto FLAG2;
}

int main()
{
	read(n);
	for(int i=1;i<=n;i++)
		head[i]=NULL;
	for(int i=1,u,v,w;i<n;i++)
	{
		read(u);
		read(v);
		read(w);
		head[u]=new EdgeType(v,w,head[u]);
		head[v]=new EdgeType(u,w,head[v]);
	}
	dfs(1,0);
	std::cout<<ans;
	return 0;
}
