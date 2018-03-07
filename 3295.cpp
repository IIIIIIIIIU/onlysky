#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e5+5;

struct node
{
	int t,p,v;
	
	ll f;
	
	inline bool operator<(const node &tmp)const
	{
		return t<tmp.t;
	}
};

struct node ai[maxn],bi[maxn];

int n,m,tree[maxn],num,ci[maxn],pi[maxn];

ll count[maxn];

inline void update(int pos,int x)
{
	while(pos<=n)
	{
		tree[pos]+=x;
		pos+=(pos&(-pos));
	}
}

inline ll query(int pos)
{
	ll res=0;
	while(pos>0)
	{
		res+=tree[pos];
		pos-=(pos&(-pos));
	}
	return res;
}

inline ll query(int l,int r)
{
	if(l>r)
		return 0;
	return query(r)-query(l-1);
}

void solve(int l,int r)
{
	if(l==r)
		return;
	int mid=l+r>>1;
	solve(l,mid);
	solve(mid+1,r);
	int pos=l;
	for(int i=mid+1;i<=r;i++)
	{
		while(pos<=mid&&ai[pos].p<ai[i].p)
			update(ai[pos++].v,1);
		ai[i].f+=query(ai[i].v+1,n);
	}
	while(pos>l)
		update(ai[--pos].v,-1);
	pos=mid;
	for(int i=r;i>mid;i--)
	{
		while(pos>=l&&ai[pos].p>ai[i].p)
			update(ai[pos--].v,1);
		ai[i].f+=query(1,ai[i].v-1);
	}
	while(pos<mid)
		update(ai[++pos].v,-1);
	int tl=l,tr=mid+1;
	pos=l;
	while(tl<=mid&&tr<=r)
		if(ai[tl].p<ai[tr].p)
			bi[pos++]=ai[tl++];
		else
			bi[pos++]=ai[tr++];
	while(tl<=mid)
		bi[pos++]=ai[tl++];
	while(tr<=r)
		bi[pos++]=ai[tr++];
	for(int i=l;i<=r;i++)
		ai[i]=bi[i];
}

ll getIt()
{
	ll res=0;
	for(int i=1;i<=num;i++)
	{
		res+=query(ci[i]+1,n);
		update(ci[i],1);
	}
	memset(tree,0,sizeof(tree));
	return res;
}

int main()
{
//	freopen("data.txt","r",stdin);
//	freopen("inverse.in","r",stdin);
//	freopen("inverse.out","w",stdout);
	std::cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		ai[i].p=i;
		std::cin>>ai[i].v;
		pi[ai[i].v]=i;
	}
	for(int i=m,x;i>=1;i--)
	{
		std::cin>>x;
		ai[pi[x]].t=n-m+i;
	}
	for(int i=1;i<=n;i++)
		if(ai[i].t==0)
			ci[++num]=ai[i].v;
	int t=0;
	for(int i=1;i<=n;i++)
		if(ai[i].t==0)
			ai[i].t=++t;
	if(num)
		count[n-m]=getIt();
	std::sort(ai+1,ai+n+1);
	solve(1,n);
	for(int i=1;i<=n;i++)
		if(ai[i].t>n-m)
			count[ai[i].t]+=ai[i].f;
	for(int i=n-m+1;i<=n;i++)
		count[i]+=count[i-1];
	for(int i=n;i>n-m;i--)
		printf("%lld\n",count[i]);
	return 0;
}
