#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e3+5;
const int INF=0x3f3f3f3f;

struct EdgeType
{
	int v,w,f;
	
	EdgeType *next,*opposition;
	
	EdgeType(){}
	
	EdgeType(int v_,int w_,int f_,EdgeType *next_)
	{
		v=v_;
		w=w_;
		f=f_;
		next=next_;
	}
};

struct EdgeType *head[maxn],*pre[maxn];

int n,a,b,s,t,dis[maxn],que[maxn];

bool vis[maxn];

inline bool isx2(int x)
{
	int tmp=sqrt(x);
	return tmp*tmp==x;
}

inline int gcd(int A,int B)
{
	if(!B)
		return A;
	return gcd(B,A%B);
}

inline void edge_add(int u,int v,int w,int f)
{
	head[u]=new EdgeType(v,w,f,head[u]);
	head[v]=new EdgeType(u,-w,0,head[v]);
	head[u]->opposition=head[v];
	head[v]->opposition=head[u];
}

bool spfa()
{
	for(int i=s;i<=t;i++)
	{
		dis[i]=-INF;
		pre[i]=NULL;
		vis[i]=false;
	}
	dis[s]=0;
	vis[s]=true;
	int h=0,tail=1,now;
	que[0]=s;
	while(h<tail)
	{
		now=que[h++];
		for(EdgeType *i=head[now];i!=NULL;i=i->next)
			if(i->f&&dis[i->v]<dis[now]+i->w)
			{
				pre[i->v]=i;
				dis[i->v]=dis[now]+i->w;
				if(!vis[i->v])
					que[tail++]=i->v;
			}
	}
	return dis[t]!=-INF;
}

int main()
{
	std::cin>>a>>b;
	s=0;
	t=2001;
	for(int i=a,v,tmp;i<=b;i++)
	{
		edge_add(s,i,0,1);
		edge_add(i+1000,t,0,1);
		for(v=a;v<i;v++)
		{
			tmp=i*i-v*v;
			if(isx2(tmp)&&gcd(v,tmp)==1)
			{
				edge_add(i,v+1000,i+v,1);
				edge_add(v,i+1000,i+v,1);
			}
		}
	}
	int ans=0;
	while(spfa())
	{
		int now=t,pos=INF;
		while(now!=s)
		{
			if(pre[now]->f<pos)
				pos=pre[now]->f;
			now=pre[now]->opposition->v;
		}
		now=t;
		while(now!=s)
		{
			pre[now]->f-=pos;
			pre[now]->opposition->f+=pos;
			now=pre[now]->opposition->v;
		}
		ans+=dis[t]*pos;
	}
	int k=0;
	for(EdgeType *i=head[s];i!=NULL;i=i->next)
		if(i->f==0)
			k++;
	std::cout<<(k>>1)<<' '<<(ans>>1);
	return 0;
}
