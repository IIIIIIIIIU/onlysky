#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e5+5;

int n,pos[maxn],num;

ll ai[maxn],bi[maxn],ans;

inline void read(ll &now)
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

inline ll gcd(ll a,ll b)
{
	return !b?a:gcd(b,a%b);
}

int main()
{
	std::cin>>n;
	for(int i=1;i<=n;i++)
	{
		read(ai[i]);
		bi[++num]=ai[i];
		pos[num]=i;
		for(int v=1;v<num;v++)
			bi[v]=gcd(bi[v],ai[i]);
		int t=1;
		if(bi[1]*i>ans)
			ans=bi[1]*i;
		for(int v=2;v<=num;v++)
			if(bi[v]!=bi[v-1])
			{
				bi[++t]=bi[v];
				pos[t]=pos[v];
				if((i-pos[t]+1)*bi[t]>ans)
					ans=bi[t]*(i-pos[t]+1);
			}
		num=t;
	}
	std::cout<<ans<<std::endl;
	return 0;
}
