#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e6+5;
const int mod=1999999;
const int INF=0x3f3f3f3f;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};

int n,m,head[maxn],E[maxn],V[maxn],F[maxn],cnt=1;
int front[maxn],Ef[maxn],id[maxn],deep[maxn],que[maxn];
int num,R,C,xi[maxn],yi[maxn],wi[maxn],s,t,kind[maxn];

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

inline void add(int d)
{
	int base=(1LL*xi[d]*(n+1)+yi[d])%mod;
	Ef[++num]=front[base];
	id[num]=d;
	front[base]=num;
}

inline int find(int x,int y)
{
	int base=(1LL*x*(n+1)+y)%mod;
	for(int i=front[base];i!=0;i=Ef[i])
		if(xi[id[i]]==x&&yi[id[i]]==y)
			return id[i];
	return 0;
}

inline int get(int x,int y)
{
	if(y%4==1)
	{
		if(x%2)
			return 2;
		return 1;
	}
	else if(y%4==0)
	{
		if(x%2)
			return 1;
		return 2;
	}
	else if(y%4==2)
	{
		if(x%2)
			return 3;
		return 4;
	}
	else
	{
		if(x%2)
			return 4;
		return 3;
	}
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
			if(deep[V[i]]<0&&F[i]>0)
			{
				deep[V[i]]=deep[now]+1;
				if(V[i]==t)
					return true;
				que[tail++]=V[i];
			}
	}
	return false;
}

inline int flowing(int now,int flow)
{
	if(now==t||flow<=0)
		return flow;
	int oldflow=0,tmp;
	for(int i=head[now];i!=0;i=E[i])
		if(F[i]>0&&deep[V[i]]==deep[now]+1)
		{
			tmp=flowing(V[i],std::min(flow,F[i]));
			flow-=tmp;
			oldflow+=tmp;
			F[i]-=tmp;
			F[i^1]+=tmp;
			if(!flow)
				return oldflow;
		}
	if(flow)
		deep[now]=-1;
	return oldflow;
}

int main()
{
	freopen("data.txt","r",stdin);
	read(R);
	read(C);
	read(n);
	t=n<<1|1;
	for(int i=1;i<=n;i++)
	{
		read(yi[i]);
		read(xi[i]);
		read(wi[i]);
		add(i);
		kind[i]=get(xi[i],yi[i]);
		edge_add(i,i+n,wi[i]);
	}
	for(int i=1,x,y,e;i<=n;i++)
	{
		if(kind[i]==1)
			edge_add(s,i,INF);
		if(kind[i]==4)
			edge_add(i+n,t,INF);
		for(int v=0;v<4;v++)
		{
			x=xi[i]+dx[v];
			y=yi[i]+dy[v];
			e=find(x,y);
			if(e&&kind[e]==kind[i]+1)
				edge_add(i+n,e,INF);
		}
	}
	int ans=0;
	while(bfs())
		ans+=flowing(s,INF);
	std::cout<<ans<<std::endl;
	return 0;
}
