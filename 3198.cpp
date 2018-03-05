#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef unsigned long long ll;

const int mod=1e9+7;
const int maxn=1e6+5;

int n,ai[maxn][6],head[maxn],cnt,E[maxn];
int k,C[10][10];

ll W[maxn],f[maxn],V[maxn];

inline int count(int s)
{
	int res=0;
	while(s>0)
	{
		res+=(s&1);
		s>>=1;
	}
	return res;
}

int main()
{
	C[0][0]=1;
	for(int i=1;i<=6;i++)
	{
		C[i][0]=1;
		for(int v=1;v<=i;v++)
			C[i][v]=C[i-1][v]+C[i-1][v-1];
	}
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		for(short v=0;v<6;v++)
			scanf("%d",&ai[i][v]);
	for(int s=0,cur;s<(1<<6);s++)
		if((cur=count(s))>=k)
		{
			for(int i=0;i<n;i++)
				head[i]=0;
			cnt=0;
			ll base,t;
			for(int i=1;i<=n;i++)
			{
				base=0;
				for(short v=0;v<6;v++)
					if((1<<v)&s)
						base=base*mod+ai[i][v];
				t=base%n;
				for(int v=head[t];v!=0;v=E[v])
					if(V[v]==base)
					{
						W[v]++;
						t=-1;
						break;
					}
				if(t>=0)
				{
					E[++cnt]=head[t];
					V[cnt]=base;
					W[cnt]=1;
					head[t]=cnt;
				}
			}
			for(int i=0;i<n;i++)
				for(int v=head[i];v!=0;v=E[v])
					f[cur]+=W[v]*(W[v]-1)>>1;
		}
	long long t=1,ans=0;
	for(int i=k;i<=6;i++,t=-t)
		ans+=(long long)f[i]*C[i][k]*t;
	std::cout<<ans;
	return 0;
}
