#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef double real;
typedef long long ll;
const ll INF=1e18;
const int maxn=2e5+5;
const int maxtree=maxn<<2|1;
struct node
{
	real x,y;
	node(){}
	node(const ll &x_,const ll &y_)
	{
		x=x_;
		y=y_;
	}
	inline node operator-(const node &tmp)const
	{
		return node(x-tmp.x,y-tmp.y);
	}
	inline real operator*(const node &tmp)const
	{
		return x*tmp.y-y*tmp.x;
	}
};
int n,type,L[maxtree],R[maxtree],mid[maxtree];
int vec[maxn*20],*val[maxtree],tot,f[maxn],deep[maxn];
int id[maxn],back[maxn],size[maxn],head[maxn],E[maxn<<1];
int V[maxn<<1],cnt,lar[maxn],top[maxn],len[maxtree];
int num[maxtree],len2[maxtree],sta[maxn],Ans1,Ans2;
ll dis[maxn],di[maxn],pi[maxn],qi[maxn],g[maxn];
ll li[maxn];
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
inline void read(ll &now)
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
void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	val[now]=vec+tot;
	tot+=r-l+1;
	len[now]=r-l+1;
	if(l==r)
		return;
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
}
void dfs1(int now)
{
	size[now]=1;
	deep[now]=deep[f[now]]+1;
	dis[now]=dis[f[now]]+di[now];
	for(int i=head[now];i!=0;i=E[i])
	{
		dfs1(V[i]);
		size[now]+=size[V[i]];
		if(size[V[i]]>=size[lar[now]])
			lar[now]=V[i];
	}
}
void dfs2(int now,int chain)
{
	id[now]=++cnt;
	back[cnt]=now;
	top[now]=chain;
	if(lar[now])
		dfs2(lar[now],chain);
	for(int i=head[now];i!=0;i=E[i])
		if(lar[now]!=V[i])
			dfs2(V[i],V[i]);
}
int getUp(int x,ll y)
{
	if(y<=0)
		return 1;
	int res=x;
	while(dis[top[x]]>y)
	{
		res=top[x];
		x=f[top[x]];
	}
	int l=id[top[x]],r=x,mid;
	while(l<=r)
	{
		mid=l+r>>1;
		if(dis[back[mid]]>=y)
		{
			res=back[mid];
			r=mid-1;
		}
		else
			l=mid+1;
	}
	return res;
}
inline bool cmp(const int &x,const int &y)
{
	return g[x]<g[y];
}
inline bool compare(int x,int y,int z)
{
	node X=node(g[x],dis[x]);
	node Y=node(g[y],dis[y]);
	node Z=node(g[z],dis[z]);
	Y=Y-X;
	Z=Z-X;
	return Z*Y<=0;
}
void makeit(int now)
{
	std::sort(val[now],val[now]+num[now],cmp);
	int t=0;
	sta[1]=val[now][0];
	sta[t=2]=val[now][1];
	for(int i=2;i<num[now];i++)
	{
		while(t>1&&compare(sta[t-1],sta[t],val[now][i]))
			t--;
		sta[++t]=val[now][i];
	}
	for(int i=1;i<=t;i++)
		val[now][len2[now]++]=sta[i];
}
void add(int now,int to,int x)
{
	val[now][num[now]++]=x;
	if(L[now]==R[now])
	{
		len2[now]=1;
		return;
	}
	if(to<=mid[now])
		add(now<<1,to,x);
	else
		add(now<<1|1,to,x);
	if(num[now]==len[now])
		makeit(now);
}
void threeD(int now)
{
	if(len2[now]<=3)
	{
		for(int i=0;i<len2[now];i++)
		{
			if(Ans2*dis[val[now][i]]-g[val[now][i]]>Ans2*dis[Ans1]-g[Ans1])
				Ans1=val[now][i];
		}
		return;
	}
	int l=0,r=len2[now]-1,mid1,mid2,res;
	while(r-l>=3)
	{
		mid1=l+(r-l)/3;
		mid2=r-(r-l)/3;
		if(Ans2*dis[val[now][mid1]]-g[val[now][mid1]]>Ans2*dis[val[now][mid2]]-g[val[now][mid2]])
			r=mid2;
		else
			l=mid1;
	}
	for(int i=l;i<=r;i++)
		if(Ans2*dis[val[now][i]]-g[val[now][i]]>Ans2*dis[Ans1]-g[Ans1])
			Ans1=val[now][i];
}
void query(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
	{
		threeD(now);
		return;
	}
	if(l<=mid[now])
		query(now<<1,l,r);
	if(r>mid[now])
		query(now<<1|1,l,r);
}
ll getAns(int now,int to)
{
	Ans1=f[now];
	Ans2=pi[now];
	int t=f[now];
	while(top[t]!=top[to])
	{
		query(1,id[top[t]],id[t]);
		t=f[top[t]];
	}
	query(1,id[to],id[t]);
	return (dis[now]-dis[Ans1])*pi[now]+g[Ans1]+qi[now];
}
int main()
{
	read(n);
	read(type);
	for(int i=2;i<=n;i++)
	{
		read(f[i]);
		read(di[i]);
		read(pi[i]);
		read(qi[i]);
		read(li[i]);
		E[++cnt]=head[f[i]];
		V[cnt]=i;
		head[f[i]]=cnt;
	}
	cnt=0;
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	add(1,1,1);
	for(int i=2;i<=n;i++)
	{
		int x=getUp(i,dis[i]-li[i]);
		g[i]=getAns(i,x);
		printf("%lld\n",g[i]);
		add(1,id[i],i);
	}
	return 0;
}
