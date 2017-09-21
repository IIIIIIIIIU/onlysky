#include <bits/stdc++.h>
using namespace std;
#define maxn 20005
#define ll long long
struct DataType {
    ll d[61],p[61];
    ll cnt;
    DataType()
    {
        memset(d,0,sizeof(d));
        memset(p,0,sizeof(p));
        cnt=0;
    }
    bool insert(long long val)
    {
        for(ll i=60;i>=0;i--)
        {
            if(val&(1LL<<i))
            {
                if(!d[i])
                {
                    d[i]=val;
                    break;
                }
                val^=d[i];
            }
        }
        return val>0;
    }
    ll Max()
    {
        ll res=0;
        for(ll i=60;i>=0;i--)
        {
            if((res^d[i])>res) res^=d[i];
        }
        return res;
    }
};
struct DataType ans;
struct TreeNodeType {
    ll l,r,mid;
    DataType data;
};
struct TreeNodeType tree[maxn<<2];
ll n,m,deep[maxn],id[maxn],size[maxn],f[maxn],head[maxn];
ll E[maxn<<1],V[maxn<<1],tot,ai[maxn],bi[maxn],lar[maxn];
ll top[maxn];
inline void in(ll &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void edge_add(ll u,ll v)
{
    E[++tot]=head[u],V[tot]=v,head[u]=tot;
    E[++tot]=head[v],V[tot]=u,head[v]=tot;
}
void merge(DataType &a,DataType b)
{
    for(ll i=0;i<=60;i++)
    {
        if(b.d[i]) a.insert(b.d[i]);
    }
}
void dfs1(ll now,ll fa)
{
    f[now]=fa,deep[now]=deep[fa]+1,size[now]=1;
    for(ll i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now),size[now]+=size[V[i]];
        if(size[lar[now]]<size[V[i]]) lar[now]=V[i];
    }
}
void dfs2(ll now,ll chain)
{
    top[now]=chain,id[now]=++tot,bi[tot]=ai[now];
    if(lar[now])
    {
        dfs2(lar[now],chain);
        for(ll i=head[now];i;i=E[i])
        {
            if(V[i]==lar[now]||V[i]==f[now]) continue;
            dfs2(V[i],V[i]);
        }
    }
}
void build(ll now,ll l,ll r)
{
    tree[now].l=l,tree[now].r=r;
    if(l==r)
    {
        tree[now].data.insert(bi[l]);
        return;
    }
    tree[now].mid=l+r>>1;
    build(now<<1,l,tree[now].mid),build(now<<1|1,tree[now].mid+1,r);
    tree[now].data=tree[now<<1].data;
    merge(tree[now].data,tree[now<<1|1].data);
}
void query(ll now,ll l,ll r)
{
    if(tree[now].l>=l&&tree[now].r<=r)
    {
        merge(ans,tree[now].data);
        return;
    }
    if(l<=tree[now].mid) query(now<<1,l,r);
    if(r>tree[now].mid) query(now<<1|1,l,r);
}
ll query(ll x,ll y)
{
    for(int i=0;i<=60;i++) ans.d[i]=0,ans.p[i]=0;
    ans.cnt=0;
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]]) query(1,id[top[y]],id[y]),y=f[top[y]];
        else query(1,id[top[x]],id[x]),x=f[top[x]];
    }
    if(deep[x]>deep[y]) swap(x,y);
    query(1,id[x],id[y]);
    return ans.Max();
}
int main()
{
    in(n),in(m);ll u,v;
    for(ll i=1;i<=n;i++) in(ai[i]);
    for(ll i=1;i<n;i++)in(u),in(v),edge_add(u,v);
    dfs1(1,0),tot=0,dfs2(1,1),build(1,1,n);
    while(m--) in(u),in(v),printf("%lld\n",query(u,v));
    return 0;
}
