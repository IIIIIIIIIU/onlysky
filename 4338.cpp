#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e5+5;
const int maxp=1e4+5;
int n,m,p,k,u[maxn],d[maxn],tot,pi[maxp],whe[maxn];
void init()
{
	scanf("%d%d%d%d",&n,&m,&k,&p);
	for(int i=2;i<=m;i++)
		if(!whe[i])
		{
			pi[tot++]=i;
			for(int v=2;i*v<=m;v++)
				if(!whe[i*v])
					whe[i*v]=1;
		}
}
void work()
{
	for(int i=0;i<m;i++)
	{
		u[i]=k+i;
		d[i]=i+1;
	}
	for(int i=0;i<tot;i++)
	{
		int cnt=0;
		for(int v=pi[i]-1;v<m;v+=pi[i])
			if(d[v]%pi[i]==0)
				while(d[v]%pi[i]==0)
				{
					++cnt;
					d[v]/=pi[i];
				}
		int tak=(k-1)%pi[i]+1;
		for(int v=pi[i]-tak;v<m;v+=pi[i])
			if(u[v]%pi[i]==0)
			{
				while(u[v]%pi[i]==0&&cnt)
				{
					u[v]/=pi[i];
					cnt--;
				}
				if(!cnt)
					break;
			}
	}
	ll st=1;
	for(int i=0;i<m;i++)
		(st*=u[i])%=p;
	if(st<n)
		printf("0\n");
	else
	{
		ll ans=1;
		for(int i=0;i<n;i++)
		{
			(ans*=st)%=p;
			st--;
		}
		printf("%lld\n",ans);
	}
}
int main()
{
	init();
	work();
	return 0;
}
