#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod=9999973;
ll n,m,dp[105][105][105];
int main()
{
    cin>>n>>m;
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++)
        for(int k1=0;k1<=m;k1++)
            for(int k2=0;k2<=m-k1;k2++)
            {
                if(k1) (dp[i][k1][k2]+=dp[i-1][k1-1][k2]*(m-k2-k1+1))%=mod;//one k1
            //  if(k2) (dp[i][k1][k2]+=dp[i-1][k1][k2-1]*(m-k1-k2+1))%=mod;//two k2
                if(k2) (dp[i][k1][k2]+=dp[i-1][k1+1][k2-1]*(k1+1))%=mod;//one k2
                if(k2>1&&k1+k2<=m) (dp[i][k1][k2]+=dp[i-1][k1+2][k2-2]*(k1+2)*(k1+1)/2)%=mod;//two k2*2
                if(k2&&k1) (dp[i][k1][k2]+=dp[i-1][k1][k2-1]*(m-k2-k1+1)*k1)%=mod;//two k1 k2
                if(k1>1) (dp[i][k1][k2]+=dp[i-1][k1-2][k2]*(m-k2-k1+2)*(m-k2-k1+1)/2)%=mod;//two k1 k1
                (dp[i][k1][k2]+=dp[i-1][k1][k2])%=mod;
            }
    ll ans=0;
    for(int i=0;i<=m;i++)
        for(int v=0;v<=m-i;v++) (ans+=dp[n][i][v])%=mod;
    cout<<ans;
    return 0;
}
