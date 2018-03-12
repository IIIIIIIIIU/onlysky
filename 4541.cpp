#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long long ll;

const int maxn=200010;
const int rhl=2341687;
const int maxm=1200010;

struct point
{
	int x,y;
	
	point(){}
	
	point(int x_,int y_)
	{
		x=x_;
		y=y_;
	}
	
	inline point operator-(const point &tmp)const
	{
		return point(x-tmp.x,y-tmp.y);
	}
};

struct point p[maxn];

struct edge
{
	int u,v,id;
	
	real ang;
	
	inline bool operator<(const edge &tmp)const
	{
		return ang<tmp.ang;
	}
};

struct edge g[maxm];

struct E
{
	int nt,to,id;
};

struct E G[maxm];

struct H
{
	int nt,x,y,id;
};

struct H hsh[maxm];

std::vector<edge>e[maxn];

int hd[rhl+10],head[maxm],vis[maxm],fa[maxm],in[maxm],bl[maxm];
int nxt[maxm],ask[maxm<<1],n,m,k,rt,num,cnt,ecnt,hcnt;

ll sp[maxm],s[maxm],P,Q;

inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while(!isdigit(Cget=getchar()))
		if(Cget=='-')
			if_z=-1;
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}

inline ll gcd(ll a,ll b)
{
	return !b?a:gcd(b,a%b);
}

inline ll cross(point a,point b)
{
	return 1LL*a.x*b.y-1LL*a.y*b.x;
}

inline void insert(int a,int b)
{
	real ang=std::atan2(p[b].y-p[a].y,p[b].x-p[a].x);
	++num;
	g[num]=(edge){a,b,num,ang};
	e[a].push_back(g[num]);
}

inline void Insert(int from,int to,int id)
{
	G[++ecnt]=(E){head[from],to,id},head[from]=ecnt;
}

inline void ins(int from,int x,int y,int id)
{
	hsh[++hcnt]=(H){hd[from],x,y,id},hd[from]=hcnt;
}

inline void add(int x,int y,int id)
{
	int cnm=(1LL*x*maxn+y)%rhl;
	ins(cnm,x,y,id);
}

inline int get(int x,int y)
{
	int cnm=(1LL*x*maxn+y)%rhl;
	for(int i=hd[cnm];i;i=hsh[i].nt)
		if(hsh[i].x==x&&hsh[i].y==y)
			return hsh[i].id;
	return 0;
}

inline void dfs(int x)
{
	vis[x]=1;
	sp[x]=s[x]*s[x],s[x]<<=1;
	int v;
	for(int i=head[x];i;i=G[i].nt)
	{
		v=G[i].to;
		if(vis[v])
			continue;
		fa[v]=x;
		in[G[i].id]=in[G[i].id^1]=1;
		dfs(v);
		sp[x]+=sp[v];
		s[x]+=s[v];
	}
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	read(k);
	num=1;
	int x,y;
	for(int i=1;i<=n;i++)
	{
		read(x);
		read(y);
		p[i]=(point){x,y};
	}
	for(int i=1;i<=m;i++)
	{
		read(x);
		read(y);
		insert(x,y);
		insert(y,x);
	}
	for(int i=1,sz;i<=n;i++)
	{
		std::sort(e[i].begin(),e[i].end());
		sz=e[i].size();
		for(int j=1;j<sz;j++)
			nxt[e[i][j].id]=e[i][j-1].id;
		nxt[e[i][0].id]=e[i][sz-1].id;
	}
	for(int i=2;i<=num;i++)
	{
		if(bl[i])
			continue;
		bl[i]=bl[nxt[i^1]]=++cnt;
		for(int now=nxt[i^1];g[now].v!=g[i].u;now=nxt[now^1],bl[now]=cnt)
			s[cnt]+=cross(p[g[now].u]-p[g[i].u],p[g[now].v]-p[g[i].u]);
		if(s[cnt]<=0)
			rt=cnt;
	}
	for(int i=2;i<=num;++i)
	{
		Insert(bl[i],bl[i^1],i);
		add(g[i].u,g[i].v,g[i].id);
	}
	dfs(rt);
	for(int q=1,d,t;q<=k;++q)
	{
		read(t);
		d=(t+P)%n+1;
		for(int i=1;i<=d;i++)
		{
			read(t);
			ask[i]=(t+P)%n+1;
		}
		ask[d+1]=ask[1];
		P=Q=0;
		for(int i=1,now;i<=d;i++)
		{
			now=get(ask[i],ask[i+1]);
			if(!in[now])
				continue;
			if(fa[bl[now]]==bl[now^1])
			{
				P+=sp[bl[now]];
				Q+=s[bl[now]];
			}
			else
			{
				P-=sp[bl[now^1]];
				Q-=s[bl[now^1]];
			}
		}
		ll gg=gcd(P,Q);
		P/=gg;
		Q/=gg;
		printf("%lld %lld\n",P,Q);
	}
	return 0;
}
