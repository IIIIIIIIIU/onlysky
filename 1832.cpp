#include <bits/stdc++.h>
using namespace std;
const int maxn=500005;
int deep[maxn],f[maxn],head[maxn],E[maxn<<1],V[maxn<<1],cnt,n,m;
int top[maxn],lar[maxn],size[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void dfs1(int now,int fa)
{
    f[now]=fa,deep[now]=deep[fa]+1,size[now]=1;
    for(int i=head[now];i;i=E[i])
        if(V[i]!=fa)
        {
            dfs1(V[i],now),size[now]+=size[V[i]];
            if(size[V[i]]>size[lar[now]]) lar[now]=V[i];
        }
}
void dfs2(int now,int chain)
{
    top[now]=chain;
    if(lar[now]) dfs2(lar[now],chain);
    for(int i=head[now];i;i=E[i])
        if(V[i]!=f[now]&&V[i]!=lar[now])
            dfs2(V[i],V[i]);
}
inline int get(int x,int y)
{
    while(top[x]!=top[y])
        if(deep[top[x]]>deep[top[y]]) x=f[top[x]];
        else y=f[top[y]];
    return deep[x]<deep[y]?x:y;
}
int main()
{
    in(n),in(m);
    int u,v;
    for(int i=1;i<n;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    dfs1(1,0),dfs2(1,1);
    int p1,p2,p3,l12,l13,l23;
    while(m--)
    {
        in(p1),in(p2),in(p3);
        l12=get(p1,p2),l13=get(p1,p3),l23=get(p2,p3);
        if(l12==l13) printf("%d %d\n",l23,deep[p2]+deep[p3]+deep[p1]-deep[l23]-deep[l12]*2);
        else if(l12==l23) printf("%d %d\n",l13,deep[p1]+deep[p2]+deep[p3]-deep[l13]-deep[l12]*2);
        else printf("%d %d\n",l12,deep[p1]+deep[p2]+deep[p3]-deep[l12]-deep[l13]*2);
    }
    return 0;
}
