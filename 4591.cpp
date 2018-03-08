#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=2333;

ll t,N,K,S[mod+1][mod+1],C[mod+1][mod+1];

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

void pre()
{
	for(int i=0;i<=mod;i++)
	{
		C[i][0]=1;
		S[i][0]=1;
		for(int v=1;v<=i;v++)
		{
			C[i][v]=(C[i-1][v-1]+C[i-1][v])%mod;
			S[i][v]=(S[i][v-1]+C[i][v])%mod;
		}
		for(int v=i+1;v<=mod;v++)
			S[i][v]=S[i][v-1];
	}
}

ll getC(ll n,ll k)
{
	if(!k)
		return 1;
	if(k>n)
		return 0;
	if(n<mod&&k<mod)
		return C[n][k];
	return getC(n/mod,k/mod)*getC(n%mod,k%mod)%mod;
}

ll getS(ll n,ll k)
{
	if(k<0)
		return 0;
	if(n<=mod&&k<=mod)
		return S[n][k];
	return ((getS(n/mod,k/mod-1)*getS(n%mod,mod-1)%mod)+(getC(n/mod,k/mod)*getS(n%mod,k%mod))%mod)%mod;
}

int main()
{
	pre();
	read(t);
	while(t--)
	{
		read(N);
		read(K);
		printf("%lld\n",getS(N,K));
	}
	return 0;
}
