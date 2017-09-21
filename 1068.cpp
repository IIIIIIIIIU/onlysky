#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int hpos=29;
int dp[55][55][4],n;
ull Hash[55],num[55];
char str[55];
ull get(int l,int r)
{
    return Hash[r]-Hash[l-1]*num[r-l+1];
}
int main()
{
    scanf("%s",str+1),n=strlen(str+1);
    num[0]=1;
    for(int i=1;i<=n;i++)
    {
        num[i]=num[i-1]*hpos;
        Hash[i]=Hash[i-1]*hpos+str[i]-'a'+1;
    }
    memset(dp,127/3,sizeof(dp));
    for(int i=1;i<=n;i++) dp[i][i][0]=1,dp[i][i][1]=2;
    dp[1][1][1]=1;
    int l,r;
    for(int i=2;i<=n;i++)
        for(int v=1;v+i-1<=n;v++)
        {
            l=v,r=v+i-1;
            if((r-l+1)%2==0)
                if(get(l,l+r>>1)==get((((l+r)>>1)+1),r))
                    dp[l][r][1]=dp[l][l+r>>1][1]+1;
            for(int e=l;e<r;e++)
            {
                dp[l][r][0]=min(dp[l][r][0],dp[l][r][0]+dp[e+1][r][0]);
                dp[l][r][1]=min(dp[l][r][1],dp[l][e][1]+dp[e+1][r][0]);
                dp[l][r][2]=min(dp[l][r][2],dp[l][e][0]+dp[e+1][r][1]);
                dp[l][r][2]=min(dp[l][r][2],dp[l][e][0]+dp[e+1][r][2]);
                dp[l][r][2]=min(dp[l][r][2],dp[l][e][0]+dp[e+1][r][3]);
                dp[l][r][2]=min(dp[l][r][2],dp[l][e][2]+dp[e+1][r][2]);
                dp[l][r][2]=min(dp[l][r][2],dp[l][e][2]+dp[e+1][r][0]);
                dp[l][r][3]=min(dp[l][r][3],dp[l][e][1]+dp[e+1][r][1]);
                dp[l][r][3]=min(dp[l][r][3],dp[l][e][1]+dp[e+1][r][2]);
                dp[l][r][3]=min(dp[l][r][3],dp[l][e][1]+dp[e+1][r][3]);
                dp[l][r][3]=min(dp[l][r][3],dp[l][e][3]+dp[e+1][r][0]);
                dp[l][r][3]=min(dp[l][r][3],dp[l][e][3]+dp[e+1][r][1]);
                dp[l][r][3]=min(dp[l][r][3],dp[l][e][3]+dp[e+1][r][2]);
                dp[l][r][3]=min(dp[l][r][3],dp[l][e][3]+dp[e+1][r][3]);
            }
        }
    cout<<min(min(dp[1][n][0],dp[1][n][1]),min(dp[1][n][2],dp[1][n][3]));
    return 0;
}
