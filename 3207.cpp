#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef unsigned long long ll;

const int maxn=1e5+5;
const int maxtree=maxn*40;
const int mod=1e9+7+998244353;

int n,m,k,root[maxn],ch[maxtree][2],tot,ai[maxn],num;
int val[maxtree];

ll Hash[maxn],bi[maxn];

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

void insert(int &now,int pre,int l,int r,int to)
{
	val[now=++tot]=val[pre]+1;
	if(l==r)
		return;
	int mid=l+r>>1;
	if(to<=mid)
	{
		insert(ch[now][0],ch[pre][0],l,mid,to);
		ch[now][1]=ch[pre][1];
	}
	else
	{
		insert(ch[now][1],ch[pre][1],mid+1,r,to);
		ch[now][0]=ch[pre][0];
	}
}

inline bool query(int now,int pre,int l,int r,int to)
{
	if(!now||val[now]-val[pre]==0)
		return false;
	if(l==r)
		return true;
	int mid=l+r>>1;
	if(to<=mid)
		return query(ch[now][0],ch[pre][0],l,mid,to);
	else
		return query(ch[now][1],ch[pre][1],mid+1,r,to);
}

inline bool query(int l,int r,ll x)
{
	int t=std::lower_bound(bi+1,bi+num+1,x)-bi;
	if(t>num||bi[t]!=x)
		return false;
	return query(root[r],root[l-1],1,num,t);
}

int main()
{
	read(n);
	read(m);
	read(k);
	for(int i=1;i<=n;i++)
		read(ai[i]);
	ll x,th=1;
	for(int i=1;i<=k;i++)
		th=th*mod;
	for(int i=1;i<=n;i++)
	{
		Hash[i]=Hash[i-1]*mod+ai[i];
		if(i>=k)
			bi[++num]=Hash[i]-Hash[i-k]*th;
	}
	std::sort(bi+1,bi+num+1);
	num=std::unique(bi+1,bi+num+1)-bi-1;
	for(int i=k;i<=n;i++)
		insert(root[i],root[i-1],1,num,std::lower_bound(bi+1,bi+num+1,Hash[i]-Hash[i-k]*th)-bi);
	for(int i=1,l,r,t;i<=m;i++)
	{
		read(l);
		read(r);
		x=0;
		for(short v=1;v<=k;v++)
		{
			read(t);
			x=x*mod+t;
		}
		if(l+k-1>r||!query(l+k-1,r,x))
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
