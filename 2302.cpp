#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=305;

int n,m,p,cnt[maxn],sum[maxn];

ll C[maxn][maxn],dp[maxn][maxn];

inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

void pre()
{
	memset(C,0,sizeof(C));
	memset(dp,0,sizeof(dp));
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<=n;i++)
	{
		C[i][0]=1;
		for(int v=1;v<=i;v++)
			(C[i][v]=C[i-1][v-1]+C[i-1][v])%=p;
	}
}

int main()
{
	int T;
	read(T);
	for(int t=1;t<=T;t++)
	{
		read(n);
		read(m);
		read(p);
		pre();
		sum[0]=n-m;
		for(int i=1,tmp;i<=m;i++)
		{
			read(tmp);
			read(tmp);
			cnt[tmp]++;
		}
		bool DID=false;
		for(int i=1;i<=n;i++)
		{
			sum[i]=sum[i-1]+cnt[i];
			if(sum[i]<i)
			{
				puts("NO");
				DID=true;
				break;
			}
		}
		if(DID)
			continue;
		dp[0][0]=1;
		for(int i=1;i<=n;i++)
			for(int j=sum[i];j>=i;j--)
				for(int k=j-i+1;k>=cnt[i];k--)
					(dp[i][j]+=dp[i-1][j-k]*C[sum[i]-j+k-cnt[i]][k-cnt[i]])%=p;
		printf("YES %lld\n",dp[n][n]);
	}
	return 0;
}
