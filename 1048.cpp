#include <cmath>
#include <cstdio>
using namespace std;
typedef double real;
const real INF=3e9;
int a,b,n;
real dp[11][11][11][11][11],sum[11][11],ave[11][11];
bool vis[11][11][11][11][11];
real min(real a,real b)
{
    if(a<b) return a;
    else return b;
}
real dfs(int x,int y,int x_,int y_,int now)
{
    if(vis[x][y][x_][y_][now]) return dp[x][y][x_][y_][now];
    vis[x][y][x_][y_][now]=true,dp[x][y][x_][y_][now]=INF;
    real tmp1,tmp2;
    for(int i=1;i<now;i++)
    {
        for(int v=x;v<x_;v++)
            dp[x][y][x_][y_][now]=min(dp[x][y][x_][y_][now],dfs(x,y,v,y_,i)+dfs(v+1,y,x_,y_,now-i));
        for(int v=y;v<y_;v++)
            dp[x][y][x_][y_][now]=min(dp[x][y][x_][y_][now],dfs(x,y,x_,v,i)+dfs(x,v+1,x_,y_,now-i));
    }
    return dp[x][y][x_][y_][now];
}
int main()
{
    scanf("%d%d%d",&a,&b,&n);
    for(int i=1;i<=a;i++)
        for(int v=1;v<=b;v++)
            scanf("%lf",&sum[i][v]),sum[i][v]+=sum[i-1][v]+sum[i][v-1]-sum[i-1][v-1];
    real pos;
    for(int i=1;i<=a;i++)
        for(int v=1;v<=b;v++)
            for(int e=i;e<=a;e++)
                for(int k=v;k<=b;k++)
                {
                    vis[i][v][e][k][1]=true;
                    pos=sum[e][k]-sum[i-1][k]-sum[e][v-1]+sum[i-1][v-1];
                    dp[i][v][e][k][1]=pos*pos;
                    //printf("%d %d %d %d:%.1lf\n",i,v,e,k,dp[i][v][e][k][1]);
                }
    dfs(1,1,a,b,n),pos=sum[a][b]/n;
    real ans=2*sum[a][b]*pos-pos*pos*n;
    printf("%.2lf",sqrt((dp[1][1][a][b][n]-ans)/n));
    return 0;
}
