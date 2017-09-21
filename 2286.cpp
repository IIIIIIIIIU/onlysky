#include <bits/stdc++.h>
using namespace std;
#define INF 1e17
#define maxn 250005
#define ll long long 
#define maxm (maxn<<1)
struct LandType {
    ll id,key;
    bool operator<(const LandType pos)const
    {
        return key<pos.key;
    }
};
struct LandType ai[maxn];
ll n,head[maxn],E[maxm],V[maxm],W[maxm],cnt;
ll size[maxn],top[maxn],f[maxn],deep[maxn];
ll lar[maxn],m,id[maxn],dis[maxn],li[maxn];
ll ri[maxn],sta[maxn];
bool if_[maxn];
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
inline void edge_add(ll u,ll v,ll w)
{
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
}
inline void edge_add(ll u,ll v)
{
//    printf("%d %d\n",u,v);
    E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
}
void dfs1(ll now,ll fa,ll pi)
{
    deep[now]=deep[fa]+1,f[now]=fa;
    dis[now]=pi,size[now]=1;
    for(ll i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now,min(pi,W[i]));
        size[now]+=size[V[i]];
        if(size[V[i]]>size[lar[now]])lar[now]=V[i];
    }
}
void dfs2(ll now,ll chain)
{
    top[now]=chain,id[now]=++cnt,li[now]=cnt;
    if(lar[now])
    {
        dfs2(lar[now],chain);
        for(ll i=head[now];i;i=E[i])
        {
            if(V[i]==f[now]||V[i]==lar[now]) continue;
            dfs2(V[i],V[i]);
        }
    }
    ri[now]=cnt;
}
inline ll find(ll x,ll y)
{
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]]) swap(x,y);
        x=f[top[x]];
    }
    return deep[x]<deep[y]?x:y;
}
ll dp(ll now,ll fa)
{
    bool flag=false;
    ll pos=0;
    for(ll i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        pos+=dp(V[i],now),flag=true;
    }
    bool myj=if_[now];head[now]=0;if_[now]=false;
    if(flag&&!myj) return min(pos,dis[now]);
    else return dis[now];
}
int main()
{
    in(n);ll u,v,w,ki;
    for(ll i=1;i<n;i++)in(u),in(v),in(w),edge_add(u,v,w);
    cnt=0,dfs1(1,0,INF),dfs2(1,1),in(m); 
    memset(if_,0,sizeof(if_));memset(head,0,sizeof(head));
    while(m--)
    {
        in(ki),cnt=0;
        for(ll i=1;i<=ki;i++) in(ai[i].id),ai[i].key=id[ai[i].id],if_[ai[i].id]=true;
        sort(ai+1,ai+ki+1);ll p=1;sta[p]=1;
        for(ll i=1;i<=ki;i++)
        {
            ll now=ai[i].id,pos=sta[p],pos_=sta[p-1];
            if(id[now]>li[pos]&&id[now]<=ri[pos]) sta[++p]=now;
            else
            {
                if(id[now]>li[pos_]&&id[now]<=ri[pos_])
                {
                    ll lca=find(now,pos);
                    if(pos!=lca) edge_add(pos,lca);
                    p--;
                    if(lca!=pos_) sta[++p]=lca;
                    sta[++p]=now;
                }
                else
                {
                    while((id[now]<li[pos_]||id[now]>ri[pos_])&&p>1)
                    {
                        edge_add(pos_,pos),p--;
                        pos=sta[p],pos_=sta[p-1];
                    }
                    ll lca=find(now,pos);
                    edge_add(lca,pos),p--;
                    if(pos_!=lca) sta[++p]=lca;
                    sta[++p]=now;
                }
            }
        }
        while(p>1)
        edge_add(sta[p],sta[p-1]),p--;
        printf("%lld\n",dp(1,0));
    }
    return 0;
}
