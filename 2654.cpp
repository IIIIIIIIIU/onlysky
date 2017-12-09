#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e5+5;

struct EdgeType
{
	ll u,v,w,t;
	
	bool operator<(const EdgeType &tmp)const
	{
		if(w==tmp.w)
			return t<tmp.t;
		return w<tmp.w;
	}
};

struct EdgeType Base[maxn],edge[maxn];

ll n,ans,m,need,cnt,f[maxn];

inline void read(ll &now)
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

ll find(ll x)
{
	if(f[x]==x)
		return x;
	return f[x]=find(f[x]);
}

ll getdis(ll x)
{
	cnt=0;
	for(ll i=1;i<=m;i++)
	{
		edge[i]=Base[i];
		if(!edge[i].t)
			edge[i].w+=x;
	}
	std::sort(edge+1,edge+m+1);
	for(ll i=0;i<=n;i++)
		f[i]=i;
	ll res=0;
	for(ll i=1,x,y;i<=m;i++)
	{
		x=find(edge[i].u);
		y=find(edge[i].v);
		if(x!=y)
		{
			f[x]=y;
			if(!edge[i].t)
				cnt++;
			res+=edge[i].w;
		}
	}
	return res;
}

int main()
{
	read(n);
	read(m);
	read(need);
	for(ll i=1;i<=m;i++)
	{
		read(Base[i].u);
		read(Base[i].v);
		read(Base[i].w);
		read(Base[i].t);
	}
	ll l=-10000,r=10000,mid,res=1e15,x;
	while(l<=r)
	{
		mid=l+r>>1;
		x=getdis(mid);
		if(cnt>=need)
		{
			res=std::min(res,x-mid*need);
			l=mid+1;
		}
		else
			r=mid-1;
	}
	std::cout<<res;
	return 0;
}
