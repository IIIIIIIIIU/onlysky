#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=3e2+5;
const int INF=-0x3f3f3f3f;
int n,m,c[maxn],a[maxn];
ll f[maxn][maxn][maxn],w[maxn];
char s[maxn];
void clear()
{
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			for(int k=0;k<=(1<<m)-1;k++)
				f[i][v][k]=INF;
}
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		a[i]=s[i]-'0';
	for(int i=0;i<(1<<m);i++)
	{
		char s1[2];
		scanf("%s",s1+1);
		c[i]=s1[1]-'0';
		scanf("%lld",&w[i]);
	}
	clear();
	for(int i=n;i>=1;i--)
		for(int v=i;v<=n;v++)
		{
			if(i==v)
			{
				f[i][v][a[i]]=0;
				continue;
			}
			int len=v-i;
			while(len>=m)
				len-=m-1;
			for(int k=v;k>i;k-=m-1)
				for(int t=(1<<len)-1;t>=0;t--)
				{
					ll now=f[i][k-1][t];
					if(now==INF)
						continue;
					if(f[k][v][0]!=INF)
						f[i][v][t<<1]=std::max(f[i][v][t<<1],f[k][v][0]+now);
					if(f[k][v][1]!=INF)
						f[i][v][t<<1|1]=std::max(f[i][v][t<<1|1],f[k][v][1]+now);
				}
			if(len==m-1)
			{
				ll g[2];
				g[0]=g[1]=INF;
				for(int t=(1<<m)-1;t>=0;t--)
					if(f[i][v][t]!=INF)
						g[c[t]]=std::max(g[c[t]],f[i][v][t]+w[t]);
				f[i][v][0]=g[0];
				f[i][v][1]=g[1];
			}
		}
	ll ans=0;
	for(int i=(1<<m)-1;i>=0;i--)
		ans=std::max(ans,f[1][n][i]);
	printf("%lld\n",ans);
	return 0;
}
