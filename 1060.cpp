#include <bits/stdc++.h>
using namespace std;
const int maxn=500005;
const int maxm=2000005;
int n,head[maxn],E[maxm],V[maxm],W[maxm],cnt,s;
int f[maxn],g[maxn];
long long ans=0;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void dfs(int now,int fa)
{
    int tmp=0;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs(V[i],now),f[now]=max(f[V[i]]+W[i],f[now]);
    }
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        ans+=f[now]-f[V[i]]-W[i];
    }
}
int main()
{
    in(n),in(s);int u,v,w;
    for(int i=1;i<n;i++)
    {
        in(u),in(v),in(w);
        E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
    }
    dfs(s,0),cout<<ans;
    return 0;
}
