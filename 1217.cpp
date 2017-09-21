#include <bits/stdc++.h>
using namespace std;
int n,head[10001],E[20001],V[20001],cnt,dp[1001][5];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void dfs(int now)
{
    dp[now][0]=1;
    for(int i=head[now];i;i=E[i])
    {
        dfs(V[i]);
        dp[now][0]+=dp[V[i]][4];
        dp[now][3]+=dp[V[i]][2];
        dp[now][4]+=dp[V[i]][3];
    }
    int x2=2e9,x1=2e9;
    for(int i=head[now];i;i=E[i])
    {
        x2=min(x2,dp[V[i]][1]-dp[V[i]][2]);
        x1=min(x1,dp[V[i]][0]-dp[V[i]][3]);
    }
    dp[now][2]=x2+dp[now][3];
    dp[now][1]=x1+dp[now][4];
    dp[now][2]=min(dp[now][2],min(dp[now][1],dp[now][0]));
    dp[now][3]=min(dp[now][3],dp[now][2]);
    dp[now][4]=min(dp[now][4],dp[now][3]);
}
int main()
{
    in(n);int u,v;
    for(int i=2;i<=n;i++)
    {
        in(u),v=i;
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
    }
    dfs(1),printf("%d\n",min(dp[1][0],min(dp[1][1],dp[1][2])));
    return 0;
}
