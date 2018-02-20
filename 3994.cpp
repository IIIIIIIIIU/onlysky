#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=5e4+5;
int mu[maxn],pi[maxn],num;
ll f[maxn];
bool vis[maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	while((!isdigit(Cget=getchar())));
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}
void pre()
{
	mu[1]=1;
	f[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(!vis[i])
		{
			pi[++num]=i;
			mu[i]=-1;
		}
		for(int v=1;v<=num&&pi[v]*i<maxn;v++)
		{
			vis[pi[v]*i]=true;
			if(i%pi[v]==0)
				break;
			mu[i*pi[v]]=-mu[i];
		}
		for(int v=1,nxt;v<=i;v=nxt+1)
		{
			nxt=i/(i/v);
			f[i]+=(nxt-v+1)*(i/v);
		}
	}
	for(int i=2;i<maxn;i++)
		mu[i]+=mu[i-1];
}
int main()
{
	pre();
	int T;
	read(T);
	while(T--)
	{
		int n,m;
		read(n);
		read(m);
		if(n>m)
			std::swap(n,m);
		ll ans=0;
		for(int i=1,nxt;i<=n;i=nxt+1)
		{
			nxt=std::min(n/(n/i),m/(m/i));
			ans+=f[n/i]*f[m/i]*(mu[nxt]-mu[i-1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
