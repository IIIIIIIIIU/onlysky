#include <cstdio>
#include <cstring>
#include <iostream>

const int maxn=4505;

int n,p,f[2][maxn],s,ans;

int main()
{
	scanf("%d%d",&n,&p);
	f[1][1]=1;
	for(int i=2;i<=n;++i)
	{
		memset(f[i&1],0,sizeof(f[0]));
		s=0;
		for(int j=i-1;j;--j)
		{
			s=(s+f[i&1^1][i-j])%p;
			f[i&1][j]=s;
		}
	}
	for(int j=1;j<=n;++j) ans=(ans+f[n&1][j])%p;
	std::cout<<(ans<<1)%p;
	return 0;
}
