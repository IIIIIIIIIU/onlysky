#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=3e5+5;
const int maxtree=maxn<<2|1;
const int INF=0x3f3f3f3f;

struct OperationType
{
	char op[3];
	
	int x,v;
};

struct OperationType operation[maxn];

int n,m,ai[maxn],f[maxn],id[maxn],cnt;
int tmpdis[maxn],L[maxtree],R[maxtree],mid[maxtree];
int tag[maxtree],val[maxtree],pre[maxn],suf[maxn],st[maxn],end[maxn];

inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')
		if(Cget=='-')
			if_z=-1;
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}

inline int find(int x)
{
	if(x==f[x])
		return x;
	return find(f[x]);
}

void merge(int x,int y)
{
	x=find(x);
	y=find(y);
	if(x!=y)
	{
		f[y]=x;
		suf[end[x]]=st[y];
		pre[st[y]]=end[x];
		end[x]=end[y];
	}
}

void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	if(l==r)
	{
		val[now]=tmpdis[l];
		return;
	}
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
	if(val[now<<1]>val[now<<1|1])
		val[now]=val[now<<1];
	else
		val[now]=val[now<<1|1];
}

void pushdown(int now)
{
	val[now<<1]+=tag[now];
	val[now<<1|1]+=tag[now];
	tag[now<<1]+=tag[now];
	tag[now<<1|1]+=tag[now];
	tag[now]=0;
}

void updata(int now,int l,int r,int x)
{
	if(L[now]>=l&&R[now]<=r)
	{
		val[now]+=x;
		tag[now]+=x;
		return;
	}
	if(tag[now])
		pushdown(now);
	if(l<=mid[now])
		updata(now<<1,l,r,x);
	if(r>mid[now])
		updata(now<<1|1,l,r,x);
	if(val[now<<1]>val[now<<1|1])
		val[now]=val[now<<1];
	else
		val[now]=val[now<<1|1];
}

int query(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
		return val[now];
	if(tag[now])
		pushdown(now);
	int res=-INF;
	if(l<=mid[now])
		res=query(now<<1,l,r);
	if(r>mid[now])
		res=std::max(query(now<<1|1,l,r),res);
	return res;
}

int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(ai[i]);
		f[i]=i;
		st[i]=i;
		end[i]=i;
	}
	read(m);
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%s",operation[i].op);
		if(operation[i].op[0]=='A')
		{
			if(operation[i].op[1]=='1')
			{
				read(operation[i].x);
				read(operation[i].v);
			}
			else if(operation[i].op[1]=='2')
			{
				read(operation[i].x);
				read(operation[i].v);
			}
			else
				read(operation[i].v);
		}
		if(operation[i].op[0]=='U')
		{
			read(operation[i].x);
			read(operation[i].v);
			x=operation[i].x;
			y=operation[i].v;
			if(x!=y)
				merge(x,y);
		}
		if(operation[i].op[0]=='F')
		{
			if(operation[i].op[1]=='1')
				read(operation[i].x);
			else if(operation[i].op[1]=='2')
				read(operation[i].x);
		}
	}
	for(int i=1;i<=n;i++)
		if(!pre[i])
		{
			int now=i;
			while(now)
			{
				id[now]=++cnt;
				tmpdis[cnt]=ai[now];
				now=suf[now];
			}
		}
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		st[i]=i;
		end[i]=i;
		pre[i]=0;
		suf[i]=0;
		f[i]=i;
	}
	for(int i=1,x,y;i<=m;i++)
	{
		if(operation[i].op[0]=='U')
			merge(operation[i].x,operation[i].v);
		if(operation[i].op[0]=='A')
		{
			if(operation[i].op[1]=='1')
				updata(1,id[operation[i].x],id[operation[i].x],operation[i].v);
			else if(operation[i].op[1]=='2')
				updata(1,id[st[find(operation[i].x)]],id[end[find(operation[i].x)]],operation[i].v);
			else
				updata(1,1,n,operation[i].v);
		}
		if(operation[i].op[0]=='F')
		{
			if(operation[i].op[1]=='1')
				printf("%d\n",query(1,id[operation[i].x],id[operation[i].x]));
			else if(operation[i].op[1]=='2')
				printf("%d\n",query(1,id[st[find(operation[i].x)]],id[end[find(operation[i].x)]]));
			else
				printf("%d\n",query(1,1,n));
		}
	}
	return 0;
}
