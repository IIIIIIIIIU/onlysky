#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=15;
const int mod=1e9+7;

int n,m,out[maxn+1],num[1<<maxn];

ll g[1<<maxn],f[1<<maxn],poww[maxn*maxn+1],h[1<<maxn];

inline int CountingPath(int s,int t)
{
	int res=0;
	for(int i=1,v=1;i<=n;i++,v<<=1)
		if(s&v)
			res+=num[out[i]&t];
	return res;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		out[u]|=(1<<(v-1));
	}
	poww[0]=1;
	for(int i=1;i<=m;i++)
		poww[i]=(poww[i-1]<<1)%mod;
	for(int i=1;i<(1<<n);i++)
		num[i]=num[i>>1]+(i&1);
	for(int s=1,u,v;s<(1<<n);s++)
	{
		u=(s&(-s));
		v=(s^u);
		for(int i=v;i!=0;i=(i-1)&v)
			(g[s]-=f[s^i]*g[i])%=mod;
		f[s]=poww[h[s]=CountingPath(s,s)];
		for(int i=s;i!=0;i=(i-1)&s)
			(f[s]-=poww[CountingPath(i,s-i)+h[s-i]]*g[i]%mod)%=mod;
		(g[s]=f[s]+g[s])%=mod;
	}
	std::cout<<(f[(1<<n)-1]+mod)%mod<<std::endl;
	return 0;
}
