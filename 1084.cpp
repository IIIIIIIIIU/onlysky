#include <bits/stdc++.h>
using namespace std;
const int INF=-1e7;
int sum1[1005],sum2[1005],sum[1005],n,m,k,dp[105][105][12],f[105][12];
inline void in(int &now)
{
    char Cget;now=0;int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}
int main()
{
    in(n),in(m),in(k);
    if(m==1)
    {
        int tmp;
        for(int i=1;i<=n;i++) in(tmp),sum[i]=sum[i-1]+tmp;
        for(int i=1;i<=n;i++)
            for(int v=0;v<i;v++)
                for(int e=1;e<=k;e++)
                {
                    f[i][e]=max(f[i][e],f[v][e]);
                    f[i][e]=max(f[v][e-1]+sum[i]-sum[v],f[i][e]);
                }
        int ans=INF;
        for(int i=0;i<=k;i++) ans=max(ans,f[n][i]);
        cout<<ans;
    }
    else
    {
        int tmp;
        for(int i=1;i<=n;i++)
        {
            in(tmp),sum1[i]=sum1[i-1]+tmp;
            in(tmp),sum2[i]=sum2[i-1]+tmp;
        }
        for(int i=1;i<=n;i++)
            for(int v=1;v<=n;v++)
            {
                for(int e=1;e<=k;e++)
                {
                    for(int t=0;t<i;t++)
                    {
                        dp[i][v][e]=max(dp[i][v][e],dp[t][v][e]);
                        dp[i][v][e]=max(dp[i][v][e],dp[t][v][e-1]+sum1[i]-sum1[t]);
                    }
                    for(int t=0;t<v;t++)
                    {
                        dp[i][v][e]=max(dp[i][v][e],dp[i][t][e]);
                        dp[i][v][e]=max(dp[i][v][e],dp[i][t][e-1]+sum2[v]-sum2[t]);
                    }
                    if(i==v)
                    {
                        for(int t=0;t<min(i,v);t++)
                        {
                            dp[i][v][e]=max(dp[i][v][e],dp[t][t][e]);
                            dp[i][v][e]=max(dp[i][v][e],dp[t][t][e-1]+sum1[i]+sum2[i]-sum1[t]-sum2[t]);
                        }
                    }
                }
            }
        int ans=INF;
        for(int i=1;i<=k;i++) ans=max(ans,dp[n][n][k]);
        cout<<ans;
    }
    return 0;
}
