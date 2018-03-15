#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const real eps=1e-4;
const real INF=1e16;
const int maxn=1e3+5;
const int maxm=1e5+5;

int n,m,head[maxn],E[maxm],V[maxm],n1,m1,que[maxm*10];
int s,t,deep[maxn],cnt;

bool vis[maxn];

real T[maxm],S[maxm],W[maxm],dis[maxn],val[maxn];

inline int GetInt()
{
	char Cget;
	int now=0;
	while(!isdigit(Cget=getchar()));
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	return now;
}

bool spfa(int RES,real tmp)
{
	for(int i=1;i<=m;i++)
		W[i]=T[i]-S[i]*tmp;
	for(int i=1;i<=n;i++)
	{
		dis[i]=INF;
		vis[i]=false;
	}
	dis[n]=0;
	vis[n]=true;
	int h=0,tail=1,now;
	que[0]=n;
	while(h<tail)
	{
		now=que[h++];
		vis[now]=false;
		for(int i=head[now];i!=0;i=E[i])
			if(dis[V[i]]>dis[now]+W[i])
			{
				dis[V[i]]=dis[now]+W[i];
				if(dis[RES]<0)
					return true;
				if(!vis[V[i]])
				{
					vis[V[i]]=true;
					que[tail++]=V[i];
				}
			}
	}
	return dis[RES]<0;
}

inline void edge_add(int u,int v,real f)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	W[cnt]=f;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	W[cnt]=0;
	head[v]=cnt;
}

bool bfs()
{
	for(int i=s;i<=t;i++)
		deep[i]=-1;
	int h=0,tail=1,now;
	deep[s]=0;
	que[h]=s;
	while(h<tail)
	{
		now=que[h++];
		for(int i=head[now];i!=0;i=E[i])
			if(deep[V[i]]<0&&W[i]>eps)
			{
				deep[V[i]]=deep[now]+1;
				if(V[i]==t)
					return true;
				que[tail++]=V[i];
			}
	}
	return false;
}

real flowing(int now,real flow)
{
	if(t==now||flow<=eps)
		return flow;
	real oldflow=0,tmp;
	for(int i=head[now];i!=0;i=E[i])
		if(deep[V[i]]==deep[now]+1&&W[i]>eps)
		{
			tmp=flowing(V[i],std::min(flow,W[i]));
			W[i]-=tmp;
			W[i^1]+=tmp;
			flow-=tmp;
			oldflow+=tmp;
			if(flow<=eps)
				return oldflow;
		}
	if(flow>eps)
		deep[now]=-1;
	return oldflow;
}

int main()
{
	freopen("data.txt","r",stdin);
//	freopen("tfnhnsm.in","r",stdin);
//	freopen("tfnhnsm.out","w",stdout);
	n=GetInt();
	m=GetInt();
	for(int i=1,u,v,a,b;i<=m;i++)
	{
		u=GetInt();
		v=GetInt();
		a=GetInt();
		b=GetInt();
		E[++cnt]=head[u];
		V[cnt]=v;
		T[cnt]=a;
		S[cnt]=b;
		head[u]=cnt;
	}
	m1=GetInt();
	n1=GetInt();
	for(int i=1;i<=n1;i++)
	{
		real l=0,r=20,mid,res=INF;
		while(l+eps<=r)
		{
			mid=(l+r)/2.0;
			if(spfa(i,mid))
			{
				res=mid;
				r=mid;
			}
			else
				l=mid;
		}
		val[i]=res;
	}
	memset(head,0,sizeof(head));
	cnt=1;
	s=0;
	t=n1+1;
	for(int i=1,u,v;i<=m1;i++)
	{
		u=GetInt();
		v=GetInt();
		if(val[u]==INF&&val[v]==INF)
		{
			puts("-1");
			return 0;
		}
		edge_add(u,v,INF);
	}
	for(int i=1;i<=n1;i++)
		if(i&1)
			edge_add(s,i,val[i]);
		else
			edge_add(i,t,val[i]);
	real ans=0;
	while(bfs())
		ans+=flowing(s,INF);
	printf("%.1lf\n",ans);
	return 0;
}
