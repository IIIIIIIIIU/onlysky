#include <bits/stdc++.h>
using namespace std;
#define maxn 2505
const double eps=1e-5;
int si[maxn],pi[maxn],head[maxn],E[maxn<<1],V[maxn<<1],cnt,n,m;
int size[maxn];
double val[maxn],dp[maxn][maxn],list[maxn];
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void dfs(int now,int fa)
{
    size[now]=1,dp[now][1]=val[now];
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs(V[i],now),size[now]+=size[V[i]];
        int to=V[i];
        for(int e=min(size[now],m);e>=1;e--)
            for(int v=1;v<=min(min(e,m),size[to]);v++)
                if(e-v>=1) dp[now][e]=max(dp[now][e],dp[now][e-v]+dp[to][v]);
    }
}
bool check(double cur)
{
    memset(dp,-127/3,sizeof(dp)),size[0]=0;
    for(int i=1;i<=n;i++) val[i]=pi[i]-cur*si[i],size[i]=0;
    dp[0][0]=0;
    for(int i=head[0];i;i=E[i])
    {
        dfs(V[i],0),size[0]+=size[V[i]];
        int to=V[i];
        for(int e=min(size[0],m);e;e--)
            for(int v=1;v<=min(min(e,m),size[to]);v++)
                if(e-v>=0) dp[0][e]=max(dp[0][e],dp[0][e-v]+dp[to][v]);
    }
    return dp[0][m]>=0;
}
int main()
{
    in(m),in(n);int u,v;
    for(int i=1;i<=n;i++)
    {
        in(si[i]),in(pi[i]),in(v),u=i;
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    double l=0,r=1000000,mid,res=0;
    while(fabs(r-l)>=eps)
    {
        mid=(l+r)/2;
        if(check(mid)) res=mid,l=mid+eps;
        else r=mid-eps;
    }
    printf("%.3lf",res);
    return 0;
}
