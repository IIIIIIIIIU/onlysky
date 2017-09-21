#include <bits/stdc++.h>
using namespace std;
#define maxn 600005
#define maxtot maxn*19
int n,m,deep[maxn],top[maxn],size[maxn];
int f[maxn],cnt,head[maxn],E[maxn<<1],V[maxn<<1];
int watch[maxn],st[maxn],en[maxn],tot,Count,ans[maxn];
int lc[maxtot],rc[maxtot],dis[maxtot],lar[maxn];
int lca[maxn],id[maxn],root[maxn*3],li[maxn],ri[maxn];
inline void in(int &now)
{
    int if_z=1;now=0;
    char Cget=getchar();
    while(Cget>'9'||Cget<'0')
    {
        if(Cget=='-') if_z=-1;
        Cget=getchar();
    }
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
}
void dfs1(int now,int fa)
{
    size[now]=1,f[now]=fa;
    deep[now]=deep[fa]+1;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==f[now]) continue;
        dfs1(V[i],now),size[now]+=size[V[i]];
        if(size[V[i]]>size[lar[now]]) lar[now]=V[i];
    }
}
void dfs2(int now,int chain)
{
    top[now]=chain,id[now]=++cnt,li[now]=cnt;
    if(lar[now]) dfs2(lar[now],chain);
    else
    {
        ri[now]=cnt;
        return;
    }
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==f[now]||V[i]==lar[now]) continue;
        dfs2(V[i],V[i]);
    }
    ri[now]=cnt;
}
inline int find(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]]) swap(x,y);
        x=f[top[x]];
    }
    if(deep[x]>deep[y]) swap(x,y);
    return x;
}
void updata(int &now,int l,int r,int to,int x)
{
    if(!to) return;
    if(!now) now=++tot;
    dis[now]+=x;
    if(l==r) return;
    int mid=l+r>>1;
    if(to<=mid) updata(lc[now],l,mid,to,x);
    else updata(rc[now],mid+1,r,to,x);
}
void query(int now,int l,int r,int tl,int tr)
{
    if(!now) return;
    if(l>=tl&&r<=tr)
    {
        Count+=dis[now];
        return;
    }
    int mid=l+r>>1;
    if(tl<=mid) query(lc[now],l,mid,tl,tr);
    if(tr>mid) query(rc[now],mid+1,r,tl,tr);
}
int main()
{
    in(n),in(m);int u,v,pos;
    for(int i=1;i<n;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    cnt=0,dfs1(1,0),cnt=0,dfs2(1,1);
    for(int i=1;i<=n;i++) in(watch[i]);
    for(int i=1;i<=m;i++)
    {
        in(st[i]),in(en[i]);
        lca[i]=find(st[i],en[i]);
        updata(root[deep[st[i]]],1,n,id[st[i]],1);
        updata(root[deep[st[i]]],1,n,id[f[lca[i]]],-1);
    }
    for(int i=1;i<=n;i++)
    {
        Count=0;
        query(root[deep[i]+watch[i]],1,n,li[i],ri[i]);
        ans[i]=Count;
    }
    memset(rc,0,sizeof(rc));
    memset(lc,0,sizeof(lc));
    memset(dis,0,sizeof(dis));
    memset(root,0,sizeof(root));
    tot=0;
    for(int i=1;i<=m;i++)
    {
        pos=deep[st[i]]-deep[lca[i]]*2+n*2;
        updata(root[pos],1,n,id[en[i]],1);
        updata(root[pos],1,n,id[lca[i]],-1);
    }
    for(int i=1;i<=n;i++)
    {
        Count=0;
        query(root[watch[i]-deep[i]+n*2],1,n,li[i],ri[i]);
        ans[i]+=Count;
    }
    for(int i=1;i<n;i++) printf("%d ",ans[i]);
    printf("%d",ans[n]);
    return 0;
}
