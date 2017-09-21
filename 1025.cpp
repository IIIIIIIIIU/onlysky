#include <bits/stdc++.h>
using namespace std;
#define maxn 1005
#define ll long long
int n,num;
ll dp[maxn][maxn],pi[maxn];
bool if_p[maxn];
void euler(int limit)
{
    for(int i=2;i<=limit;i++)
    {
        if(!if_p[i]) pi[++num]=i;
        for(int j=1;pi[j]*i<=limit&&j<=num;j++)
        {
            if_p[i*pi[j]]=true;
            if(i%pi[j]==0) break;
        }
    }
}
int main()
{
    scanf("%d",&n),euler(n);
    dp[0][0]=1;
    for(int i=1;i<=num;i++)
    {
        for(int v=0;v<=n;v++)
        {
            dp[i][v]=dp[i-1][v];
            for(ll pos=pi[i];pos<=v;pos*=pi[i])
            {
                dp[i][v]+=dp[i-1][v-pos];
            }
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++) ans+=dp[num][i];
    cout<<ans+1;
    return 0;
}
