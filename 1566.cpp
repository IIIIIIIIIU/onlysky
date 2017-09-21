#include <bits/stdc++.h>
using namespace std;
const int mod=1024523;
int n,m,tot,dp[2][505][505];
char A[1001],B[1001];
inline void G(int &x)
{
    if(x>=mod) x-=mod;
}
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",A+1);
    scanf("%s",B+1);
    tot=n+m;
    dp[0][0][0]=1;
    for(int i=1;i<=tot;i++)
    {
        int now=i%2,last=(i+1)%2;
        for(int l=max(0,i-m);l<=min(i,n);l++)
            for(int r=max(0,i-m);r<=min(i,n);r++)
            {
                dp[now][l][r]=0;
                if(l&&r&&A[l]==A[r]) G(dp[now][l][r]+=dp[last][l-1][r-1]);
                if(l&&(i-r)&&A[l]==B[i-r]) G(dp[now][l][r]+=dp[last][l-1][r]);
                if((i-l)&&r&&B[i-l]==A[r]) G(dp[now][l][r]+=dp[last][l][r-1]);
                if((i-l)&&(i-r)&&B[i-l]==B[i-r]) G(dp[now][l][r]+=dp[last][l][r]);
            }
    }
    cout<<dp[tot%2][n][n];
    return 0;
}
