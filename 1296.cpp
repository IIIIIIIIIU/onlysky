#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n,m,k,dp[55][55],f[2505],ci[55][55];
char ch[100];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch+1);
        memset(dp,0,sizeof(dp));
        memset(ci,0,sizeof(ci));
        for(int l=1;l<=m;l++)
            for(int r=l;r<=m;r++)
            {
                for(int e=l;e<=r;e++) ci[l][r]+=ch[e]-'0';
                ci[l][r]=max(ci[l][r],r-l+1-ci[l][r]);
            }
        for(int v=1;v<=m;v++)
            for(int e=0;e<v;e++)
                for(int t=1;t<=m;t++)
                    dp[v][t]=max(dp[e][t-1]+ci[e+1][v],dp[v][t]);
        for(int v=k;v>=1;v--)
            for(int e=1;e<=min(k,m)&&v-e>=0;e++)
                f[v]=max(f[v],f[v-e]+dp[m][e]);
    }
    cout<<f[k];
    return 0;
}
