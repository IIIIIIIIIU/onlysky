#include<cstdio>
#include<iostream>
 
#define mod 999983
 
using namespace std;
 
int n,m;
long long int dp[101][101][101],ans=0;
 
int main()
{
    scanf("%d%d",&n,&m);
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int k=0;k<=m;k++)
        {
            for(int j=0;j<=m-k;j++)
            {
                dp[i][k][j]=dp[i-1][k][j];
                if(k) dp[i][k][j]+=(m-k-j+1)*dp[i-1][k-1][j]%mod;
                if(j&&k<m) dp[i][k][j]+=(k+1)*dp[i-1][k+1][j-1]%mod;
                if(k>1) dp[i][k][j]+=(m-j-k+2)*(m-j-k+1)/2*dp[i-1][k-2][j]%mod;
                if(j>1&&k<m-1) dp[i][k][j]+=(k+2)*(k+1)/2*dp[i-1][k+2][j-2]%mod;
                if(k&&j) dp[i][k][j]+=(m-j-k+1)*(k)*dp[i-1][k][j-1]%mod;
                dp[i][k][j]%=mod;
            }
        }
    }
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=m-i;j++)
        {
            ans+=dp[n][i][j];
            ans%=mod;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
