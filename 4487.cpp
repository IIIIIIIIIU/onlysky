#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e9+7;
const int maxn=4e2+5;

int n,m,c;

ll C[maxn][maxn],one[maxn*10],kop[maxn*maxn];

inline ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			res=(res*x)%mod;
		x=(x*x)%mod;
		e>>=1;
	}
	return res;
}

void pre()
{
	C[0][0]=1;
	int lit=std::max(n,std::max(m,c));
	for(int i=1;i<=lit;i++)
	{
		C[i][0]=1;
		for(int v=1;v<=lit;v++)
			C[i][v]=(C[i-1][v]+C[i-1][v-1])%mod;
	}
	one[0]=1;
	for(int i=1;i<=lit*3;i++)
		one[i]=-one[i-1];
}

int main()
{
	ll ans=0;
	std::cin>>n>>m>>c;
	pre();
	int t=n+m+c;
	for(int k=0;k<=c;k++)
	{
		kop[0]=1;
		for(int i=1,lit=n*m;i<=lit;i++)
			kop[i]=kop[i-1]*(k+1)%mod;
		for(int i=0;i<=n;i++)
			for(int v=0;v<=m;v++)
				(ans+=C[n][i]*C[m][v]%mod*C[c][k]%mod*one[t-i-k-v]*kop[i*v]%mod)%=mod;
	}
	std::cout<<(ans+mod)%mod<<std::endl;
	return 0;
}
