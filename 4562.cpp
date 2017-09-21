#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxm 200005
int head[maxn],E[maxm],V[maxm],cnt;
int n,m,dis[maxn],dout[maxn],din[maxn],ans;
bool vis[maxn];
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
int dfs(int now)
{
    if(vis[now]) return dis[now];
    vis[now]=true;
    for(int i=head[now];i;i=E[i]) dis[now]+=dfs(V[i]);
    return dis[now];
}
int main()
{
    in(n),in(m);int u,v;
    while(m--)
    {
        in(u),in(v),dout[u]++,din[v]++;
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
    }
    for(int i=1;i<=n;i++)
        if(!dout[i]&&din[i]) vis[i]=true,dis[i]=1;
    for(int i=1;i<=n;i++)
        if(dout[i]&&!din[i]) ans+=dfs(i);
    cout<<ans;
    return 0;
}
