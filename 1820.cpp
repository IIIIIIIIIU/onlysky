#include <bits/stdc++.h>
using namespace std;
const int maxn=205;
int dis[maxn][maxn],seq[maxn*6],cnt,m,dp[2][maxn][maxn],n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=n;v++)
            scanf("%d",&dis[i][v]);
    seq[++cnt]=1;
    int tmp=0;
    while(scanf("%d",&tmp)!=EOF) seq[++cnt]=tmp;
    memset(dp[1],127/3,sizeof(dp[1]));
    dp[1][2][3]=0;
    for(int i=2;i<=cnt;i++)
    {
        int now=i%2,last=now^1,pos=seq[i-1];
        memset(dp[now],127/3,sizeof(dp[now]));
        for(int p1=1;p1<=n;p1++)
            for(int p2=1;p2<=n;p2++)
            {
                dp[now][p1][p2]=min(dp[now][p1][p2],dp[last][p1][p2]+dis[pos][seq[i]]);
                dp[now][pos][p2]=min(dp[now][pos][p2],dp[last][p1][p2]+dis[p1][seq[i]]);
                dp[now][p1][pos]=min(dp[now][p1][pos],dp[last][p1][p2]+dis[p2][seq[i]]);
            }
    }
    int now=cnt%2,ans=0x3f3f3f3f;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=n;v++)
            ans=min(ans,dp[now][i][v]);
    cout<<ans;
    return 0;
}
