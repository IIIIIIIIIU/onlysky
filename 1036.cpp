#include <cstdio>
#include <iostream>
#include <algorithm>
 
#define maxn 30001
 
using namespace std;
 
struct TreeNodeType {
    int l,r,dis,mid,max_;
};
struct TreeNodeType tree[maxn<<2];
 
struct EdgeType {
    int to,next;
};
struct EdgeType edge[maxn<<1];
 
int if_z,n,m,dis[maxn],Enum,f[maxn],deep[maxn];
int size[maxn],tot,flag[maxn],belong[maxn],dis_[maxn];
int head[maxn],cnt;
 
char Cget;
 
inline void read_int(int &now)
{
    if_z=1,now=0,Cget=getchar();
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
 
inline void edge_add(int from,int to)
{
    edge[++Enum].to=from,edge[Enum].next=head[to],head[to]=Enum;
    edge[++Enum].to=to,edge[Enum].next=head[from],head[from]=Enum;
}
 
void search(int now,int fa)
{
    int pos=tot++;
    f[now]=fa,deep[now]=deep[fa]+1;
    for(int i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==fa) continue;
        search(edge[i].to,now);
    }
    size[now]=tot-pos;
}
 
void search_(int now,int chain)
{
    flag[now]=++cnt,belong[now]=chain;
    dis_[flag[now]]=dis[now];
    int pos=0;
    for(int i=head[now];i;i=edge[i].next)
    {
        if(flag[edge[i].to]) continue;
        if(size[edge[i].to]>size[pos]) pos=edge[i].to;
    }
    if(pos!=0) search_(pos,chain);
    else return ;
    for(int i=head[now];i;i=edge[i].next)
    {
        if(flag[edge[i].to]) continue;
        search_(edge[i].to,edge[i].to);
    }
}
 
int max(int SOME1,int SOME2)
{
    if(SOME1>SOME2) return SOME1;
    else return SOME2;
}
 
inline void tree_up(int now)
{
    tree[now].dis=tree[now<<1].dis+tree[now<<1|1].dis;
    tree[now].max_=max(tree[now<<1].max_,tree[now<<1|1].max_);
}
 
void tree_build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r;
    if(l==r)
    {
        tree[now].dis=dis_[++cnt];
        tree[now].max_=dis_[cnt];
        return ;
    }
    tree[now].mid=(l+r)>>1;
    tree_build(now<<1,l,tree[now].mid);
    tree_build(now<<1|1,tree[now].mid+1,r);
    tree_up(now);
}
 
void tree_change(int now,int to,int x)
{
    if(tree[now].l==tree[now].r&&tree[now].l==to)
    {
        tree[now].dis=x,tree[now].max_=x;
        return ;
    }
    if(to>tree[now].mid) tree_change(now<<1|1,to,x);
    else tree_change(now<<1,to,x);
    tree_up(now);
}
 
int tree_query_max(int now,int l,int r)
{
    if(tree[now].l==l&&tree[now].r==r)
    {
        return tree[now].max_;
    }
    if(l>tree[now].mid) return tree_query_max(now<<1|1,l,r);
    else if(r<=tree[now].mid) return tree_query_max(now<<1,l,r);
    else return max(tree_query_max(now<<1,l,tree[now].mid),tree_query_max(now<<1|1,tree[now].mid+1,r));
}
 
int tree_query_dis(int now,int l,int r)
{
    if(tree[now].l==l&&tree[now].r==r)
    {
        return tree[now].dis;
    }
    if(l>tree[now].mid) return tree_query_dis(now<<1|1,l,r);
    else if(r<=tree[now].mid) return tree_query_dis(now<<1,l,r);
    else return tree_query_dis(now<<1,l,tree[now].mid)+tree_query_dis(now<<1|1,tree[now].mid+1,r);
}
 
inline int solve_dis(int x,int y)
{
    int ans=0;
    while(belong[x]!=belong[y])
    {
        if(deep[belong[x]]<deep[belong[y]]) swap(x,y);
        ans+=tree_query_dis(1,flag[belong[x]],flag[x]);
        x=f[belong[x]];
    }
    ans+=tree_query_dis(1,min(flag[x],flag[y]),max(flag[x],flag[y]));
    return ans;
}
 
inline int solve_max(int x,int y)
{
    int ans=-0x7ffffff;
    while(belong[x]!=belong[y])
    {
        if(deep[belong[x]]<deep[belong[y]]) swap(x,y);
        ans=max(ans,tree_query_max(1,flag[belong[x]],flag[x]));
        x=f[belong[x]];
    }
    ans=max(ans,tree_query_max(1,min(flag[x],flag[y]),max(flag[x],flag[y])));
    return ans;
}
 
int main()
{
    read_int(n);
    int from,to;
    for(int i=1;i<n;i++)
    {
        read_int(from),read_int(to);
        edge_add(from,to);
    }
    for(int i=1;i<=n;i++) read_int(dis[i]);
    search(1,0),search_(1,1),cnt=0,tree_build(1,1,n);
    read_int(m);
    char ch[10];
    for(int i=1;i<=m;i++)
    {
        scanf("%s",ch);read_int(from),read_int(to);
        if(ch[0]=='C')
        {
            tree_change(1,flag[from],to);
        }
        else
        {
            if(ch[1]=='S') printf("%d\n",solve_dis(from,to));
            else printf("%d\n",solve_max(from,to));
        }
    }
    return 0;
}
