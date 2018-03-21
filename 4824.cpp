#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll mod=1e9+7;
const ll maxn=1e2+5;

ll n,C[maxn][maxn],f[maxn][maxn],sp[maxn][maxn];
ll sf[maxn][maxn],size[maxn];

char s[maxn];

inline void add(ll &x,const ll &y)
{
	if((x+=y)>=mod)
		x-=mod;
}

void pre()
{
	C[0][0]=1;
	for(ll i=1;i<=n;i++)
	{
		C[i][0]=1;
		for(ll j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
}

void dfs(ll x)
{
	size[x]=1;
	ll lc=x<<1,rc=x<<1|1;
	if(lc>n&&rc>n)
		f[x][1]=1;
	else if(lc<=n&&rc>n)
	{
		dfs(lc);
		size[x]+=size[lc];
		f[x][s[lc]=='>'?2:1]=1;
	}
	else
	{
		dfs(lc);
		size[x]+=size[lc];
		dfs(rc);
		size[x]+=size[rc];
		for(ll i=1;i<=size[x];i++)
			for(ll j=0;j<std::min(i,size[lc]+1);j++)
			{
				ll k=i-1-j;
				ll tmp=C[i-1][j]*C[size[x]-i][size[lc]-j]%mod;
				if(s[lc]=='>')
					tmp=tmp*sp[lc][j]%mod;
				else
					tmp=tmp*sf[lc][j+1]%mod;
				if(s[rc]=='>')
					tmp=tmp*sp[rc][k]%mod;
				else
					tmp=tmp*sf[rc][k+1]%mod;
				add(f[x][i],tmp);
			}
	}
	for(ll i=n;i;i--)
		sf[x][i]=(sf[x][i+1]+f[x][i])%mod;
	for(ll i=1;i<=size[x];i++)
		sp[x][i]=(sp[x][i-1]+f[x][i])%mod;
}

int main()
{
	std::cin>>n;
	scanf("%s",s+2);
	pre();
	dfs(1);
	std::cout<<sf[1][1]<<std::endl;
	return 0;
}
