#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=2e5+5;

struct node
{
	ll a;
	int b;
	
	node(){}
	
	node(ll a_,int b_)
	{
		a=a_;
		b=b_;
	}
	
	inline bool operator<(const node &tmp)const
	{
		return a<tmp.a;
	}
	
	inline bool operator==(const node &tmp)const
	{
		return a==tmp.a;
	}
};

int n,m,li[maxn],ri[maxn],lastxor,lastgcd;
int blockSize,bel[maxn],num,ai[maxn],g[maxn],xr[maxn];

std::set<node>Set[1005];

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

inline int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}

int main()
{
//	freopen("data.txt","r",stdin);
	freopen("gcdxor.in","r",stdin);
	freopen("gcdxor.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++)
		read(ai[i]);
	blockSize=std::sqrt(n);
	for(int i=1;i<=n;i++)
	{
		bel[i]=i/blockSize+1;
		num=bel[i];
		if(!li[bel[i]])
			li[bel[i]]=i;
		ri[bel[i]]=i;
	}
	std::set<node>::iterator it;
	for(int i=1;i<=num;i++)
	{
		g[li[i]]=ai[li[i]];
		xr[li[i]]=ai[li[i]];
		Set[i].insert(node(xr[li[i]],li[i]));
		for(int v=li[i]+1;v<=ri[i];v++)
		{
			g[v]=gcd(g[v-1],ai[v]);
			xr[v]=xr[v-1]^ai[v];
			if((it=Set[i].find(node(xr[v],0)))==Set[i].end())
				Set[i].insert(node(xr[v],v));
		}
	}
	read(m);
	char op[25];
	int id,x;
	ll X;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",op);
		if(op[0]=='M')
		{
			read(id);
			id++;
			read(x);
			int b=bel[id];
			Set[b].clear();
			ai[id]=x;
			xr[li[b]]=g[li[b]]=ai[li[b]];
			Set[b].insert(node(xr[li[b]],li[b]));
			for(int v=li[b]+1;v<=ri[b];v++)
			{
				g[v]=gcd(g[v-1],ai[v]);
				xr[v]=xr[v-1]^ai[v];
				if((it=Set[b].find(node(xr[v],0)))==Set[b].end())
					Set[b].insert(node(xr[v],v));
			}
		}
		else
		{
			scanf("%lld",&X);
			lastxor=0;
			lastgcd=ai[1];
			int p=0;
			for(int v=li[1];v<=ri[1];v++)
			{
				lastxor^=ai[v];
				lastgcd=gcd(lastgcd,ai[v]);
				if(X%lastgcd==0&&lastxor==X/lastgcd)
				{
					p=v;
					break;
				}
			}
			if(p)
			{
				printf("%d\n",p-1);
				continue;
			}
			for(int v=2;v<=num;v++)
			{
				if(gcd(lastgcd,g[ri[v]])==lastgcd)
				{
					if(X%lastgcd==0&&(it=Set[v].find(node((X/lastgcd)^lastxor,0)))!=Set[v].end())
					{
						p=it->b;
						break;
					}
					lastxor^=xr[ri[v]];
				}
				else
				{
					for(int e=li[v];e<=ri[v];e++)
					{
						lastxor^=ai[e];
						lastgcd=gcd(lastgcd,ai[e]);
						if(X%lastgcd==0&&lastxor==X/lastgcd)
						{
							p=e;
							break;
						}
					}
					if(p)
						break;
				}
			}
			if(p)
				printf("%d\n",p-1);
			else
				puts("no");
		}
	}
	return 0;
}
