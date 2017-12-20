#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e7+5;
int n,prime[maxn],tot;
bool vis[maxn];
ll ans,phi[maxn];
void getphi(int lit)
{
	phi[1]=1;
	for(int i=2,v;i<=lit;i++)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(v=1;v<=tot;v++)
		{
			if(i*prime[v]>lit)
				break;
			vis[i*prime[v]]=true;
			if(i%prime[v]==0)
			{
				phi[i*prime[v]]=prime[v]*phi[i];
				break;
			}
			else
				phi[i*prime[v]]=phi[i]*(prime[v]-1);
		}
	}
}
int main()
{
	std::cin>>n;
	getphi(n);
	for(int i=2;i<=n;i++)
		phi[i]+=phi[i-1];
	for(int i=1;i<=tot&&prime[i]<=n;i++)
			ans+=phi[n/prime[i]]*2-1;
	std::cout<<ans;
	return 0;
}
