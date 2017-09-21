#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define maxn 80005
 
using namespace std;
 
struct TreeNodeType {
    int l,r,dis;
};
struct TreeNodeType tree[25000005];
 
struct EdgeType {
    int v,next;
};
struct EdgeType edge[maxn<<2];
 
int if_z,t,n,m,size,dis[maxn],head[maxn];
int cnt,f[maxn][22],ft[maxn],deep[maxn];
int num[maxn],dis_[maxn],last,tot,root[maxn];
 
char Cget;
 
inline void in(int &now)
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
 
inline void edge_add(int u,int v)
{
    cnt++;
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
 
int find(int x)
{
    if(x==ft[x]) return x;
    ft[x]=find(ft[x]);
    return ft[x];
}
 
void tree_add(int pre,int &now,int l,int r,int to)
{
    now=++tot;
    tree[now].dis=tree[pre].dis+1;tree[now].r=tree[pre].r;tree[now].l=tree[pre].l;
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(to<=mid)
    {
        tree_add(tree[pre].l,tree[now].l,l,mid,to);
         
    }
    else
    {
        tree_add(tree[pre].r,tree[now].r,mid+1,r,to);
         
    }
}
 
void search(int now,int pre)
{
    f[now][0]=pre,deep[now]=deep[pre]+1;
    for(int i=1;i<=20;i++) f[now][i]=f[f[now][i-1]][i-1];
    int pos=lower_bound(dis_+1,dis_+size+1,dis[now])-dis_;
    tree_add(root[pre],root[now],1,size,pos);
    for(int i=head[now];i;i=edge[i].next)
    {
        if(edge[i].v==pre) continue;
        search(edge[i].v,now);
    }
}
 
void tree_build(int &now,int l,int r)
{
    now=++tot;
    if(l==r) return ;
    int mid=(l+r)>>1;
    tree_build(tree[now].l,l,mid);
    tree_build(tree[now].r,mid+1,r);
}
 
int get_same(int u,int x)
{
    for(int i=0;i<=20;i++) if(x&(1<<i)) u=f[u][i];
    return u;
}
 
int lca(int x,int y)
{
    if(deep[x]<deep[y]) swap(x,y);
    x=get_same(x,deep[x]-deep[y]);
    if(x==y) return x;
    for(int i=20;i>=0;i--)
    {
        if(f[x][i]!=f[y][i])
        {
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
 
int tree_query(int pre,int fpre,int now,int now_,int k,int l,int r)
{
    if(l==r) return l;
    int pos=tree[tree[now].l].dis+tree[tree[now_].l].dis;
    pos-=(tree[tree[pre].l].dis+tree[tree[fpre].l].dis);
    int mid=(l+r)>>1;
    if(k>pos) return tree_query(tree[pre].r,tree[fpre].r,tree[now].r,tree[now_].r,k-pos,mid+1,r);
    else return tree_query(tree[pre].l,tree[fpre].l,tree[now].l,tree[now_].l,k,l,mid);
}
 
int main()
{
//  freopen("forest.in","r",stdin);
//  freopen("forest.out","w",stdout);
    in(t),in(n),in(m),in(t);
    for(int i=1;i<=n;i++)
    {
        in(dis[i]);
        num[i]=1;
        dis_[i]=dis[i],ft[i]=i;
    }
    sort(dis_+1,dis_+n+1);
    size=unique(dis_+1,dis_+n+1)-dis_-1;
    int u,v,x,y,k;
    while(m--)
    {
        in(u),in(v);
        edge_add(u,v);
        edge_add(v,u);
        x=find(u),y=find(v);
        if(num[x]>num[y])
        {
            ft[y]=x;
            num[x]+=num[y];
        }
        else
        {
            ft[x]=y;
            num[y]+=num[x];
        }
    }
    tree_build(root[0],1,size);
    for(int i=1;i<=n;i++)
    {
        if(ft[i]==i) search(i,0);
    }
    char ch[10];
    while(t--)
    {
        scanf("%s",ch);
        if(ch[0]=='L')
        {
            in(u),in(v);
            u=u^last,v=v^last;
            edge_add(u,v);
            edge_add(v,u);
            x=find(u),y=find(v);
            if(num[x]>num[y])
            {
                ft[y]=x;
                num[x]+=num[y];
                search(v,u);
            }
            else
            {
                ft[x]=y;
                num[y]+=num[x];
                search(u,v);
            }
        }
        else
        {
            in(u),in(v),in(k);
            u=u^last,v=v^last,k=k^last;
            int lca_=lca(u,v);
            last=tree_query(root[lca_],root[f[lca_][0]],root[u],root[v],k,1,size);
            last=dis_[last];
            printf("%d\n",last);
        }
    }
    return 0;
}
