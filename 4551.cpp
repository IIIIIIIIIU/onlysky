#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 100005
#define maxm maxn<<1
#define maxtree maxn<<2
int n,head[maxn],E[maxm],V[maxm],cnt,m,deep[maxn],li[maxn],ri[maxn];
int val[maxtree],L[maxtree],R[maxtree],mid[maxtree],key[maxtree],tmp1,tmp2;
bool if_[maxtree];
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
void dfs(int now,int fa)
{
    deep[now]=deep[fa]+1,li[now]=++cnt;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs(V[i],now);
    }
    ri[now]=cnt;
}
void build(int now,int l,int r)
{
    L[now]=l,R[now]=r;
    if(l==r)
    {
        if_[now]=true,val[now]=1,key[now]=1;
        return;
    }
    mid[now]=l+r>>1;
    build(now<<1,l,mid[now]);
    build(now<<1|1,mid[now]+1,r);
}
void change(int now,int l,int r,int va,int ke)
{
    if(L[now]>=l&&R[now]<=r)
    {
        if(if_[now])
        {
            if(ke>key[now])key[now]=ke,val[now]=va;
        }
        else if_[now]=true,key[now]=ke,val[now]=va;
        return;
    }
    if(l<=mid[now]) change(now<<1,l,r,va,ke);
    if(r>mid[now]) change(now<<1|1,l,r,va,ke);
}
void query(int now,int to)
{
    if(if_[now]&&key[now]>tmp2) tmp1=val[now],tmp2=key[now];
    if(L[now]==R[now]) return;
    if(to<=mid[now]) query(now<<1,to);
    else query(now<<1|1,to);
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
    cnt=0,dfs(1,0),build(1,1,n);
    char op[5];
    for(int i=1;i<=m;i++)
    {
        scanf("%s",op),in(u);
        if(op[0]=='C') change(1,li[u],ri[u],u,deep[u]);
        else tmp1=1,tmp2=1,query(1,li[u]),printf("%d\n",tmp1);
    }
    return 0;
}
