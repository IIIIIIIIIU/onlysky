#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e3+5;
int n,k,cnt;
ll L,R,a[maxn],b[maxn],p[maxn];
bool vis[maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')
		if(Cget=='-')
			if_z=-1;
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}
inline void read(ll &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')
		if(Cget=='-')
			if_z=-1;
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}
ll solve(ll x)
{
	if(x==-1)
			return -1;
	ll res=0,ans=0;
	for(int i=1;i<=cnt;i++)
		if(res+p[i]<=x)
		{
			res+=p[i];
			ans+=(1LL<<cnt-i);
		}
	return ans;
}
int main()
{
	read(n);
	read(k);
	read(L);
	read(R);
	ll end=(1LL<<k)-1;
	for(int i=1;i<=n;i++)
		read(a[i]);
	ll now=0;
	for(int i=k-1;i>=0;i--)
		if(!vis[i])
		{
			now=end;
			for(int j=1;j<=n;j++)
				if((a[j]>>i)&1)
					now&=a[j];
				else now&=(~a[j]);
			for(int j=0;j<=i;j++)
				if((now>>j)&1)
					vis[j]=1;
			p[++cnt]=now;
		}
	std::cout<<solve(R)-solve(L-1);
	return 0;
}
