#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define ll long long
 
ll n,m,k,e,map[25][25],cost[105][105],que[105*105*2],dp[105];
 
bool if_[105][25];
 
inline void in(ll &now)
{
    register char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
 
ll spfa(ll u,ll v)
{
    ll dis[25],can[25],init[25],h=0,tail=1;
    for(ll i=1;i<=m;i++) can[i]=true,dis[i]=0x7ffffff,init[i]=false;
    for(ll i=u;i<=v;i++)
    {
        for(ll j=1;j<=m;j++) if(if_[i][j]) can[j]=false;
    }
    que[0]=1,dis[1]=0,init[1]=true;
    while(h<tail)
    {
        ll now=que[h++];init[now]=false;
        for(ll i=1;i<=m;i++)
        {
            if(can[i]&&dis[i]>dis[now]+map[now][i])
            {
                dis[i]=dis[now]+map[now][i];
                if(!init[i])
                {
                    init[i]=true;
                    que[tail++]=i;
                }
            }
        }
    }
    return dis[m];
}
 
int main()
{
    in(n),in(m),in(k),in(e);ll u,v,w;
    memset(dp,127/3,sizeof(dp));
    memset(map,127/3,sizeof(map));
    while(e--)
    {
        in(u),in(v),in(w);
        map[u][v]=map[v][u]=min(w,map[v][u]);
    }
    in(e);
    while(e--)
    {
        in(w),in(u),in(v);
        for(ll i=u;i<=v;i++) if_[i][w]=true;
    }
    for(ll i=1;i<=n;i++)
    {
        for(ll j=i;j<=n;j++)
        {
            cost[i][j]=spfa(i,j);
        }
    }
    dp[0]=0;
    for(ll i=1;i<=n;i++)
    {
        for(ll j=0;j<i;j++)
        {
            dp[i]=min(dp[i],dp[j]+cost[j+1][i]*(i-j)+k);
        }
    }
    cout<<dp[n]-k;
}
