#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e6+5;
struct QueryType
{
	int l,r,id;
	bool operator<(const QueryType &tmp)const
	{
		return r<tmp.r;
	}
};
struct QueryType qu[maxn];
int n,c,ci[maxn],m,ppre[maxn],pre[maxn],last[maxn];
int tree[maxn],ans[maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}
inline void add(int to,int x)
{
	while(to<=n)
	{
		tree[to]+=x;
		to+=(to&(-to));
	}
}
inline int query(int l)
{
	int res=0;
	while(l>0)
	{
		res+=tree[l];
		l-=(l&(-l));
	}
	return res;
}
void updata(int x)
{
	int l=ppre[x]+1;
	int r=pre[x];
	if(l<=r)
	{
		add(l,1);
		add(r+1,-1);
	}
}
int main()
{
	//freopen("1flower.in","r",stdin);
	//freopen("1flower.out","w",stdout);
	read(n);
	read(c);
	read(m);
	for(int i=1;i<=n;i++)
	{
		read(ci[i]);
		pre[i]=last[ci[i]];
		ppre[i]=pre[pre[i]];
		last[ci[i]]=i;
	}
	for(int i=1;i<=m;i++)
	{
		read(qu[i].l);
		read(qu[i].r);
		qu[i].id=i;
	}
	std::sort(qu+1,qu+m+1);
	for(int i=1,x=0;i<=m;i++)
	{
		while(x<qu[i].r)
			updata(++x);
		ans[qu[i].id]=query(qu[i].l);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
