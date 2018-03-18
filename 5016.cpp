#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=5e4+5+5;

struct QueryType
{
	int l,r,id,key,d;
	
	bool operator<(const QueryType &tmp)const
	{
		if(key==tmp.key)
			return r<tmp.r;
		return key<tmp.key;
	}
};

struct QueryType qu[maxn<<2|1];

int n,q,m,bel[maxn],ai[maxn];

bool vis[maxn];

ll ans[maxn],num1[maxn],num2[maxn],count;

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

inline void updateR(int x,bool d)
{
	if(!x)
		return;
	x=ai[x];
	if(d)
	{
		count+=num1[x];
		num2[x]++;
	}
	else
	{
		count-=num1[x];
		num2[x]--;
	}
}

inline void updateL(int x,bool d)
{
	if(!x)
		return;
	x=ai[x];
	if(d)
	{
		count+=num2[x];
		num1[x]++;
	}
	else
	{
		count-=num2[x];
		num1[x]--;
	}
}

int main()
{
	read(n);
	int BlockSize=std::sqrt(n);
	for(int i=1;i<=n;i++)
	{
		read(ai[i]);
		bel[i]=i/BlockSize+1;
	}
	bel[0]=1;
	read(q);
	for(int i=1,l1,r1,l2,r2;i<=q;i++)
	{
		read(l1);
		read(r1);
		read(l2);
		read(r2);
		++m;
		qu[m].l=r1;
		qu[m].r=r2;
		qu[m].key=bel[r1];
		qu[m].id=i;
		qu[m].d=1;
		++m;
		qu[m].l=l1-1;
		qu[m].r=r2;
		qu[m].key=bel[l1-1];
		qu[m].id=i;
		qu[m].d=-1;
		++m;
		qu[m].l=r1;
		qu[m].r=l2-1;
		qu[m].key=bel[r1];
		qu[m].id=i;
		qu[m].d=-1;
		++m;
		qu[m].l=l1-1;
		qu[m].r=l2-1;
		qu[m].key=bel[l1-1];
		qu[m].id=i;
		qu[m].d=1;
	}
	std::sort(qu+1,qu+m+1);
	int l=0,r=0;
	for(int i=1;i<=m;i++)
	{
		while(r<qu[i].r)
			updateR(++r,true);
		while(r>qu[i].r)
			updateR(r--,false);
		while(l<qu[i].l)
			updateL(++l,true);
		while(l>qu[i].l)
			updateL(l--,false);
		ans[qu[i].id]+=count*qu[i].d;
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
