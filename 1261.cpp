#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const real INF=1e9;
int n,tot,vi[35];
real k,c,dp[35][35][35],f[35];
real get(int x,real fix)
{
    return (k*(x+1)+c)*fix;
}
int main()
{
    scanf("%d%lf%lf",&n,&k,&c);
    for(int i=1;i<=n;i++) scanf("%d",&vi[i]),tot+=vi[i];
    for(int i=1;i<=n;i++) f[i]=(real)vi[i]/tot;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=n;v++)
            for(int e=0;e<n;e++)
                dp[i][v][e]=1e9;
    for(int i=1;i<=n;i++)
        for(int e=0;e<n;e++) dp[i][i][e]=get(e,f[i]);
    real tmp;
    for(int i=2;i<=n;i++)
        for(int l=1,r;l+i-1<=n;l++)
        {
            r=l+i-1;
            for(int e=0;e<n;e++)
                for(int v=l;v<=r;v++)
                {
                    tmp=dp[v][v][e];
                    if(v-1>=l) tmp+=dp[l][v-1][e+1];
                    if(v+1<=r) tmp+=dp[v+1][r][e+1];
                    dp[l][r][e]=min(dp[l][r][e],tmp);
                }
        }
    printf("%.3lf",dp[1][n][0]);
    return 0;
}
