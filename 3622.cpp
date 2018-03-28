#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e9+9;
const int maxn=2e3+5;

int n,m,A[maxn],B[maxn];

ll f[maxn][maxn],dp[maxn],C[maxn][maxn],fac[maxn];

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

int main()
{
	read(n);
	read(m);
	m=(m+n)>>1;
	for(int i=1;i<=n;i++)
		read(A[i]);
	for(int i=1;i<=n;i++)
		read(B[i]);
	std::sort(A+1,A+n+1);
	std::sort(B+1,B+n+1);
	int p=0;
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		while(p<n&&B[p+1]<A[i])
			++p;
		f[i][0]=1;
		for(int v=1;v<=n;v++)
			f[i][v]=(f[i-1][v]+f[i-1][v-1]*std::max(p-v+1,0))%mod;
	}
	C[0][0]=1;
	fac[0]=1;
	for(int i=1;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		C[i][0]=1;
		for(int v=1;v<=i;v++)
			C[i][v]=(C[i-1][v]+C[i-1][v-1])%mod;
	}
	for(int i=n;i>=m;i--)
	{
		dp[i]=f[n][i]*fac[n-i]%mod;
		for(int v=i+1;v<=n;v++)
			(dp[i]-=C[v][i]*dp[v]%mod)%=mod;
		dp[i]=(dp[i]+mod)%mod;
	}
	std::cout<<dp[m]<<std::endl;
	return 0;
}
