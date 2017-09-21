#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define LL long long
#define maxn 100001
 
using namespace std;
 
struct TreeNodeType {
    LL dis,lc,rc;
};
struct TreeNodeType tree[maxn*45];
 
struct EdgeType {
    LL to,next;
};
struct EdgeType edge[maxn<<1];
 
LL if_z,n,m,hash[maxn],hash_[maxn],cnt,head[maxn];
LL size_,tot,root[maxn],deep[maxn],f[maxn],size[maxn];
LL belong[maxn];
 
char Cget;
 
inline void read_int(LL &now)
{
    now=0,if_z=1,Cget=getchar();
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
 
inline void edge_add(LL from,LL to)
{
    cnt++;
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt;
}
 
void tree_build(LL now,LL l,LL r)
{
    tree[now].dis=0;
    if(l==r) return ;
    LL mid=(l+r)>>1;
    tree[now].lc=++tot;
    tree_build(tot,l,mid);
    tree[now].rc=++tot;
    tree_build(tot,mid+1,r);
}
 
void tree_add(LL pre,LL now,LL to,LL l,LL r)
{
    tree[now].dis=tree[pre].dis+1;
    if(l==r) return ;
    LL mid=(l+r)>>1;
    if(to>mid)
    {
        tree[now].lc=tree[pre].lc;
        tree[now].rc=++tot;
        tree_add(tree[pre].rc,tree[now].rc,to,mid+1,r);
    }
    else
    {
        tree[now].rc=tree[pre].rc;
        tree[now].lc=++tot;
        tree_add(tree[pre].lc,tree[now].lc,to,l,mid);
    }
}
 
void search(LL now,LL pre)
{
    LL pos=cnt++;
    f[now]=pre;
    deep[now]=deep[pre]+1;
    hash_[now]=lower_bound(hash+1,hash+size_+1,hash_[now])-hash;
    root[now]=++tot;
    tree_add(root[pre],root[now],hash_[now],1,size_);
    for(LL i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==pre) continue;
        search(edge[i].to,now);
    }
    size[now]=cnt-pos;
}
 
void search_(LL now,LL chain)
{
    LL pos=0;
    belong[now]=chain;
    for(LL i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==f[now]) continue;
        if(size[edge[i].to]>size[pos]) pos=edge[i].to;
    }
    if(pos==0) return ;
    search_(pos,chain);
    for(LL i=head[now];i;i=edge[i].next)
    {
        if(pos==edge[i].to||edge[i].to==f[now]) continue;
        search_(edge[i].to,edge[i].to);
    }
}
 
inline LL tree_lca(LL x,LL y)
{
    while(belong[x]!=belong[y])
    {
        if(deep[belong[x]]<deep[belong[y]]) swap(x,y);
        x=f[belong[x]];
    }
    if(deep[x]<deep[y]) return x;
    else return y;
}
 
inline LL tree_query(LL x,LL y,LL lca,LL flca,LL l,LL r,LL k)
{
    LL dis,mid;
    while(l!=r)
    {
        dis=tree[tree[x].lc].dis+tree[tree[y].lc].dis-tree[tree[lca].lc].dis-tree[tree[flca].lc].dis;
        mid=(l+r)>>1;
        if(k>dis)
        {
            k-=dis;
            l=mid+1;
            lca=tree[lca].rc;
            flca=tree[flca].rc;
            x=tree[x].rc,y=tree[y].rc;
        }
        else
        {
            r=mid;
            lca=tree[lca].lc;
            flca=tree[flca].lc;
            x=tree[x].lc,y=tree[y].lc;
        }
    }
    return l;
}
 
int main()
{
    read_int(n),read_int(m);
    for(LL i=1;i<=n;i++)
    {
        read_int(hash[i]);
        hash_[i]=hash[i];
    }
    LL from,to;
    for(LL i=1;i<n;i++)
    {
        read_int(from),read_int(to);
        edge_add(from,to);
        edge_add(to,from);
    }
    sort(hash+1,hash+n+1);
    size_=unique(hash+1,hash+n+1)-hash-1;
    root[0]=++tot;
    tree_build(root[0],1,size_);
    cnt=0,search(1,0);
    cnt=0,search_(1,1);
    LL K,last=0;
    for(LL i=1;i<=m;i++)
    {
        read_int(from),read_int(to),read_int(K);
        from=from^last;
        LL lca=tree_lca(from,to);
        last=hash[tree_query(root[from],root[to],root[lca],root[f[lca]],1,size_,K)];
        if(i!=m) printf("%lld\n",last);
        else printf("%lld",last);
    }
    return 0;
}
