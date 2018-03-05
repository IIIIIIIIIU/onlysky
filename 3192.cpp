#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e5+5;

struct node
{
	int pos,key;
	
	inline bool operator<(const node &tmp)const
	{
		return key>tmp.key;
	}
};

struct node ai[maxn];

int n,m,top,tree[maxn];

void add(int pos,int x)
{
	while(pos<=n+m)
	{
		tree[pos]+=x;
		pos+=(pos&(-pos));
	}
}

int query(int pos)
{
	if(pos<=0)
		return 0;
	int res=0;
	while(pos)
	{
		res+=tree[pos];
		pos-=(pos&(-pos));
	}
	return res;
}

int query(int l,int r)
{
	if(l>r)
		return 0;
	return query(r)-query(l-1);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=n;i>=1;i--)
	{
		scanf("%d",&ai[i].key);
		ai[i].pos=i;
	}
	for(int i=n+1;i<=n+m;i++)
	{
		scanf("%d",&ai[i].key);
		ai[i].pos=i;
	}
	std::sort(ai+1,ai+n+m+1);
	top=n;
	for(int i=1;i<=n+m;i++)
		add(i,1);
	long long ans=0;
	for(int i=1,pos;i<=n+m;i++)
	{
		pos=ai[i].pos;
		if(pos<=top)
		{
			ans+=query(pos+1,top);
			top=pos;
		}
		else
		{
			ans+=query(top+1,pos-1);
			top=pos-1;
		}
		add(pos,-1);
	}
	std::cout<<ans;
	return 0;
}
