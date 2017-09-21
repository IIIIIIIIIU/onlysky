#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,k,bit[10];
ll dp[10][1025][82],pos;
bool can[12];
void dfs(int lev,int now,int deep,int num)
{
    if(deep>n)
    {
        if(num<=k) dp[lev][now][num]+=pos;
        return;
    }
    if(can[deep]) dfs(lev,now|bit[deep],deep+2,num+1);
    dfs(lev,now,deep+1,num);
}
int main()
{
    scanf("%d%d",&n,&k);
    dp[0][0][0]=1,bit[1]=1;
    for(int i=2;i<=n;i++) bit[i]=bit[i-1]<<1;
    int tmp;
    for(int i=0;i<n;i++)
        for(int v=0;v<=(bit[n]<<1)-1;v++)
            for(int e=0;e<=k;e++)
                if(dp[i][v][e])
                {
                    for(int t=1;t<=n;t++) can[t]=true;
                    tmp=0,pos=dp[i][v][e];
                    for(int t=1;t<=n;t++)
                        if((v&bit[t])==bit[t])
                            can[t-1]=can[t]=can[t+1]=false;
                    dfs(i+1,0,1,e);
                }
    ll ans=0;
    for(int i=0;i<=(bit[n]<<1)-1;i++) ans+=dp[n][i][k];
    cout<<ans;
    return 0;
}
