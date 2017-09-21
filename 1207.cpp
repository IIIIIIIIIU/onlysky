#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int dp[10005],t[10005],x[10005],y[10005],n,m,ans;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=m;i++)
    {
        in(t[i]),in(x[i]),in(y[i]);
        for(int v=1;v<i;v++)
            if(t[i]-t[v]>=abs(x[i]-x[v])+abs(y[i]-y[v])) dp[i]=max(dp[i],dp[v]+1);
        ans=max(ans,dp[i]);
    }
    cout<<ans+1;
    return 0;
}
