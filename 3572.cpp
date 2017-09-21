#include <bits/stdc++.h>
using namespace std;
#define maxn 300005
#define INF 0x3f3f3f3f
struct KiType {
    int id,key;
    bool operator<(const KiType pos)const
    {
        return key<pos.key;
    }
};
struct KiType ki[maxn];
int bel[maxn],dis[maxn],size[maxn],li[maxn],ri[maxn],lar[maxn],f[maxn];
int head[maxn],E[maxn<<1],V[maxn<<1],cnt,id[maxn],id_[maxn],deep[maxn];
int top[maxn],ai[maxn],sta[maxn],sum[maxn],n,m;
int W[maxn<<1];
bool vis[maxn],if_[maxn];
queue<int>que;
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
inline void edge_add(int u,int v)
{
    E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
}
inline void edge_add1(int u,int v)
{
    if(deep[u]<deep[v]) swap(u,v);
    int w=deep[u]-deep[v];
//  printf("%d %d %d\n",u,v,w);
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
}
void dfs1(int now,int fa)
{
    f[now]=fa,deep[now]=deep[fa]+1,size[now]=1;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now),size[now]+=size[V[i]];
        if(size[V[i]]>size[lar[now]]) lar[now]=V[i];
    }
}
void dfs2(int now,int chain)
{
    top[now]=chain,id[now]=++cnt,id_[cnt]=now;
    if(lar[now]) dfs2(lar[now],chain);
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==lar[now]||V[i]==f[now]) continue;
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
    return deep[x]<deep[y]?x:y;
}
inline int up(int now,int to)
{
    while(to<deep[top[now]]) now=f[top[now]];
    return id_[id[now]-deep[now]+to];
}
void Count(int now,int fa)
{
    int pos,pos_;
    if(!fa||bel[fa]==bel[now]) goto cur;
    pos=deep[now]-deep[fa]-1;
    if(pos)
    {
        pos_=(dis[fa]+pos+dis[now]+(bel[fa]<bel[now]?1:0))>>1;
        pos_=up(now,pos_-dis[fa]+deep[fa]+1);
        pos_=size[pos_]-size[now];
        sum[bel[now]]+=pos_,sum[bel[fa]]-=pos_;
    }
cur:
    sum[bel[now]]+=size[now];
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        sum[bel[now]]-=size[V[i]];
        Count(V[i],now);
    }
}
void clear(int now,int fa)
{
    for(int i=head[now];i;i=E[i])
    {
        if(fa==V[i]) continue;
        clear(V[i],now);
    }
    head[now]=0,sum[now]=0,dis[now]=0,vis[now]=false;
    bel[now]=0,dis[now]=INF;
}
int main()
{
    in(n);int u,v;
    for(int i=1;i<n;i++) in(u),in(v),edge_add(u,v);
    cnt=0,dfs1(1,0),dfs2(1,1),memset(head,0,sizeof(head));
    in(m);
    for(int i=1;i<=n;i++) dis[i]=INF;
    while(m--)
    {
        in(u),cnt=0;
        for(int i=1;i<=u;i++)
        {
            in(ki[i].id);
            ai[i]=ki[i].id;
            dis[ki[i].id]=0;
            vis[ki[i].id]=true;
            if_[ki[i].id]=true;
            que.push(ki[i].id);
            bel[ki[i].id]=ki[i].id;
            ki[i].key=id[ki[i].id];
        }
        sort(ki+1,ki+u+1),v=1,sta[v]=1;
        for(int i=1;i<=u;i++)
        {
            int now=ki[i].id,pos=0;
            if(sta[v]==now) continue;
            while(id[now]<li[sta[v]]||id[now]>ri[sta[v]])
            {
                if(pos) edge_add1(pos,sta[v]);
                pos=sta[v],v--;
            }
            if(pos)
            {
                int lca=find(pos,now);
                if(lca!=pos) edge_add1(pos,lca);
                if(lca!=sta[v]) sta[++v]=lca;
            }
            sta[++v]=now;
        }
        while(v>1) edge_add1(sta[v],sta[v-1]),v--;
        while(!que.empty())
        {
            int now=que.front();que.pop(),if_[now]=false;
            for(int i=head[now];i;i=E[i])
            {
                if(dis[V[i]]>dis[now]+W[i])
                {
                    dis[V[i]]=dis[now]+W[i];
                    bel[V[i]]=bel[now];
                    if(!if_[V[i]]) if_[V[i]]=true,que.push(V[i]);
                }
                else if(dis[V[i]]==dis[now]+W[i])
                {
                    if(bel[now]<bel[V[i]])
                    {
                        bel[V[i]]=bel[now];
                        if(!if_[V[i]]) if_[V[i]]=true,que.push(V[i]);
                    }
                }
            }
        }
        Count(1,0);
        for(int i=1;i<u;i++) printf("%d ",sum[ai[i]]);
        printf("%d \n",sum[ai[u]]);
        clear(1,0);
    }
    return 0;
}
