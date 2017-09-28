#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=300005,maxm=1000005,maxtree=maxn<<2|1;

class Uni
{
	private:
		int f[maxn];

		int find(int x)
		{
			if(x==f[x]) return f[x];
			return f[x]=find(f[x]);
		}

	public:
		void makeit(int n)
		{
			for(int i=1;i<=n;i++) f[i]=i;
		}

		bool connect(int x,int y)
		{
			return find(x)==find(y);
		}

		void merge(int x,int y)
		{
			x=find(x),y=find(y);
			f[x]=y;
		}
};

class Uni U;

struct EdgeType
{
	int v;

	EdgeType *next;

	EdgeType(int v_,EdgeType *next_=NULL)
	{
		v=v_,next=next_;
	}
};

struct EdgeType *head[maxn];

struct Data_Edge
{
	int u,v;

	Data_Edge(int u_=0,int v_=0)
	{
		if(v_>u_) std::swap(v_,u_);
		u=u_,v=v_;
	}

	bool operator<(const Data_Edge &tmp)const
	{
		if(u==tmp.u) return v<tmp.v;
		return u<tmp.u;
	}
};

struct Data_Edge Sedge[maxm];

int n,m,deep[maxn],f[maxn],top[maxn],lar[maxn],size[maxn];
int C[maxm],A[maxm],B[maxm],cnt,id[maxn],L[maxtree],R[maxtree];
int mid[maxtree],val[maxtree],tag[maxtree],ans[maxm],cntans;

bool vis[maxn];

inline void read(int &now)
{
	char Cget;now=0;int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
	now*=if_z;
}

void dfs1(int now,int fa)
{
	f[now]=fa,deep[now]=deep[fa]+1,size[now]=1;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->v!=fa)
		{
			dfs1(i->v,now),size[now]+=size[i->v];
			if(size[i->v]>size[lar[now]]) lar[now]=i->v;
		}
}

void dfs2(int now,int chain)
{
	top[now]=chain,id[now]=++cnt;
	if(lar[now]) dfs2(lar[now],chain);
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->v!=f[now]&&i->v!=lar[now]) dfs2(i->v,i->v);
}

void build(int now,int l,int r)
{
	L[now]=l,R[now]=r,val[now]=r-l+1;
	if(l==r) return;mid[now]=l+r>>1;
	build(now<<1,l,mid[now]),build(now<<1|1,mid[now]+1,r);
}

inline void pushdown(int now)
{
	tag[now<<1]=tag[now<<1|1]=true,tag[now]=false;
	val[now<<1]=val[now<<1|1]=0;
}

void updata(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
	{
		val[now]=0,tag[now]=1;
		return;
	}
	if(tag[now]) pushdown(now);
	if(l<=mid[now]) updata(now<<1,l,r);
	if(r>mid[now]) updata(now<<1|1,l,r);
	val[now]=val[now<<1]+val[now<<1|1];
}

int query(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r) return val[now];
	if(tag[now]) pushdown(now);int res=0;
	if(l<=mid[now]) res+=query(now<<1,l,r);
	if(r>mid[now]) res+=query(now<<1|1,l,r);
	return res;
}

void clear(int x,int y)
{
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]]) updata(1,id[top[x]],id[x]),x=f[top[x]];
		else updata(1,id[top[y]],id[y]),y=f[top[y]];
	if(deep[x]>deep[y]) std::swap(x,y);
	if(x!=y) updata(1,id[x]+1,id[y]);
}

int count(int x,int y)
{
	int res=0;
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]]) res+=query(1,id[top[x]],id[x]),x=f[top[x]];
		else res+=query(1,id[top[y]],id[y]),y=f[top[y]];
	if(deep[x]>deep[y]) std::swap(x,y);
	if(x!=y) res+=query(1,id[x]+1,id[y]);
	return res;
}

int main()
{
//	freopen("lane.in","r",stdin);
//	freopen("lane.out","w",stdout);
//	freopen("data.txt","r",stdin);
	read(n),read(m);
	for(int i=1;i<=n;i++) head[i]=NULL;
	int u,v;
	for(int i=1;i<=m;i++)
	{
		read(u),read(v);
		Sedge[i]=Data_Edge(u,v);
	}
	std::sort(Sedge+1,Sedge+m+1);
	read(C[++cnt]);
	while(C[cnt]!=-1)
	{
		read(A[cnt]),read(B[cnt]);
		if(C[cnt]==0) vis[std::lower_bound(Sedge+1,Sedge+m+1,Data_Edge(A[cnt],B[cnt]))-Sedge]=true;
		read(C[++cnt]);
	}
	cnt--;
	int tmp=cnt;
	U.makeit(n);
	for(int i=1;i<=m;i++)
		if(!vis[i]&&!U.connect(Sedge[i].u,Sedge[i].v))
		{
			vis[i]=true;
			u=Sedge[i].u,v=Sedge[i].v;
			head[u]=new EdgeType(v,head[u]);
			head[v]=new EdgeType(u,head[v]);
			U.merge(u,v);
		}
	dfs1(1,0),cnt=0,dfs2(1,1),build(1,1,n);
	for(int i=1;i<=m;i++)
		if(!vis[i])
			clear(Sedge[i].u,Sedge[i].v);
	for(int i=tmp;i>=1;i--)
		if(C[i]==1) ans[++cntans]=count(A[i],B[i]);
		else clear(A[i],B[i]);
	for(int i=cntans;i>=1;i--) printf("%d\n",ans[i]);
	return 0;
}
