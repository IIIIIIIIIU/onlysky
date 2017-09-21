#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=100005;
const int maxm=1000005;
int n,m,head[maxn],E[maxm<<1],V[maxm<<1],W[maxm<<1],cnt,size[maxn];
int dis[maxm],tag,f[maxn],now_,Max[maxn],Min[maxn];
bool vis[maxn];
bool did=false;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void dfs(int now)
{
    vis[now]=true;
    Min[now_]=min(dis[now],Min[now_]);
    Max[now_]=max(dis[now],Max[now_]);
    for(int i=head[now];i;i=E[i])
    {
        if(!vis[V[i]]) dis[V[i]]=dis[now]+W[i],dfs(V[i]);
        else tag=gcd(tag,abs(dis[now]+W[i]-dis[V[i]]));
    }
}
int find(int x)
{
    if(x==f[x]) return x;
    return f[x]=find(f[x]);
}
int main()
{
    in(n),in(m);int u,v;
    memset(Min,127/3,sizeof(Min));
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,W[cnt]=1,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,W[cnt]=-1,head[v]=cnt;
        u=find(u),v=find(v);
        if(u!=v) f[u]=v;
    }
    for(int i=1;i<=n;i++) if(!vis[i]) now_=find(i),dfs(i);
    if(tag==0)
    {
        for(int i=1;i<=n;i++)
        {
            if(Min[i]<=Max[i]) tag+=Max[i]-Min[i]+1;
        }
        if(tag>=3) printf("%d 3",tag);
        else printf("-1 -1");
        return 0;
    }
    if(tag<3)
    {
        printf("-1 -1");
        return 0;
    }
    for(int i=3;i<=tag;i++)
    {
        if(tag%i==0)
        {
            cout<<tag<<' '<<i;
            return 0;
        }
    }
    return 0;
}
