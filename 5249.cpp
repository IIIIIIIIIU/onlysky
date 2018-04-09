#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const int maxn=5e5+5;
const int maxtree=maxn<<2|1;

int n,f[maxn],size[maxn],ai[maxn],bi[maxn],num;
int cnt[maxn],sum[maxtree],val[maxtree],ans[maxn];
int L[maxtree],R[maxtree],mid[maxtree];

real k;

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

inline int min(const int &a,const int &b)
{
	return a<b?a:b;
}

void build(const int &now,const int &l,const int &r)
{
	L[now]=l;
	R[now]=r;
	if(l==r)
	{
		val[now]=0;
		sum[now]=cnt[l];
		return;
	}
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
	sum[now]=sum[now<<1]+sum[now<<1|1];
	val[now]=min(val[now<<1]+sum[now<<1|1],val[now<<1|1]);
}

inline void update(const int &now,const int &to,const int &x)
{
	if(L[now]==R[now])
	{
		sum[now]+=x;
		val[now]=min(0,sum[now]);
		return;
	}
	if(to<=mid[now])
		update(now<<1,to,x);
	else
		update(now<<1|1,to,x);
	sum[now]=sum[now<<1]+sum[now<<1|1];
	val[now]=min(val[now<<1]+sum[now<<1|1],val[now<<1|1]);
}

inline bool check(const int &to,const int &x)
{
	update(1,to,-x);
	bool res=(val[1]>=0);
	update(1,to,x);
	return res;
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	scanf("%lf",&k);
	for(int i=1;i<=n;i++)
	{
		f[i]=i/k+1e-5;
		read(ai[i]);
		bi[i]=ai[i];
	}
	bi[num=n+1]=1;
	std::sort(bi+1,bi+num+1);
	num=std::unique(bi+1,bi+num+1)-bi-1;
	cnt[1]=1;
	for(int i=1;i<=n;i++)
		++cnt[ai[i]=std::lower_bound(bi+1,bi+num+1,ai[i])-bi];
	for(int i=n;i>=1;i--)
		size[f[i]]+=++size[i];
	++size[0];
	build(1,1,num);
	update(1,1,-size[0]);
	ans[0]=1;
	for(int i=1;i<=n;i++)
	{
		int l=ans[f[i]],r=num,mid;
		update(1,ans[f[i]],size[i]);
		while(l<=r)
		{
			mid=l+r>>1;
			if(check(mid,size[i]))
			{
				ans[i]=mid;
				l=mid+1;
			}
			else
				r=mid-1;
		}
		update(1,ans[i],-size[i]);
	}
	for(int i=1;i<=n;i++)
		printf("%d ",bi[ans[i]]);
	return 0;
}
