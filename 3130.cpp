#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const int maxn=105;
const real INF=5e8;
const real eps=1e-5;

struct EdgeType
{
	int v;
	
	real f,lit;
	
	EdgeType *next,*opposition;
	
	EdgeType(){}
	
	EdgeType(int v_,real f_,EdgeType *next_)
	{
		v=v_;
		f=f_;
		lit=f_;
		next=next_;
	}
	
	void clear()
	{
		f=lit;
	}
	
	void limitit(real x)
	{
		f=std::min(lit,x);
	}
};

struct EdgeType *head[maxn];

int n,m,que[maxn],deep[maxn];

real p,ans1,ans2;

bool bfs()
{
	for(int i=1;i<=n;i++)
		deep[i]=-1;
	deep[1]=0;
	int h=0,tail=1,now;
	que[0]=1;
	while(h<tail)
		for(EdgeType *i=head[now=que[h++]];i!=NULL;i=i->next)
			if(i->f>eps&&deep[i->v]<0)
			{
				deep[i->v]=deep[now]+1;
				if(i->v==n)
					return true;
				que[tail++]=i->v;
			}
	return false;
}

real flowing(int now,real flow)
{
	if(flow<=eps||now==n)
		return flow;
	real oldflow=0,tmp;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->f>eps&&deep[i->v]==deep[now]+1)
		{
			tmp=flowing(i->v,std::min(flow,i->f));
			i->f-=tmp;
			i->opposition->f+=tmp;
			flow-=tmp;
			oldflow+=tmp;
			if(flow<=eps)
				return oldflow;
		}
	if(flow>eps)
		deep[now]=-1;
	return oldflow;
}

bool check(real lit)
{
	for(int now=1;now<=n;now++)
		for(EdgeType *i=head[now];i!=NULL;i=i->next)
			i->limitit(lit);
	real tmp=0;
	while(bfs())
		tmp+=flowing(1,INF);
	return tmp>=ans1-eps;
}

int main()
{
	freopen("data.txt","r",stdin);
	scanf("%d%d%lf",&n,&m,&p);
	for(int i=1;i<=n;i++)
		head[i]=NULL;
	int u,v;
	real f;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lf",&u,&v,&f);
		head[u]=new EdgeType(v,f,head[u]);
		head[v]=new EdgeType(u,0,head[v]);
		head[u]->opposition=head[v];
		head[v]->opposition=head[u];
	}
	while(bfs())
		ans1+=flowing(1,INF);
	printf("%d\n",(int)ans1);
	real l=0,r=50000000,mid;
	for(int i=1;i<=40;i++)
	{
		mid=(l+r)/2.0;
		if(check(mid))
			r=mid-eps;
		else
			l=mid+eps;
	}
	printf("%lf\n",l*p);
	return 0;
}
