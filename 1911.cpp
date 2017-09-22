#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long long ll;

const ll maxn=1000005;

ll n,sum[maxn],A,B,C,que[maxn],dp[maxn];

inline void read(ll &now)
{
	char Cget;now=0;ll if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
	now*=if_z;
}

inline bool G(ll j,ll v,ll i)
{
	return dp[j]-dp[v]+A*sum[j]*sum[j]-A*sum[v]*sum[v]-B*sum[j]+B*sum[v]<=2*A*sum[i]*(sum[j]-sum[v]);
}

inline real g(ll j,ll v)
{
	return (1.0*dp[j]-dp[v]+A*sum[j]*sum[j]-A*sum[v]*sum[v]-B*sum[j]+B*sum[v])/(sum[j]-sum[v]);
}

int main()
{
	read(n),read(A),read(B),read(C);
	for(ll i=1;i<=n;i++)
	{
		read(sum[i]);
		sum[i]+=sum[i-1];
	}
	ll h=0,tail=0;
	for(ll i=1;i<=n;i++)
	{
		while(h<tail&&G(que[h],que[h+1],i)) ++h;
		ll v=que[h];
		dp[i]=A*(sum[i]-sum[v])*(sum[i]-sum[v])+B*(sum[i]-sum[v])+C+dp[v];
		while(h<tail&&g(que[tail-1],i)<=g(que[tail],i)) --tail;
		que[++tail]=i;
	}
	std::cout<<dp[n];
	return 0;
}
