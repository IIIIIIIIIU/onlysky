#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF=0x3f3f3f3f;
int dp[3][30005],n,m;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),m=n*5;
    memset(dp,127/3,sizeof(dp));
    dp[0][0]=0;int ta,tb,tc;
    for(int i=1;i<=n;i++)
    {
        int now=i%2,last=(i+1)%2;
        for(int i=0;i<=m;i++) dp[now][i]=INF;
        in(ta),in(tb),in(tc);
        if(ta)
            for(int v=0;v<=m;v++) if(v>=ta) dp[now][v]=min(dp[now][v],dp[last][v-ta]);
        if(tb)
            for(int v=0;v<=m;v++) dp[now][v]=min(dp[now][v],dp[last][v]+tb);
        if(tc)
            for(int v=0;v<=m;v++) if(v>=tc) dp[now][v]=min(dp[now][v],dp[last][v-tc]+tc);
    }
    int ans=INF;
    for(int i=1,c=n%2;i<=m;i++) ans=min(ans,max(i,dp[c][i]));
    cout<<ans;
    return 0;
}
