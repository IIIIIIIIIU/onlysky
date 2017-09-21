#include <bits/stdc++.h>
using namespace std;
const int maxn=250005;
const int maxtree=maxn<<2;
int n,m,deep[maxn],f[maxn],top[maxn],cnt,head[maxn];
int lar[maxn],size[maxn],L[maxtree],R[maxtree],id[maxn];
int E[maxn<<1],V[maxn<<1],mid[maxtree],tag[maxtree],val[maxtree];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void dfs1(int now,int fa)
{
    deep[now]=deep[fa]+1,f[now]=fa,size[now]=1;
    for(int i=head[now];i;i=E[i])
        if(V[i]!=fa)
        {
            dfs1(V[i],now),size[now]+=size[V[i]];
            if(size[lar[now]]<=size[V[i]]) lar[now]=V[i];
        }
}
void dfs2(int now,int chain)
{
    top[now]=chain,id[now]=++cnt;
    if(lar[now]) dfs2(lar[now],chain);
    for(int i=head[now];i;i=E[i])
        if(V[i]!=lar[now]&&V[i]!=f[now]) dfs2(V[i],V[i]);
}
void build(int now,int l,int r)
{
    L[now]=l,R[now]=r,val[now]=r-l+1;
    if(l==r) return;mid[now]=l+r>>1;
    build(now<<1,l,mid[now]),build(now<<1|1,mid[now]+1,r);
    val[now]=val[now<<1]+val[now<<1|1];
}
void pushdown(int now)
{
    tag[now<<1]=true,tag[now<<1|1]=true;
    val[now<<1]=0,val[now<<1|1]=0,tag[now]=false;
}
void change(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r)
    {
        val[now]=0,tag[now]=true;
        return ;
    }
    if(tag[now]) pushdown(now);
    if(l<=mid[now]) change(now<<1,l,r);
    if(r>mid[now]) change(now<<1|1,l,r);
    val[now]=val[now<<1]+val[now<<1|1];
}
int query(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r) return val[now];
    if(tag[now]) pushdown(now);int res=0;
    if(l<=mid[now]) res+=query(now<<1,l,r);
    if(r>mid[now]) res+=query(now<<1|1,l,r);
    return res;
}
void solve_c(int x,int y)
{
    while(top[x]!=top[y])
        if(deep[top[x]]>deep[top[y]]) change(1,id[top[x]],id[x]),x=f[top[x]];
        else change(1,id[top[y]],id[y]),y=f[top[y]];
    if(deep[x]>deep[y]) swap(x,y);
    if(x!=y) change(1,id[x]+1,id[y]);
}
int query(int x)
{
    int res=0;
    while(top[x]!=1) res+=query(1,id[top[x]],id[x]),x=f[top[x]];
    if(x!=1) res+=query(1,id[1]+1,id[x]);
    return res;
}
int main()
{
    in(n);int u,v;
    for(int i=1;i<n;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    dfs1(1,0),cnt=0,dfs2(1,1),build(1,1,n),in(m);
    char op[4];int x,y;
    while(m)
    {
        scanf("%s",op);
        if(op[0]=='W') in(x),printf("%d\n",query(x)),m--;
        else in(x),in(y),solve_c(x,y);
    }
    return 0;
}
