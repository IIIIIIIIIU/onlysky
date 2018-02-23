#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=1e9+7;
int n,m,map[21][21][21],num[21],bit[20];
ll C[21][21],f[21],ans;
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
inline ll gcd(ll a,ll b)
{
	if(!b)
		return a;
	return gcd(b,a%b);
}
ll calc()
{
	ll res=1;
	for(int i=1;i<=m;i++)
	{
		for(int v=i+1;v<=m;v++)
			while(C[v][i])
			{
				ll t=C[i][i]/C[v][i];
				for(int k=i;k<=n;k++)
					C[i][k]=(C[i][k]-C[v][k]*t%mod)%mod;
				for(int k=i;k<=n;k++)
					std::swap(C[i][k],C[v][k]);
				res=-res;
			}
		if(!C[i][i])
			return 0;
		res=res*C[i][i]%mod;
	}
	return res;
}
void count(int s)
{
	int tmp=0;
	for(short i=1,v=1;i<=n;i++)
		for(v=1;v<=n;v++)
			C[i][v]=0;
	for(int i=1;i<=m;i++)
		if(bit[i]&s)
		{
			++tmp;
			for(short v=1;v<=n;v++)
				for(short e=1;e<=n;e++)
					if(map[i][v][e])
					{
						C[v][e]--;
						C[v][v]++;
					}
		}
	(f[m-tmp]+=calc())%=mod;
}
int main()
{
	read(n);
	m=n-1;
	for(int i=1;i<=m;i++)
	{
		read(num[i]);
		for(int v=1,y,x;v<=num[i];v++)
		{
			read(x);
			read(y);
			map[i][x][y]++;
			map[i][y][x]++;
		}
	}
	bit[1]=1;
	for(int i=2;i<=m;i++)
		bit[i]=bit[i-1]<<1;
	for(int s=0;s<(1<<m);s++)
		count(s);
	int cnt=1;
	for(int i=0;i<n;i++)
	{
		(ans+=cnt*f[i]%mod)%=mod;
		cnt*=-1;
	}
	std::cout<<(ans+mod)%mod<<std::endl;
	return 0;
}
