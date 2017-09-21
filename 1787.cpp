#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 500005
int head[maxn],E[maxn<<1],V[maxn<<1],deep[maxn];
int f[maxn],top[maxn],lar[maxn],size[maxn],cnt;
int n,m;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void dfs1(int now,int fa)
{
    f[now]=fa,deep[now]=deep[fa]+1,size[now]=1;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now),size[now]+=size[V[i]];
        if(size[lar[now]]<=size[V[i]]) lar[now]=V[i];
    }
}
void dfs2(int now,int chain)
{
    top[now]=chain;
    if(lar[now]) dfs2(lar[now],chain);
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==f[now]||V[i]==lar[now]) continue;
        dfs2(V[i],V[i]);
    }
}
int get(int x,int y)
{
    while(top[x]!=top[y])
        if(deep[top[x]]>deep[top[y]]) x=f[top[x]];
        else y=f[top[y]];
    if(deep[x]>deep[y]) swap(x,y);
    return x;
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
    dfs1(1,0),dfs2(1,1);
    int p1,p2,p3,l1,l2,l3;
    while(m--)
    {
        in(p1),in(p2),in(p3);
        l1=get(p1,p2),l2=get(p2,p3),l3=get(p1,p3);
        if(deep[l1]>=deep[l2]&&deep[l1]>=deep[l3])
        {
            printf("%d %d\n",l1,deep[p1]+deep[p2]-deep[l1]+deep[p3]-deep[l2]*2);
            continue;
        }
        if(deep[l2]>=deep[l1]&&deep[l2]>=deep[l3])
        {
            printf("%d %d\n",l2,deep[p2]+deep[p3]+deep[p1]-deep[l2]-deep[l1]*2);
            continue;
        }
        printf("%d %d\n",l3,deep[p1]+deep[p2]+deep[p3]-deep[l3]-deep[l1]*2);
    }
    return 0;
}
