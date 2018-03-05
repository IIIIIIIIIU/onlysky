#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e5+5;
const int maxtree=maxn<<2|1;

int n,seq[maxn],L[maxtree],R[maxtree],mid[maxtree];
int ai[maxn],val[maxtree],out[maxn];

void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	if(l==r)
	{
		val[now]=1;
		return;
	}
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
	val[now]=val[now<<1]+val[now<<1|1];
}

int query(int now,int k)
{
	val[now]--;
	if(L[now]==R[now])
		return L[now];
	if(val[now<<1]>=k)
		return query(now<<1,k);
	else
		return query(now<<1|1,k-val[now<<1]);
}

void build(int now)
{
	val[now]=0;
	if(L[now]==R[now])
		return ;
	build(now<<1);
	build(now<<1|1);
}

int query(int now,int l,int r)
{
	if(l>r)
		return 0;
	if(L[now]>=l&&R[now]<=r)
		return val[now];
	int res=0;
	if(l<=mid[now])
		res=query(now<<1,l,r);
	if(r>mid[now])
		res=std::max(res,query(now<<1|1,l,r));
	return res;
}

void update(int now,int to,int x)
{
	if(L[now]==R[now])
	{
		val[now]=x;
		return ;
	}
	if(to<=mid[now])
		update(now<<1,to,x);
	else
		update(now<<1|1,to,x);
	val[now]=std::max(val[now<<1],val[now<<1|1]);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&ai[i]);
	build(1,1,n);
	for(int i=n;i>=1;i--)
		seq[query(1,ai[i]+1)]=i;
	build(1);
	for(int i=1;i<=n;i++)
	{
		out[seq[i]]=query(1,1,seq[i])+1;
		update(1,seq[i],out[seq[i]]);
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",out[i]=std::max(out[i],out[i-1]));
	return 0;
}
