#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const real INF=1e12,eps=1e-10;
const int maxn=3005,maxm=100005;
int n,m,head[maxn],E[maxm],V[maxm],tag,cnt;
real W[maxm],lit,dis[maxn];
bool vis[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void dfs(int now)
{
    vis[now]=true;
    for(int i=head[now];i;i=E[i])
        if(dis[V[i]]>dis[now]+W[i])
        {
            dis[V[i]]=dis[now]+W[i];
            if(vis[V[i]])
            {
                tag=1;
                return;
            }
            dfs(V[i]);
            if(tag) return;
        }
    vis[now]=false;
}
bool check()
{
    tag=0;
    for(int i=1;i<=cnt;i++) W[i]-=lit;
    for(int v=1;v<=n;v++) vis[v]=0,dis[v]=0;
    for(int i=1;i<=n;i++)
    {
        dfs(i);
        if(tag) break;
    }
    for(int i=1;i<=cnt;i++) W[i]+=lit;
    if(tag) return true;
    return false;
}
int main()
{
    in(n),in(m);int u,v;real w,l=INF,r=-INF;
    while(m--)
    {
        in(u),in(v),scanf("%lf",&w);
        E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
        l=min(l,w),r=max(r,w);
    }
    real ans;
    while(l+eps<r)
    {
        lit=(l+r)/2.0;
        if(check()) r=lit-eps,ans=lit;
        else l=lit+eps;
    }
    printf("%.8lf",ans);
    return 0;
}
