#include <bits/stdc++.h>
using namespace std;
#define maxn 200005
#define maxm maxn*100
int deep[maxn],f[maxn],id[maxn],top[maxn],cnt,soot;
int head[maxn],V[maxn],E[maxn],lar[maxn],size[maxn];
int val[maxm],root[maxn],ch[maxm][2],tot,Tl,Tr,n,m,Ans;
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
void build(int &now,int l,int r)
{
    now=++tot;
    if(l==r) return;int mid=l+r>>1;
    build(ch[now][0],l,mid);
    build(ch[now][1],mid+1,r);
}
void add(int &now,int pre,int l,int r,int to,int x)
{
    now=++tot,val[now]=val[pre]+x;
    if(l==r) return;int mid=l+r>>1;
    if(to<=mid) add(ch[now][0],ch[pre][0],l,mid,to,x),ch[now][1]=ch[pre][1];
    else add(ch[now][1],ch[pre][1],mid+1,r,to,x),ch[now][0]=ch[pre][0];
}
int lowbit(int x)
{
    return x&(-x);
}
void add(int to1,int to2,int x)
{
    while(to1<=n) add(root[to1],root[to1],1,m,to2,x),to1+=lowbit(to1);
}
void dfs1(int now)
{
    deep[now]=deep[f[now]]+1,size[now]=1;
    for(int i=head[now];i;i=E[i])
    {
        dfs1(V[i]),size[now]+=size[V[i]];
        if(size[lar[now]]<size[V[i]]) lar[now]=V[i];
    }
}
void dfs2(int now,int chain)
{
    top[now]=chain,id[now]=++cnt;
    root[id[now]]=root[0];
    if(lar[now])
    {
        dfs2(lar[now],chain);
        for(int i=head[now];i;i=E[i])
        {
            if(V[i]==lar[now]) continue;
            dfs2(V[i],V[i]);
        }
    }
}
int query(int now,int l,int r)
{
    if(l>=Tl&&r<=Tr) return val[now];
    int mid=l+r>>1,res=0;
    if(Tl<=mid) res+=query(ch[now][0],l,mid);
    if(Tr>mid) res+=query(ch[now][1],mid+1,r);
    return res;
}
int query(int l,int r)
{
    l--;int res=0;
    while(r) res+=query(root[r],1,m),r-=lowbit(r);
    while(l) res-=query(root[l],1,m),l-=lowbit(l);
    return res;
}
int query(int x,int y,int tl,int tr)
{
    int res=0;Tl=tl,Tr=tr;
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]]) res+=query(id[top[y]],id[y]),y=f[top[y]];
        else res+=query(id[top[x]],id[x]),x=f[top[x]];
    }
    if(deep[x]>deep[y]) swap(x,y);
    res+=query(id[x],id[y]);
    return res;
}
int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(deep[top[x]]>deep[top[y]]) x=f[top[x]];
        else y=f[top[y]];
    }
    return deep[x]<deep[y]?deep[x]:deep[y];
}
int main()
{
    in(n);int op,u,v,c;
    for(int i=1;i<=n;i++)
    {
        in(f[i]);
        if(!f[i]) soot=i;
        else E[i]=head[f[i]],V[i]=i,head[f[i]]=i;
    }
    in(m);
    build(root[0],1,m),dfs1(soot),dfs2(soot,soot);
    for(int i=1;i<=m;i++)
    {
        in(op);
        if(op==2)in(u),add(id[u],i,1);
        else
        {
            in(u),in(v),in(c),Ans=deep[u]+deep[v]-2*lca(u,v)+1;
            printf("%d ",Ans);
            if(i-c-1>=1) printf("%d\n",query(u,v,1,i-c-1));
            else printf("0\n");
        }
    }
    return 0;
}
