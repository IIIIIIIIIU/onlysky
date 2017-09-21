#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int INF=0x3f3f3f3f;
int n,fa,ta,fb,tb,ff,head[maxn],F[maxn],V[maxn],E[maxn],cnt=1,s,t;
int que[maxn<<3],pre[maxn],ci[maxn],W[maxn],ans,dis[maxn];
bool vis[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
inline void edge_add(int u,int v,int w,int f)
{
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,W[cnt]=-w,F[cnt]=0,head[v]=cnt;
}
bool spfa()
{
    for(int i=s;i<=t;i++) dis[i]=INF,pre[i]=-1;
    dis[s]=0,que[0]=s;int h=0,tail=1,now;
    while(h<tail)
    {
        now=que[h++],vis[now]=false;
        for(int i=head[now];i;i=E[i])
            if(F[i]&&dis[now]+W[i]<dis[V[i]])
            {
                dis[V[i]]=dis[now]+W[i],pre[V[i]]=i;
                if(!vis[V[i]]) vis[V[i]]=true,que[tail++]=V[i];
            }
    }
    return dis[t]!=INF;
}
int main()
{
    in(n),in(ta),in(tb),in(ff),in(fa),in(fb),s=0,t=n*3+1;
    for(int i=1;i<=n;i++)
    {
        in(ci[i]);
        edge_add(s,i,ff,INF);
        edge_add(i,i+n,0,ci[i]);
        edge_add(i+n,t,0,INF);
        edge_add(s,i+n+n,0,ci[i]);
        if(i+ta+1<=n) edge_add(i+n+n,i+ta+1,fa,INF);
        if(i+tb+1<=n) edge_add(i+n+n,i+tb+1,fb,INF);
        if(i<n) edge_add(i+n+n,i+1+n+n,0,INF);
    }
    while(spfa())
    {
        int now=t,pos=INF;
        while(pre[now]!=-1) pos=min(pos,F[pre[now]]),now=V[pre[now]^1];now=t;
        while(pre[now]!=-1) F[pre[now]]-=pos,F[pre[now]^1]+=pos,now=V[pre[now]^1];
        ans+=dis[t]*pos;
    }
    cout<<ans;
    return 0;
}
