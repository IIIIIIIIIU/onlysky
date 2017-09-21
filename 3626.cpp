#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxm maxn<<2
#define ll long long
#define mod 201314
struct QueryType {
    int now,id,pos,z;
    bool operator<(const QueryType pos)const
    {
        return now<pos.now;
    }
};
struct QueryType qu[maxn<<1];
int n,m,f[maxn],top[maxn],lar[maxn],size[maxn],id[maxn],deep[maxn];
int L[maxm],R[maxm],mid[maxm],head[maxn],E[maxn],V[maxn],cnt;
ll dis[maxm],ans[maxn],flag[maxm],Qes;
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void dfs1(int now)
{
    size[now]=1,deep[now]=deep[f[now]]+1;
    for(int i=head[now];i;i=E[i])
    {
        dfs1(V[i]),size[now]+=size[V[i]];
        if(size[lar[now]]<size[V[i]]) lar[now]=V[i];
    }
}
void dfs2(int now,int chain)
{
    top[now]=chain,id[now]=++cnt;
    if(lar[now]) dfs2(lar[now],chain);
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==lar[now]) continue;
        dfs2(V[i],V[i]);
    }
}
void build(int now,int l,int r)
{
    L[now]=l,R[now]=r;if(l==r) return;mid[now]=l+r>>1;
    build(now<<1,l,mid[now]),build(now<<1|1,mid[now]+1,r);
}
void downdata(int now)
{
    flag[now<<1]+=flag[now],flag[now<<1|1]+=flag[now];
    dis[now<<1]+=flag[now]*(R[now<<1]-L[now<<1]+1);
    dis[now<<1|1]+=flag[now]*(R[now<<1|1]-L[now<<1|1]+1);
    flag[now]=0;
}
void add(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r)
    {
        dis[now]+=R[now]-L[now]+1,flag[now]+=1;
        return;
    }
    if(flag[now]) downdata(now);
    if(l<=mid[now]) add(now<<1,l,r);
    if(r>mid[now]) add(now<<1|1,l,r);
    dis[now]=dis[now<<1]+dis[now<<1|1];
}
void query(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r)
    {
        Qes+=dis[now];return;
    }
    if(flag[now]) downdata(now);
    if(l<=mid[now]) query(now<<1,l,r);
    if(r>mid[now]) query(now<<1|1,l,r);
}
void add(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]]) add(1,id[top[y]],id[y]),y=f[top[y]];
        else add(1,id[top[x]],id[x]),x=f[top[x]];
    }
    if(deep[x]>deep[y]) swap(x,y);add(1,id[x],id[y]);
}
ll query(int x,int y)
{
    ll res=0;
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]])
        {
            Qes=0,query(1,id[top[y]],id[y]);
            res+=Qes,y=f[top[y]];
        }
        else
        {
            Qes=0,query(1,id[top[x]],id[x]);
            res+=Qes,x=f[top[x]];
        }
    }
    if(deep[x]>deep[y]) swap(x,y);
    Qes=0,query(1,id[x],id[y]);
    return res+Qes;
}
int main()
{
    in(n),in(m);int u,v,w;
    for(int i=2;i<=n;i++)
    {
        in(u),u++,f[i]=u;
        E[++cnt]=head[u],V[cnt]=i,head[u]=cnt;
    }
    cnt=0,dfs1(1),dfs2(1,1),build(1,1,n),cnt=0;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v),in(w),w++;
        qu[++cnt].now=u,qu[cnt].id=i,qu[cnt].pos=-1,qu[cnt].z=w;
        qu[++cnt].now=v,qu[cnt].id=i,qu[cnt].pos=1,qu[cnt].now++,qu[cnt].z=w;
    }
    sort(qu+1,qu+cnt+1);int tot=0;
    for(int i=1;i<=cnt;i++)
    {
        if(qu[i].now==0) continue;
        while(tot<qu[i].now) add(++tot,1);
        ans[qu[i].id]+=query(qu[i].z,1)*qu[i].pos;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]%mod);
    return 0;
}
