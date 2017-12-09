#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=2e5+5;

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

int n,m=n-2,deep[maxn],que[maxn];

std::map<ll,int>Map;

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

void bfs(int s)
{
	for(int i=1;i<=m;i++)
		deep[i]=0;
	deep[s]=1;
	int h=0,tail=1,now;
	que[0]=s;
	while(h<tail)
		for(EdgeType *i=head[now=que[h++]];i!=NULL;i=i->next)
			if(!deep[i->v])
			{
				deep[i->v]=deep[now]+1;
				que[tail++]=i->v;
			}
}

int main()
{
	read(n);
	m=n-2;
	for(int i=1;i<=m;i++)
		head[i]=NULL;
	ll tmp;
	for(int i=1,e,z,q[4],u,v;i<=m;i++)
	{
		for(v=1;v<=3;v++)
			read(q[v]);
		std::sort(q+1,q+3+1);
		for(e=1;e<=2;e++)
			for(z=e+1;z<=3;z++)
			{
				tmp=1LL*(m+1)*q[e]+q[z];
				if(u=Map[tmp])
				{
					v=i;
					head[u]=new EdgeType(v,head[u]);
					head[v]=new EdgeType(u,head[v]);
				}
				else
					Map[tmp]=i;
			}
	}
	bfs(1);
	int root=1;
	for(int i=1;i<=m;i++)
		if(deep[i]>deep[root])
			root=i;
	bfs(root);
	int ans=deep[root];
	for(int i=1;i<=m;i++)
		ans=std::max(ans,deep[i]);
	std::cout<<ans;
	return 0;
}
