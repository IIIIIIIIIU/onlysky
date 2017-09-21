#include <bits/stdc++.h>
using namespace std;
const int maxn=105;
int n,dp[maxn][maxn];
char ch[maxn];
int getit(int num)
{
    int res=2;
    while(num) res++,num/=10;
    return res;
}
bool can(int l,int r,int e)
{
    for(int i=l+e;i<=r;i++)
        if(ch[i]!=ch[i-e]) return false;
    return true;
}
int main()
{
    scanf("%s",ch+1),n=strlen(ch+1);
    for(int i=1;i<=n;i++)
        for(int l=1,r;l+i-1<=n;l++)
        {
            r=l+i-1,dp[l][r]=i;
            for(int e=l;e<r;e++)
                dp[l][r]=min(dp[l][r],dp[l][e]+dp[e+1][r]);
            for(int e=1;e<=(i>>1);e++)
                if(i%e==0)
                    if(can(l,r,e)) dp[l][r]=min(dp[l][r],dp[l][l+e-1]+getit(i/e));
        }
    cout<<dp[1][n];
    return 0;
}
