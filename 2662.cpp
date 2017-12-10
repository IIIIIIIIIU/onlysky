#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=55;
const int maxque=1e6+5;

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

struct EdgeType *head[maxn];

int dis[maxn][maxn],quex[maxque],quey[maxque],n,m,k;

bool vis[maxn][maxn];

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

int main()
{
	read(n);
	read(m);
	read(k);
	for(int i=1;i<=n;i++)
		head[i]=NULL;
	memset(dis,0x3f,sizeof(dis));
	dis[1][0]=0;
	vis[1][0]=true;
	int h=0,tail=1,nowx,nowy;
	quex[0]=1;
	quey[0]=0;
	for(int i=1,u,v,w;i<=m;i++)
	{
		read(u);
		read(v);
		read(w);
		head[u]=new EdgeType(v,w,head[u]);
		head[v]=new EdgeType(u,w,head[v]);
	}
	while(h<tail)
	{
		nowx=quex[h];
		nowy=quey[h++];
		vis[nowx][nowy]=false;
		for(EdgeType *i=head[nowx];i!=NULL;i=i->next)
			if(dis[i->v][nowy]>dis[nowx][nowy]+i->w)
			{
				dis[i->v][nowy]=dis[nowx][nowy]+i->w;
				if(!vis[i->v][nowy])
				{
					vis[i->v][nowy]=true;
					quex[tail]=i->v;
					quey[tail++]=nowy;
				}
			}
		if(nowy<k)
			for(EdgeType *i=head[nowx];i!=NULL;i=i->next)
				if(dis[i->v][nowy+1]>dis[nowx][nowy]+(i->w>>1))
				{
					dis[i->v][nowy+1]=dis[nowx][nowy]+(i->w>>1);
					if(!vis[i->v][nowy+1])
					{
						vis[i->v][nowy+1]=true;
						quex[tail]=i->v;
						quey[tail++]=nowy+1;
					}
				}
	}
	int ans=0x3f3f3f3f;
	for(int i=0;i<=k;i++)
		ans=std::min(ans,dis[n][i]);
	std::cout<<ans;
	return 0;
}
