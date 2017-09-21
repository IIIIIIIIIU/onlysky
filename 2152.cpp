#include <bits/stdc++.h>
using namespace std;
#define maxn 20005
#define INF 0x7fffffff
int n,m,sum,num,cnt,ans,L,root,t;
int head[maxn],vis[maxn],d[maxn];
int size[maxn],lar[maxn],flag[4];
int E[maxn<<1],V[maxn<<1],W[maxn<<1];
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
inline void edge_add(int u,int v,int w)
{
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
}
inline int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}
void GetRoot(int now,int fa)
{
    size[now]=1,lar[now]=0;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa||vis[V[i]]) continue;
        GetRoot(V[i],now);
        size[now]+=size[V[i]];
        lar[now]=max(lar[now],size[V[i]]);
    }
    lar[now]=max(lar[now],sum-size[now]);
    if(lar[now]<lar[root]) root=now;
}
void GetDeep(int now,int fa)
{
    flag[d[now]]++;
    for(int i=head[now];i;i=E[i])
    {
        if(vis[V[i]]||V[i]==fa)continue;
        d[V[i]]=(d[now]+W[i])%3;
        GetDeep(V[i],now);
    }
}
int cal(int now,int dis)
{
    d[now]=dis,flag[0]=flag[1]=flag[2]=0;
    GetDeep(now,0);
    return flag[1]*flag[2]*2+flag[0]*flag[0];
}
void work(int now)
{
    ans+=cal(now,0),vis[now]=1;
    for(int i=head[now];i;i=E[i])
    {
        if(vis[V[i]]) continue;
        ans-=cal(V[i],W[i]);
        root=0,sum=size[V[i]];
        GetRoot(V[i],0),work(root);
    }
}
int main()
{
    in(n);int u,v,w;
    for(int i=1;i<n;i++)
    {
        in(u),in(v),in(w);
        edge_add(u,v,w%3);
    }
    sum=n,lar[0]=n+1;
    GetRoot(1,0),work(root);
    t=gcd(ans,n*n);
    printf("%d/%d\n",ans/t,n*n/t);
    return 0;
}
