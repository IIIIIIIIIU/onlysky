#include <bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define INF 2000000000
#define ll long long
ll head[maxn],E[maxn<<1],V[maxn<<1],W[maxn<<1],deep[maxn];
ll f[maxn],lar[maxn],size[maxn],id[maxn],top[maxn],cnt;
ll poi[maxn],sta[maxn],val[maxn],minv[maxn],maxv[maxn];
ll tot,ans1,ans2,n,m,num;
bool has[maxn];
inline void in(ll &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void dfs1(ll now,ll fa)
{
    deep[now]=deep[fa]+1,f[now]=fa,size[now]=1;
    for(ll i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now),size[now]+=size[V[i]];
        if(size[lar[now]]<=size[V[i]]) lar[now]=V[i];
    }
}
void dfs2(ll now,ll chain)
{
    top[now]=chain,id[now]=++cnt;
    if(lar[now]) dfs2(lar[now],chain);
    for(ll i=head[now];i;i=E[i])
    {
        if(V[i]==f[now]||V[i]==lar[now]) continue;
        dfs2(V[i],V[i]);
    }
}
ll get(ll x,ll y)
{
    while(top[x]!=top[y])
    {
        if(deep[top[x]]>deep[top[y]]) x=f[top[x]];
        else y=f[top[y]];
    }
    if(deep[x]>deep[y]) swap(x,y);return x;
}
bool cmp(ll a,ll b)
{
    return id[a]<id[b];
}
void edge_add(ll u,ll v)
{
    if(u==v) return;
    ll w=deep[v]-deep[u];
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
}
void dp(ll now)
{
    ll tmp=0;
    size[now]=has[now],val[now]=0;
    minv[now]=has[now]?0:INF;
    maxv[now]=has[now]?0:-INF;
    for(ll i=head[now];i;i=E[i])
    {
        ll y=V[i];
        dp(y);
        tot+=(val[now]+size[now]*W[i])*size[y]+val[y]*size[now];
        size[now]+=size[y];
        val[now]+=val[y]+W[i]*size[y];
        ans1=min(ans1,minv[now]+minv[y]+W[i]);
        ans2=max(ans2,maxv[now]+maxv[y]+W[i]);
        minv[now]=min(minv[now],minv[y]+W[i]);
        maxv[now]=max(maxv[now],maxv[y]+W[i]);
    }
    head[now]=0,has[now]=0;
}
int main()
{
    in(n);ll u,v;
    for(ll i=1;i<n;i++)
    {
        in(u),in(v);
        edge_add(u,v);
        edge_add(v,u);
    }
    dfs1(1,0),cnt=0,dfs2(1,1);
    in(m);for(ll i=1;i<=n;i++) head[i]=0;
    while(m--)
    {
        in(num);
        for(ll i=1;i<=num;i++) in(poi[i]);
        for(ll i=1;i<=num;i++) has[poi[i]]=true;
        sort(poi+1,poi+num+1,cmp);
        ll to=0;cnt=0;
        sta[++to]=1;ll x,f;
        for(ll i=1;i<=num;i++)
        {
            x=poi[i],f=get(x,sta[to]);
            if(f==sta[to])
            {
                sta[++to]=x;
                continue;
            }
            while(f==get(x,sta[to-1]))
            {
                edge_add(sta[to-1],sta[to]);
                to--,f=get(x,sta[to]);
            }
            edge_add(f,sta[to]);
            sta[to]=f,sta[++to]=x;
        }
        while(--to) edge_add(sta[to],sta[to+1]);
        ans1=INF,ans2=-INF,tot=0,dp(1);
        printf("%lld %lld %lld\n",tot,ans1,ans2);
    }
    return 0;
}
