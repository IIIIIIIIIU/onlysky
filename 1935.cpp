#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=500005;

struct QueryType
{
	int u,d,l,r,ans;

	QueryType(int u_=0,int d_=0,int l_=0,int r_=0)
	{
		u=u_,d=d_,l=l_,r=r_,ans=0;
	}
};
struct QueryType Query[maxn];

struct Tree
{
	int x,y;
};
struct Tree tree[maxn];

struct EdgeType
{
	int v;

	bool type;

	EdgeType *next;

	EdgeType(int v_=0,bool type_=false,EdgeType *next_=NULL)
	{
		v=v_,type=type_,next=next_;
	}
};

struct EdgeType *query[maxn],*point[maxn];

int xi[maxn],yi[maxn],cntx,cnty,BIT[maxn],n,m;

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

inline void edge_add(EdgeType *&now ,int v,int type)
{
	now=new EdgeType(v,type,now);
}

#define lowbit(x) (x&(-x))

void BITadd(int x)
{
	while(x<=cntx) BIT[x]++,x+=lowbit(x);
}

int BITquery(int l,int r)
{
	int res=0;
	while(r) res+=BIT[r],r-=lowbit(r);
	while(l) res-=BIT[l],l-=lowbit(l);
	return res;
}

using std::lower_bound;

int main()
{
	freopen("data.txt","r",stdin);
	read(n),read(m);
	for(int i=1;i<=n;i++)
	{
		read(tree[i].x),read(tree[i].y);
		xi[i]=tree[i].x,yi[i]=tree[i].y;
	}
	std::sort(xi+1,xi+n+1),cntx=std::unique(xi+1,xi+n+1)-xi-1;
	std::sort(yi+1,yi+n+1),cnty=std::unique(yi+1,yi+n+1)-yi-1;
	for(int i=1;i<=n;i++)
	{
		tree[i].x=lower_bound(xi+1,xi+cntx+1,tree[i].x)-xi;
		tree[i].y=lower_bound(yi+1,yi+cnty+1,tree[i].y)-yi;
	}
	int u,d,l,r;
	for(int i=0;i<=n;i++) query[i]=point[i]=NULL;
	for(int i=1;i<=m;i++)
	{
		read(l),read(u),read(r),read(d);
		u=lower_bound(yi+1,yi+cnty+1,u)-yi-1;
		int tmp=lower_bound(yi+1,yi+cnty+1,d)-yi;
		if(d!=yi[tmp]) tmp--;
		d=tmp;
		l=lower_bound(xi+1,xi+cntx+1,l)-xi-1;
		tmp=lower_bound(xi+1,xi+cntx+1,r)-xi;
		if(xi[tmp]!=r) tmp--;
		r=tmp;
		Query[i]=QueryType(u,d,l,r);
		edge_add(query[u],i,false);
		edge_add(query[d],i,true);
	}
	for(int i=1;i<=n;i++) edge_add(point[tree[i].y],tree[i].x,false);
	for(int v=0;v<=cnty;v++)
	{
		for(EdgeType *i=point[v];i!=NULL;i=i->next) BITadd(i->v);
		for(EdgeType *i=query[v];i!=NULL;i=i->next)
		{
			u=i->v;
			l=Query[u].l,r=Query[u].r;
			if(i->type) Query[u].ans+=BITquery(l,r);
			else Query[u].ans-=BITquery(l,r);
		}
	}
	for(int i=1;i<=m;i++) printf("%d\n",Query[i].ans);
	return 0;
}
