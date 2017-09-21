#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define LL long long
#define maxn 100005
 
using namespace std;
 
struct TreeNodeType {
    LL l,r,dis,mid,flag;
};
struct TreeNodeType tree[maxn<<2];
 
struct EdgeType {
    LL to,next;
};
struct EdgeType edge[maxn<<1];
 
LL if_z,n,m,deep[maxn],top[maxn],end[maxn];
LL flag[maxn],size[maxn],head[maxn],cnt;
LL dis[maxn],dis_[maxn],f[maxn];
 
char Cget;
 
inline void in(LL &now)
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
 
inline void edge_add(LL u,LL v)
{
    cnt++;
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
 
void search_1(LL now,LL fa)
{
    LL pos=cnt++;
    f[now]=fa,deep[now]=deep[fa]+1;
    for(LL i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==fa) continue;
        search_1(edge[i].to,now);
    }
    size[now]=cnt-pos;
}
 
void search_2(LL now,LL chain)
{
    flag[now]=++cnt,top[now]=chain;
    LL pos=0;dis_[cnt]=dis[now];
    for(LL i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==f[now]) continue;
        if(size[edge[i].to]>size[pos]) pos=edge[i].to;
    }
    if(pos) search_2(pos,chain);
    for(LL i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==f[now]||edge[i].to==pos) continue;
        search_2(edge[i].to,edge[i].to);
    }
    end[now]=cnt;
}
 
void tree_build(LL now,LL l,LL r)
{
    tree[now].l=l,tree[now].r=r;
    if(l==r)
    {
        tree[now].dis=dis_[l];
        return ;
    }
    tree[now].mid=(l+r)>>1;
    tree_build(now<<1,l,tree[now].mid);
    tree_build(now<<1|1,tree[now].mid+1,r);
    tree[now].dis=tree[now<<1].dis+tree[now<<1|1].dis;
}
 
void tree_change(LL now,LL l,LL r,LL x)
{
    if(tree[now].l==l&&tree[now].r==r)
    {
        tree[now].dis+=(r-l+1)*x;
        tree[now].flag+=x;
        return ;
    }
    if(tree[now].flag)
    {
        tree[now<<1].dis+=(tree[now].mid-tree[now<<1].l+1)*tree[now].flag;
        tree[now<<1|1].dis+=(tree[now<<1|1].r-tree[now].mid)*tree[now].flag;
        tree[now<<1].flag+=tree[now].flag;
        tree[now<<1|1].flag+=tree[now].flag;
        tree[now].flag=0;
    }
    if(l>tree[now].mid) tree_change(now<<1|1,l,r,x);
    else if(r<=tree[now].mid) tree_change(now<<1,l,r,x);
    else
    {
        tree_change(now<<1,l,tree[now].mid,x);
        tree_change(now<<1|1,tree[now].mid+1,r,x);
    }
    tree[now].dis=tree[now<<1|1].dis+tree[now<<1].dis;
}
 
LL tree_query(LL now,LL l,LL r)
{
    if(tree[now].l==l&&tree[now].r==r) return tree[now].dis;
    if(tree[now].flag)
    {
        tree[now<<1].dis+=(tree[now].mid-tree[now<<1].l+1)*tree[now].flag;
        tree[now<<1|1].dis+=(tree[now<<1|1].r-tree[now].mid)*tree[now].flag;
        tree[now<<1].flag+=tree[now].flag;
        tree[now<<1|1].flag+=tree[now].flag;
        tree[now].flag=0;
    }
    if(l>tree[now].mid) return tree_query(now<<1|1,l,r);
    else if(r<=tree[now].mid) return tree_query(now<<1,l,r);
    else return tree_query(now<<1,l,tree[now].mid)+tree_query(now<<1|1,tree[now].mid+1,r);
}
 
LL solve_query(LL x,LL y)
{
    LL pos=0;
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]]) swap(x,y);
        pos+=tree_query(1,flag[top[x]],flag[x]);
        x=f[top[x]];
    }
    if(deep[x]>deep[y]) swap(x,y);
    pos+=tree_query(1,flag[x],flag[y]);
    return pos;
}
 
int main()
{
    in(n),in(m);
    for(LL i=1;i<=n;i++) in(dis[i]);
    LL u,v;
    for(LL i=1;i<n;i++)
    {
        in(u),in(v);
        edge_add(u,v);
        edge_add(v,u);
    }
    cnt=0,search_1(1,0);
    cnt=0,search_2(1,1);
    tree_build(1,1,n);
    while(m--)
    {
        in(u);
        if(u==1)
        {
            in(u),in(v);
            tree_change(1,flag[u],flag[u],v);
        }
        else if(u==2)
        {
            in(u),in(v);
            tree_change(1,flag[u],end[u],v);
        }
        else
        {
            in(v);
            cout<<solve_query(1,v);
            putchar('\n');
        }
    }
    return 0;
}
