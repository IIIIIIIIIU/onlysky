#include <bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
int dp[100][100],n;
char ch[100];
int main()
{
    scanf("%s",ch+1),n=strlen(ch+1);
    for(int i=1;i<=n;i++) dp[i][i]=1;
    for(int i=2;i<=n;i++)
        for(int l=1,r;l+i-1<=n;l++)
        {
            r=l+i-1,dp[l][r]=INF;
            if(ch[l]==ch[r])
            {
                if(i==2) dp[l][r]=1;
                else
                {
                    dp[l][r]=min(dp[l+1][r],dp[l][r-1]);
                    dp[l][r]=min(dp[l][r],dp[l+1][r-1]+1);
                }
            }
            else for(int e=l;e<r;e++)
                    dp[l][r]=min(dp[l][r],dp[l][e]+dp[e+1][r]);
        }
    cout<<dp[1][n];
    return 0;
}
