#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const real eps=1e-8;
const int maxn=1e2+5;
const int INF=0x3f3f3f3f;

struct point
{
	real x,y;
	
	point(){}
	
	point(real x_,real y_)
	{
		x=x_;
		y=y_;
	}
	
	real operator&(const point &tmp)const
	{
		return std::sqrt((x-tmp.x)*(x-tmp.x)+(y-tmp.y)*(y-tmp.y));
	}
};

struct point ai[maxn],bi[maxn];

int n,k,deep[maxn],que[maxn],s,t,head[maxn],E[maxn*maxn],V[maxn*maxn];
int F[maxn*maxn],cnt;

inline void edge_add(int u,int v,int f)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	F[cnt]=f;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	F[cnt]=0;
	head[v]=cnt;
}

bool bfs()
{
	int h=0,tail=1,now;
	for(int i=s;i<=t;i++)
		deep[i]=-1;
	deep[s]=0;
	que[0]=s;
	while(h<tail)
		for(int i=head[now=que[h++]];i!=0;i=E[i])
			if(F[i]&&deep[V[i]]<0)
			{
				deep[V[i]]=deep[now]+1;
				if(V[i]==t)
					return true;
				que[tail++]=V[i];
			}
	return false;
}

int flowing(int now,int flow)
{
	if(now==t||flow<=0)
		return flow;
	int oldflow=0,tmp;
	for(int i=head[now];i!=0;i=E[i])
		if(F[i]&&deep[V[i]]==deep[now]+1)
		{
			tmp=flowing(V[i],std::min(flow,F[i]));
			F[i]-=tmp;
			flow-=tmp;
			F[i^1]+=tmp;
			oldflow+=tmp;
			if(!flow)
				return oldflow;
		}
	if(flow)
		deep[now]=-1;
	return oldflow;
}

int get1(real lit)
{
	int res=0;
	memset(head,0,sizeof(head));
	cnt=1;
	s=0;
	t=n*2+1;
	for(int i=1;i<=n;i++)
	{
		edge_add(s,i,1);
		edge_add(i+n,t,1);
		for(int v=1;v<=n;v++)
			if((ai[i]&bi[v])<lit-eps)
				edge_add(i,v+n,1);
	}
	while(bfs())
		res+=flowing(s,INF);
	return res;
}

int get2(real lit)
{
	int res=0;
	memset(head,0,sizeof(head));
	cnt=1;
	s=0;
	t=n*2+1;
	for(int i=1;i<=n;i++)
	{
		edge_add(s,i,1);
		edge_add(i+n,t,1);
		for(int v=1;v<=n;v++)
			if((ai[i]&bi[v])>lit+eps)
				edge_add(i,v+n,1);
	}
	while(bfs())
		res+=flowing(s,INF);
	return res;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&ai[i].x,&ai[i].y);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&bi[i].x,&bi[i].y);
	real l=0,r=10000,mid;
	while(l+eps<=r)
	{
		mid=(l+r)/2;
		if(get1(mid)>=k)
			r=mid-eps;
		else
			l=mid+eps;
	}
	printf("%.2lf ",l);
	l=0,r=10000;
	while(l+eps<=r)
	{
		mid=(l+r)/2;
		if(get2(mid)>=n-k)
			l=mid+eps;
		else
			r=mid-eps;
	}
	if(l>9999)
		printf("+INF");
	else
		printf("%.2lf\n",l);
	return 0;
}
