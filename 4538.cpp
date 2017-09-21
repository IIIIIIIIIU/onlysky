#pragma GCC optimize("O2")
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 200005
#define maxm 400005
struct QueryType
{
    int u,v,x;
};
struct QueryType quest[maxn];
struct DataType
{
    int l,r;
    bool operator<(const DataType pos)const
    {
        return l<pos.l;
    }
};
struct DataType bi[maxn];
class TreeNodeType
{
    public:
    int l,r,mid;
    priority_queue<int>ins,del;
    int get()
    {
        while(!del.empty()&&(ins.top()==del.top())) del.pop(),ins.pop();
        if(!ins.empty()) return ins.top();
        else return -1;
    }
};
class TreeNodeType tree[(maxn<<2)+1];
int n,m,deep[maxn],top[maxn],f[maxn],id[maxn],size[maxn];
int head[maxn],cnt,V[maxm],E[maxm],lar[maxn],res;
int val,opp,to;
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void dfs1(int now,int fa)
{
    deep[now]=deep[fa]+1,f[now]=fa,size[now]=1;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now),size[now]+=size[V[i]];
        if(size[V[i]]>=size[lar[now]]) lar[now]=V[i];
    }
}
void dfs2(int now,int chain)
{
    top[now]=chain,id[now]=++cnt;
    if(lar[now]) dfs2(lar[now],chain);
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==f[now]||V[i]==lar[now]) continue;
        dfs2(V[i],V[i]);
    }
}
inline void build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r;if(l==r) return;tree[now].mid=l+r>>1;
    build(now<<1,l,tree[now].mid),build(now<<1|1,tree[now].mid+1,r);
}
void add(int now,int l,int r)
{
    if(tree[now].l>=l&&tree[now].r<=r)
    {
        if(opp) tree[now].ins.push(val);
        else
        {
            if(val!=tree[now].ins.top()) tree[now].del.push(val);
            else tree[now].ins.pop();
        }
        return;
    }
    if(l<=tree[now].mid) add(now<<1,l,r);
    if(r>tree[now].mid) add(now<<1|1,l,r);
}
void query(int now)
{
    while(1)
    {
        res=max(res,tree[now].get());
        if(tree[now].l==tree[now].r) return;
        if(to<=tree[now].mid) now=now<<1;
        else now=now<<1|1;
    }
}
void solve(int x,int y)
{
    int tag=0;
    while(top[x]!=top[y])
    {
        if(deep[top[x]]>deep[top[y]]) bi[++tag].l=id[top[x]],bi[tag].r=id[x],x=f[top[x]];
        else bi[++tag].l=id[top[y]],bi[tag].r=id[y],y=f[top[y]];
    }
    if(deep[x]>deep[y]) swap(x,y);
    bi[++tag].l=id[x],bi[tag].r=id[y],sort(bi+1,bi+tag+1);
    int now=1;
    for(int i=1;i<=tag;i++)
    {
        if(bi[i].l>now) add(1,now,bi[i].l-1);
        now=bi[i].r+1;
    }
    if(now<=n) add(1,now,n);
}
int main()
{
    in(n),in(m);int u,v;
    for(int i=1;i<n;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    dfs1(1,0),cnt=0,dfs2(1,1),cnt=0,build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        in(u);
        if(u==0)
        {
            in(quest[i].u),in(quest[i].v),in(quest[i].x);
            val=quest[i].x,opp=true;
            solve(quest[i].u,quest[i].v);
        }
        else if(u==1)
        {
            in(v),val=quest[v].x,opp=false;
            solve(quest[v].u,quest[v].v);
        }
        else in(u),res=-1,to=id[u],query(1),printf("%d\n",res);
    }
    return 0;
}
