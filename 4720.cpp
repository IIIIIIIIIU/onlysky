#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define maxv 305
#define maxn 2005
#define maxm 2005
#define maxe 90005
 
using namespace std;
 
int n,m,v,e,tim[maxn],timo[maxn];
 
long long dis[maxv][maxv];
 
double gv[maxn][2],ci[maxn][2][2];
double dp[maxn][maxm][2],ans=1000000009.0;
 
char Cget;
 
inline void in(int &now)
{
    now=0,Cget=getchar();
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
 
int main()
{
    in(n),in(m),in(v),in(e);int u,v1,w;
    for(int i=1;i<=n;i++) in(tim[i]);
    for(int i=1;i<=n;i++) in(timo[i]);
    for(int i=1;i<=n;i++) scanf("%lf",&gv[i][1]),gv[i][0]=1.0-gv[i][1];
    for(int i=1;i<=v;i++)
    {
        for(int j=1;j<=v;j++)
        {
            dis[i][j]=1000000000;
        }
    }
    while(e--)
    {
        in(u),in(v1),in(w);
        dis[u][v1]=min((long long)w,dis[u][v1]);
        dis[v1][u]=min((long long)w,dis[v1][u]);
    }
    for(int i=1;i<=v;i++) dis[i][i]=0;
    for(int p=1;p<=v;p++)
    {
        for(int i=1;i<=v;i++)
        {
            for(int j=1;j<=v;j++)
            {
                dis[i][j]=min(dis[i][p]+dis[p][j],dis[i][j]);
            }
        }
    }
    for(int i=2;i<=n;i++)
    {
        ci[i][0][0]=dis[tim[i-1]][tim[i]];
        ci[i][0][1]=dis[tim[i-1]][timo[i]];
        ci[i][1][0]=dis[timo[i-1]][tim[i]];
        ci[i][1][1]=dis[timo[i-1]][timo[i]];
    }
    for(int i=1;i<=n;i++) for(int j=0;j<=m;j++) dp[i][j][0]=dp[i][j][1]=100000000.0;
    dp[1][0][0]=0,dp[1][1][1]=0;
    for(int i=2;i<=n;i++)
    {
        dp[i][0][1]=100000000.0;
        dp[i][0][0]=dp[i-1][0][0]+ci[i][0][0];
        for(int j=1;j<=m&&j<=i;j++)
        {
            dp[i][j][0]=min(dp[i-1][j][0]+ci[i][0][0],dp[i-1][j][1]+gv[i-1][0]*ci[i][0][0]+gv[i-1][1]*ci[i][1][0]);
            dp[i][j][1]=min(dp[i-1][j-1][0]+ci[i][0][1]*gv[i][1]+gv[i][0]*ci[i][0][0],dp[i-1][j-1][1]+ci[i][0][0]*gv[i-1][0]*gv[i][0]+ci[i][0][1]*gv[i-1][0]*gv[i][1]+ci[i][1][0]*gv[i-1][1]*gv[i][0]+ci[i][1][1]*gv[i-1][1]*gv[i][1]);
        }
    }
    for(int i=0;i<=m;i++) ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
    printf("%.2lf\n",ans);
    return 0;
}
