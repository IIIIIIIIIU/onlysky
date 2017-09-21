#include <bits/stdc++.h>
using namespace std;
#define maxn 500005
struct TreeNodeType {
    int l,r,mid,dis,flag;
};
struct TreeNodeType tree[maxn<<2];
int n,m,rev[maxn],f[maxn],ch[maxn][2],Qes,deep[maxn],id[maxn];
int f_[maxn],top[maxn],tp,sta[maxn],size[maxn],lar[maxn];
int li[maxn],ri[maxn],cnt,E[maxn<<1],V[maxn<<1],head[maxn];
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
void build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r;
    if(l==r){tree[now].dis=deep[id[l]];return;}
    tree[now].mid=l+r>>1;build(now<<1,l,tree[now].mid);
    build(now<<1|1,tree[now].mid+1,r);
    tree[now].dis=max(tree[now<<1].dis,tree[now<<1|1].dis);
}
inline void down(int now)
{
    tree[now<<1].dis+=tree[now].flag;
    tree[now<<1].flag+=tree[now].flag;
    tree[now<<1|1].dis+=tree[now].flag;
    tree[now<<1|1].flag+=tree[now].flag;
    tree[now].flag=0;
}
void add(int now,int l,int r,int x)
{
    if(tree[now].l>=l&&tree[now].r<=r)
    {
        tree[now].dis+=x,tree[now].flag+=x;
        return;
    }
    if(tree[now].flag!=0) down(now);
    if(l<=tree[now].mid) add(now<<1,l,r,x);
    if(r>tree[now].mid) add(now<<1|1,l,r,x);
    tree[now].dis=max(tree[now<<1].dis,tree[now<<1|1].dis);
}
void query(int now,int l,int r)
{
    if(tree[now].l>=l&&tree[now].r<=r)
    {
        Qes=max(Qes,tree[now].dis);
        return;
    }
    if(tree[now].flag!=0) down(now);
    if(l<=tree[now].mid) query(now<<1,l,r);
    if(r>tree[now].mid) query(now<<1|1,l,r);
}
void downdata(int now)
{
    rev[now]^=1,swap(ch[now][1],ch[now][0]);
    if(ch[now][1]) rev[ch[now][1]]^=1;
    if(ch[now][0]) rev[ch[now][0]]^=1;
}
bool isroot(int now)
{
    return (ch[f[now]][1]!=now)&&(ch[f[now]][0]!=now);
}
void rotate(int now)
{
    int fa=f[now],ffa=f[fa],l=(ch[fa][1]==now),r=l^1;
    if(!isroot(fa)) ch[ffa][ch[ffa][1]==fa]=now;
    f[now]=ffa,f[fa]=now,ch[fa][l]=ch[now][r],ch[now][r]=fa;
    if(ch[fa][l]) f[ch[fa][l]]=fa;
}
void splay(int now)
{
    tp=1,sta[tp]=now;int fa,ffa;
    for(int i=now;!isroot(i);i=f[i]) sta[++tp]=f[i];
    while(tp)
    {
        if(rev[sta[tp]]) downdata(sta[tp]);
        tp--;
    }
    while(!isroot(now))
    {
        fa=f[now],ffa=f[fa];
        if(!isroot(fa)) rotate(((ch[ffa][1]==fa)^(ch[fa][1]==now))?fa:now);
        rotate(now);
    }
}
int getson(int now)
{
    while(ch[now][0]) now=ch[now][0];
    return now;
}
void access(int now)
{
    int tmp;
    for(int i=0;now;i=now,now=f[now])
    {
        splay(now);
        tmp=getson(ch[now][1]);
        if(tmp) add(1,li[tmp],ri[tmp],1);
        ch[now][1]=i,tmp=getson(i);
        if(tmp) add(1,li[tmp],ri[tmp],-1);
    }
}
void makeroot(int now)
{
    access(now),splay(now),rev[now]^=1;
}
void link(int x,int y)
{
    makeroot(x),f[x]=y;
}
void edge_add(int u,int v)
{
    E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
}
void dfs1(int now,int fa)
{
    deep[now]=deep[fa]+1,li[now]=++cnt;
    id[cnt]=now,size[now]=1,f_[now]=fa;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now),size[now]+=size[V[i]];
        if(size[lar[now]]<size[V[i]]) lar[now]=V[i];
    }
    ri[now]=cnt;
}
void dfs2(int now,int chain)
{
    top[now]=chain;
    if(f_[now]) f[now]=f_[now];
    if(lar[now]) dfs2(lar[now],chain);
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==lar[now]||V[i]==f_[now]) continue;
        dfs2(V[i],V[i]);
    }
}
int find(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]]) y=f_[top[y]];
        else x=f_[top[x]];
    }
    return deep[x]<deep[y]?x:y;
}
int main()
{
    in(n),in(m);int u,v,op;
    for(int i=1;i<n;i++) in(u),in(v),edge_add(u,v);
    cnt=0,dfs1(1,0),build(1,1,n),dfs2(1,1),makeroot(1);
    while(m--)
    {
        in(op);
        if(op==1) in(u),makeroot(1),access(u);
        if(op==2)
        {
            in(u),in(v);
            int lca=find(u,v);
            Qes=0,query(1,li[u],li[u]),u=Qes;
            Qes=0,query(1,li[v],li[v]),v=Qes;
            if(lca) Qes=0,query(1,li[lca],li[lca]),lca=Qes;
            else lca=0;
            printf("%d\n",u+v-lca*2+1);
        }
        if(op==3) in(u),Qes=0,query(1,li[u],ri[u]),printf("%d\n",Qes);
    }
    return 0;
}
