#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define ll long long
#define maxtree maxn*25
class TreeType
{
    public:
        ll ch[maxtree][2],val[maxtree],tot,head[maxn],E[maxn<<1];
        ll V[maxn<<1],cnt,deep[maxn],top[maxn],f[maxn],size[maxn];
        ll lar[maxn],li[maxn],ri[maxn],tag,root[maxn],dis[maxn];
        ll n;
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
        void edge_add(ll u,ll v)
        {
            E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
            E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
        }
        void dfs1(ll now,ll fa)
        {
            deep[now]=deep[fa]+1,size[now]=1,f[now]=fa;
            for(ll i=head[now];i;i=E[i])
            {
                if(V[i]==fa) continue;
                dfs1(V[i],now),size[now]+=size[V[i]];
                if(size[V[i]]>=size[lar[now]]) lar[now]=V[i];
            }
        }
        void dfs2(ll now,ll chain)
        {
            top[now]=chain,li[now]=++tag,dis[tag]=now;
            if(lar[now]) dfs2(lar[now],chain);
            for(ll i=head[now];i;i=E[i])
            {
                if(V[i]==lar[now]||V[i]==f[now]) continue;
                dfs2(V[i],V[i]);
            }
            ri[now]=tag;
        }
        void add(ll &now,ll pre,ll l,ll r,ll to)
        {
            now=++tot,val[now]=val[pre]+1;
            if(l==r) return;ll mid=l+r>>1;
            if(to<=mid) add(ch[now][0],ch[pre][0],l,mid,to),ch[now][1]=ch[pre][1];
            else add(ch[now][1],ch[pre][1],mid+1,r,to),ch[now][0]=ch[pre][0];
        }
        ll query(ll qu,ll to)
        {
            ll now=root[ri[qu]],pre=root[li[qu]-1],l=1,r=n,dis,mid;
            while(1)
            {
                if(l==r) return l;
                dis=val[ch[now][0]]-val[ch[pre][0]],mid=l+r>>1;
                if(dis>=to) now=ch[now][0],pre=ch[pre][0],r=mid;
                else to-=dis,now=ch[now][1],pre=ch[pre][1],l=mid+1;
            }
        }
        ll Rank(ll qu,ll to)
        {
            ll now=root[ri[qu]],pre=root[li[qu]-1],l=1,r=n,dis,mid;
            ll res=0;
            while(1)
            {
                if(l==r) return res+val[now]-val[pre];
                dis=val[ch[now][0]]-val[ch[pre][0]],mid=l+r>>1;
                if(to>mid) res+=dis,now=ch[now][1],pre=ch[pre][1];
                else now=ch[now][0],pre=ch[pre][0];
            }
        }
        void makeit(ll _n)
        {
            n=_n;ll u,v;
            for(ll i=1;i<n;i++)
            {
                in(u),in(v);
                edge_add(u,v);
            }
            dfs1(1,0),dfs2(1,1);
            for(ll i=1;i<=n;i++) add(root[i],root[i-1],1,n,dis[i]);
        }
        ll lca(ll x,ll y)
        {
            while(top[x]!=top[y])
                if(deep[top[x]]>deep[top[y]]) x=f[top[x]];
                else y=f[top[y]];
            if(deep[x]>deep[y]) swap(x,y);
            return x;
        }
};
class TreeType tree;
ll n,m,q,li[maxn],ri[maxn],deep[maxn],size[maxn],top[maxn];
ll f[maxn],fdeep[maxn],rot[maxn],frot[maxn],cnt,head[maxn];
ll E[maxn<<1],V[maxn<<1],tot,tag,lar[maxn];
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
ll find(ll v)
{
    ll l=1,r=tot,mid;
    while(l<=r)
    {
        mid=l+r>>1;
        if(v>=li[mid]&&v<=ri[mid]) return mid;
        if(v<li[mid]) r=mid-1;
        else l=mid+1;
    }
    return l;
}
void dfs1(ll now,ll fa)
{
    f[now]=fa,deep[now]=deep[fa]+1,size[now]=1;
    for(ll i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now),size[now]+=size[V[i]];
        if(size[lar[now]]<=size[V[i]]) lar[now]=V[i];
    }
}
void dfs2(ll now,ll chain)
{
    top[now]=chain;
    if(lar[now]) dfs2(lar[now],chain);
    for(ll i=head[now];i;i=E[i])
    {
        if(V[i]==lar[now]||V[i]==f[now]) continue;
        dfs2(V[i],V[i]);
    }
}
void dfs3(ll now)
{
    if(now==1) fdeep[now]=1;
    else
    {
        ll fa=f[now],tmp=find(frot[now]);
        ll pos=frot[now]-li[tmp]+1,now_deep=tree.query(rot[fa],pos);
        now_deep=tree.deep[now_deep]-tree.deep[rot[fa]],fdeep[now]=now_deep+fdeep[fa]+1;
    }
    for(ll i=head[now];i;i=E[i])
        if(V[i]!=f[now]) dfs3(V[i]);
}
ll getdeep(ll now)
{
    ll tmp=find(now),pos=tree.query(rot[tmp],now-li[tmp]+1);
    return tree.deep[pos]-tree.deep[rot[tmp]]+fdeep[tmp];
}
ll getlca(ll x,ll y)
{
    ll tmpx=find(x),tmpy=find(y);
flag1:
    if(tmpx==tmpy)
    {
        ll idx=x-li[tmpx]+1,idy=y-li[tmpy]+1;
        idx=tree.query(rot[tmpx],idx);
        idy=tree.query(rot[tmpx],idy);
        ll lca=tree.lca(idx,idy);
        return fdeep[tmpx]+tree.deep[lca]-tree.deep[rot[tmpx]];
    }
    ll tx=tmpx,ty=tmpy;
    while(top[tx]!=top[ty])
        if(deep[top[tx]]>deep[top[ty]]) tx=f[top[tx]];
        else ty=f[top[ty]];
    if(deep[tx]>deep[ty]) swap(tx,ty);
    ll lca=tx;
    if(tmpx==lca||tmpy==lca)
    {
        if(tmpy==lca) swap(x,y),swap(tmpx,tmpy);
        ll fy;
        while(top[tmpy]!=top[tmpx]) fy=frot[top[tmpy]],tmpy=f[top[tmpy]];
        if(tmpy!=tmpx) y=frot[lar[lca]];else y=fy;
        tmpy=tmpx;
        goto flag1;
    }
    ll fx,fy;
    while(top[tmpx]!=top[lca]) fx=frot[top[tmpx]],tmpx=f[top[tmpx]];
    if(tmpx!=lca) x=frot[lar[lca]];else x=fx;
    while(top[tmpy]!=top[lca]) fy=frot[top[tmpy]],tmpy=f[top[tmpy]];
    if(tmpy!=lca) y=frot[lar[lca]];else y=fy;
    tmpx=tmpy=lca;goto flag1;
}
int main()
{
    in(n),in(m),in(q),tree.makeit(n);ll u,v;
    tot=1,li[1]=1,ri[1]=n,tag=n,rot[1]=1;ll size_,tmp;
    for(ll i=1;i<=m;i++)
    {
        in(u),in(v),tot++,size_=tree.size[u],rot[tot]=u;
        li[tot]=tag+1,ri[tot]=tag+size_,tag=ri[tot],tmp=find(v);
        E[++cnt]=head[tmp],V[cnt]=tot,head[tmp]=cnt,frot[tot]=v;
        E[++cnt]=head[tot],V[cnt]=tmp,head[tot]=cnt;
    }
    dfs1(1,0),dfs2(1,1),dfs3(1);
    for(ll i=1;i<=q;i++)
    {
        in(u),in(v);
        printf("%lld\n",getdeep(u)+getdeep(v)-getlca(u,v)*2);
    }
    return 0;
}
