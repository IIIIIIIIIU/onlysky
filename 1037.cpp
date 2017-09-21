#include <bits/stdc++.h>
using namespace std;
const int mod=12345678;
#define get(x) (x)%=mod
int dp[152][153][22][22],n,m,k,ans;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    dp[0][0][0][0]=1;
    for(int i=0;i<=n;i++)
        for(int v=0;v<=m;v++)
            for(int a=0;a<=k;a++)
                for(int b=0;b<=k;b++)
                {
                    if(!dp[i][v][a][b]) continue;
                    get(dp[i+1][v][a+1][max(b-1,0)]+=dp[i][v][a][b]);
                    get(dp[i][v+1][max(a-1,0)][b+1]+=dp[i][v][a][b]);
                }
    for(int i=0;i<=k;i++)
        for(int v=0;v<=k;v++) get(ans+=dp[n][m][i][v]);
    cout<<ans;
    return 0;
}
