#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxs 100005
#define ll long long
int ci[5],n,di[5],s;
ll dp[maxs],ans;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void dfs(int now,ll dis,int deep)
{
    dis-=(di[now]+1)*ci[now];
    if(dis>=0)
    {
        if(deep%2) ans-=dp[dis];
        else ans+=dp[dis];
        for(int v=now+1;v<=4;v++) dfs(v,dis,deep+1);
    }
}
int main()
{
    dp[0]=1;
    for(int i=1;i<=4;i++) in(ci[i]);
    in(n);
    for(int v=1;v<=4;v++)
        for(int i=1;i<maxs;i++)
            if(ci[v]<=i) dp[i]+=dp[i-ci[v]];
    while(n--)
    {
        for(int i=1;i<=4;i++) in(di[i]);
        in(s),ans=dp[s],dfs(1,s,1),dfs(2,s,1),dfs(3,s,1),dfs(4,s,1);
        printf("%lld\n",ans);
    }
    return 0;
}
