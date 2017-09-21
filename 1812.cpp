#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1e12;
const int maxn=105;
int n,k,ch[maxn][2],ci[maxn],di[maxn];
ll dp[maxn][maxn][maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget<='9'&&Cget>='0')now=now*10+Cget-'0',Cget=getchar();
}
void dfs(int now,int last)
{
    if(now==-1) return;
    di[now]+=last;
    dfs(ch[now][0],di[now]);
    dfs(ch[now][1],last);
}
ll get(int now,int a,int b)
{
    if(dp[now][a][b]!=-1) return dp[now][a][b];
    dp[now][a][b]=INF;
    for(int t=0;t<=a;t++)
    {
        ll tmp=0;
        if(ch[now][0]!=-1) tmp+=get(ch[now][0],t,b);
        if(ch[now][1]!=-1) tmp+=get(ch[now][1],a-t,b);
        dp[now][a][b]=min(dp[now][a][b],tmp+(di[now]-di[b])*ci[now]);
        if(t<a)
        {
            tmp=0;
            if(ch[now][0]!=-1) tmp+=get(ch[now][0],t,now);
            if(ch[now][1]!=-1) tmp+=get(ch[now][1],a-t-1,b);
            dp[now][a][b]=min(dp[now][a][b],tmp);
        }
    }
    return dp[now][a][b];
}
int main()
{
    in(n),in(k);int pre;
    for(int i=1;i<=n;i++)
    {
        in(ci[i]),in(pre),in(di[i]);
        if(!ch[pre][0]) ch[pre][0]=i;
        else
        {
            int tmp=ch[pre][0];
            while(ch[tmp][1]) tmp=ch[tmp][1];
            ch[tmp][1]=i;
        }
    }
    for(int i=0;i<=n;i++)
    {
        if(!ch[i][0]) ch[i][0]=-1;
        if(!ch[i][1]) ch[i][1]=-1;
    }
    dfs(0,0);
    memset(dp,-1,sizeof(dp));
    cout<<get(0,k,0);
    return 0;
}
