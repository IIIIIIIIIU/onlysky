#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int INF=0x3f3f3f3f;

int n,ki[125],ci[125];

ll f[126][250001],m,ans=INF;

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
	f[0][0]=1;
	read(n);
	std::cin>>m;
	for(int i=1;i<=n;i++)
		read(ki[i]);
	for(int i=1;i<=n;i++)
		read(ci[i]);
	for(int i=1,sum=0;i<=n;i++)
	{
		sum+=ki[i]*ci[i];
		for(int v=0,e;v<=sum;v++)
		{
			f[i][v]=f[i-1][v];
			for(e=1;e<=ki[i]&&v-e*ci[i]>=0;e++)
				if(f[i-1][v-e*ci[i]]*e>f[i][v])
					f[i][v]=f[i-1][v-e*ci[i]]*e;
			if(f[i][v]>=m)
			{
				f[i][v]=m;
				if(v<ans)
					ans=v;
			}
		}
	}
	std::cout<<ans<<std::endl;
	return 0;
}
