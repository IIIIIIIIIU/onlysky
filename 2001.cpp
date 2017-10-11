#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int INF=1e9,maxn=50005;

struct node
{
	int x,y;
};

struct node q[maxn];

struct edge
{
	int x,y,w,pos;
};

struct edge t[maxn],d[maxn],e[25][maxn];

int n,m,Q,father[maxn],size[maxn],a[maxn],c[maxn],sum[maxn];

ll ans[maxn];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget<='9'&&Cget>='0')now=now*10+Cget-'0',Cget=getchar();
}

inline bool cmp(edge u,edge v)
{
	return u.w<v.w;
}

inline void clear(int tot)
{
	for(int i=1;i<=tot;i++)
	{
		father[d[i].x]=d[i].x;
		father[d[i].y]=d[i].y;
		size[d[i].x]=size[d[i].y]=1;
	}
}

inline int find(int x)
{
	if(x==father[x]) return father[x];
	return father[x]=find(father[x]);
}

inline void merge(int x,int y)
{
	if(size[x]<=size[y]) size[y]+=size[x],father[x]=y;
	else size[x]+=size[y],father[y]=x;
}

inline void NOT_INF(int &tot,ll &cnt)
{
	int tmp=0;
	clear(tot);
	std::sort(d+1,d+tot+1,cmp);
	for(int i=1;i<=tot;i++)
		if(find(d[i].x)!=find(d[i].y))
			merge(father[d[i].x],father[d[i].y]),t[++tmp]=d[i];
	for(int i=1;i<=tmp;i++)
	{
		father[t[i].x]=t[i].x;
		father[t[i].y]=t[i].y;
		size[t[i].x]=size[t[i].y]=1;
	}
	for(int i=1;i<=tmp;i++)
		if(t[i].w!=-INF&&find(t[i].x)!=find(t[i].y))
			merge(father[t[i].x],father[t[i].y]),cnt+=t[i].w;
	tmp=0;
	for(int i=1;i<=tot;i++)
		if(find(d[i].x)!=find(d[i].y))
		{
			t[++tmp]=d[i];
			c[d[i].pos]=tmp;
			t[tmp].x=father[d[i].x];
			t[tmp].y=father[d[i].y];
		}
	tot=tmp;
	for(int i=1;i<=tot;i++) d[i]=t[i];
}

inline void YES_INF(int &tot)
{
	int tmp=0;
	clear(tot);
	std::sort(d+1,d+tot+1,cmp);
	for(int i=1;i<=tot;i++)
	{
		if(find(d[i].x)!=find(d[i].y))
		{
			t[++tmp]=d[i],c[d[i].pos]=tmp;
			merge(father[d[i].x],father[d[i].y]);
		}
		else if(d[i].w==INF)
			t[++tmp]=d[i],c[d[i].pos]=tmp;
	}
	tot=tmp;
	for(int i=1;i<=tot;i++) d[i]=t[i];
}

inline void solve(int l,int r,int now,ll cnt)
{
	int tot=sum[now];
	if(l==r) a[q[l].x]=q[l].y;
	for(int i=1;i<=tot;i++) e[now][i].w=a[e[now][i].pos];
	for(int i=1;i<=tot;i++) d[i]=e[now][i],c[d[i].pos]=i;
	if(l==r)
	{
		clear(tot);
		ans[l]=cnt;
		std::sort(d+1,d+tot+1,cmp);
		for(int i=1;i<=tot;i++)
			if(find(d[i].x)!=find(d[i].y))
				merge(father[d[i].x],father[d[i].y]),ans[l]+=d[i].w;
		return;
	}
	for(int i=l;i<=r;i++) d[c[q[i].x]].w=-INF;
	NOT_INF(tot,cnt);
	for(int i=l;i<=r;i++) d[c[q[i].x]].w=INF;
	YES_INF(tot);
	sum[now+1]=tot;
	for(int i=1;i<=tot;i++) e[now+1][i]=d[i];
	int mid=l+r>>1;
	solve(l,mid,now+1,cnt);
	solve(mid+1,r,now+1,cnt);
}

int main()
{
//	freopen("hnoi2010_city.in","r",stdin);
//	freopen("hnoi2010_city.out","w",stdout);
	int u,v,x,y;
	read(n),read(m),read(Q);
	for(int i=1;i<=m;i++)
	{
		read(x),read(y),read(a[i]);
		e[0][i]=(edge){x,y,a[i],i};
	}
	for(int i=1;i<=Q;i++)
		read(q[i].x),read(q[i].y);
	sum[0]=m,solve(1,Q,0,0);
	for(int i=1;i<=Q;i++) printf("%lld\n",ans[i]);
	return 0;
}
