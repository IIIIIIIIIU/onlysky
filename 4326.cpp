#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 300005
#define INF 0x7fffffff
 
int n,deep[maxn],dis[maxn],dis_[maxn],f[maxn],top[maxn];
int head[maxn],E[maxn<<1],V[maxn<<1],W[maxn<<1],cnt,m;
int path1[maxn],path2[maxn],ti[maxn],lar[maxn],size[maxn];
int lca[maxn],lit_r,set[maxn];
 
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
 
void dfs1(int now,int fa)
{
    deep[now]=deep[fa]+1,f[now]=fa,size[now]=1;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dis[V[i]]=W[i]+dis[now],dfs1(V[i],now),size[now]+=size[V[i]];
        if(size[lar[now]]<size[V[i]]) lar[now]=V[i];
    }
}
 
void dfs2(int now,int chain)
{
    top[now]=chain,dis_[now]=dis[now]-dis[f[now]];
    if(lar[now]) dfs2(lar[now],chain);else return;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==f[now]||V[i]==lar[now]) continue;
        dfs2(V[i],V[i]);
    }
}
 
void tree_lca(int op)
{
    int x=path1[op],y=path2[op],&ci=ti[op];
    ci=dis[x]+dis[y];
    for(;top[x]!=top[y];)
    {
        if(deep[top[x]]<deep[top[y]]) swap(x,y);
        x=f[top[x]];
    }
    if(deep[x]>deep[y]) swap(x,y);
    lca[op]=x,lit_r=max(ci,lit_r);
    ci-=dis[lca[op]]*2;
}
 
void dfs3(int now)
{
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==f[now]) continue;
        dfs3(V[i]),dis[now]+=dis[V[i]];
    }
    if(dis[now]==lit_r) set[++cnt]=now;
}
 
bool check(int x)
{
    int num=0,pos=0;
    memset(dis,0,4*n+4);
    for(int i=1;i<=m;i++)
    {
        if(ti[i]>x)
        {
            num++;if(ti[i]>ti[pos]) pos=i;
            dis[path1[i]]++,dis[path2[i]]++,dis[lca[i]]-=2;
        }
    }
    if(!num) return true;
    cnt=0,lit_r=num,dfs3(1);pos=ti[pos];
    for(int i=1;i<=cnt;i++) if(pos-dis_[set[i]]<=x) return true;
    return false;
}
 
int main()
{
    in(n),in(m);int u,v,w;
    for(int i=1;i<n;i++)
    {
        in(u),in(v),in(w);
        E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
    }
    cnt=0,dfs1(1,0),dfs2(1,1);
    for(int i=1;i<=m;i++) in(path1[i]),in(path2[i]),tree_lca(i);
    int l=0,r=lit_r,ans=INF;lit_r=0;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
