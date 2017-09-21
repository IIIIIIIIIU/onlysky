#include <bits/stdc++.h>
using namespace std;
const int mod=10007;
const int maxn=50005;
int n,m,sumlen,len[maxn],dp[2][maxn],ans2,sum[2][maxn],pre[maxn];
int ci[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
bool check(int k)
{
    int temp=0,pos=0;
    for(int i=1;i<=n;i++)
    {
        if(len[i]+temp>k) pos++,temp=len[i];
        else temp+=len[i];
    }
    return pos<=m&&temp<=k;
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++) in(len[i]),sumlen+=len[i];
    int l=0,r=sumlen,mid,ans=0;
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    int to=0;
    for(int i=0;i<=n;i++)
    {
        ci[i]=ci[i-1]+len[i];
        while(ci[i]-ci[to]>ans) to++;
        pre[i]=to-1;
    }
    int now=1,last=0;dp[0][0]=1,sum[0][0]=1;
    for(int i=1;i<=n;i++) sum[0][i]=sum[0][i-1];
    for(int i=1;i<=m+1;i++)
    {
        memset(dp[now],0,sizeof(dp[now]));
        for(int v=1;v<=n;v++)
            (dp[now][v]=(sum[last][v-1]-(pre[v]==-1?0:sum[last][pre[v]])+mod)%mod)%=mod;
        sum[now][0]=0;
        for(int v=1;v<=n;v++) sum[now][v]=sum[now][v-1]+dp[now][v];
        (ans2+=dp[now][n])%=mod,now^=1,last^=1;
    }
    cout<<ans<<' '<<ans2;
    return 0;
}
