#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int mod=1e9+7;
const int maxn=1e5+5;
const int maxtree=maxn<<2|1;

int n,ai[maxn],bi[maxn],num,L[maxtree],R[maxtree];
int val[maxtree],last[maxn],mid[maxtree];

void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	if(l==r)
		return ;
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
}

void update(int now,int to,int x)
{
	if(L[now]==R[now])
	{
		(val[now]+=x)%=mod;
		return;
	}
	if(to<=mid[now])
		update(now<<1,to,x);
	else
		update(now<<1|1,to,x);
	val[now]=(val[now<<1]+val[now<<1|1])%mod;
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
		res=(res+query(now<<1|1,l,r))%mod;
	return res;
}

int main()
{
	std::cin>>n;
	for(int i=1;i<=n;i++)
	{
		std::cin>>ai[i];
		bi[i]=ai[i];
	}
	std::sort(bi+1,bi+n+1);
	num=std::unique(bi+1,bi+n+1)-bi-1;
	int ans=0;
	for(int i=1;i<=n;i++)
		ai[i]=std::lower_bound(bi+1,bi+num+1,ai[i])-bi;
	build(1,1,num);
	for(int i=1,t;i<=n;i++)
	{
		t=query(1,1,ai[i]-1)+1;
		update(1,ai[i],t-last[ai[i]]);
		last[ai[i]]=t;
	}
	std::cout<<((val[1]-num)%mod+mod)%mod<<std::endl;
	return 0;
}
