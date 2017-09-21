#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 800005
int n,head[maxn],E[maxn<<1],V[maxn<<1],f[maxn],cnt,ans,m;
int out[maxn],path[maxn];
bool vis[maxn],did[maxn],has[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
int find(int x)
{
    if(x==f[x]) return f[x];
    return f[x]=find(f[x]);
}
int main()
{
    in(n),in(m);int u,v;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    in(m);
    for(int i=m;i>=1;i--) in(path[i]),did[path[i]]=true;
    for(int i=0;i<n;i++) f[i]=i;
    int x,y;
    for(int i=0;i<n;i++)
    {
        if(did[i]) continue;
        for(int v=head[i];v;v=E[v])
        {
            if(did[V[v]]) continue;
            x=find(i),y=find(V[v]);
            if(x!=y) f[x]=y;
        }
    }
    for(int i=0;i<n;i++)
    {
        f[i]=find(f[i]);
        if(did[i]) continue;
        if(!vis[f[i]]) ans++,vis[f[i]]=true;
    }
    int tmp;
    for(int i=1;i<=m;i++)
    {
        out[i]=ans;
        did[path[i]]=false;
        int v,now=path[i];
        v=head[now];bool pos=true;
        for(;v;v=E[v])
        {
            if(did[V[v]]) continue;
            x=find(now),y=find(V[v]);
            f[x]=y,pos=false;
            break;
        }
        for(;v;v=E[v])
        {
            if(did[V[v]]) continue;
            x=find(now),y=find(V[v]);
            if(x!=y) ans--,f[x]=y;
        }
        if(pos) ans++;
        tmp=ans;
    }
    printf("%d\n",ans);
    for(int i=m;i>=1;i--) printf("%d\n",out[i]);
    return 0;
}
