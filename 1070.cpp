#include <bits/stdc++.h>
using namespace std;
const int maxn=10005;
const int maxm=200005;
const int INF=0x3f3f3f3f;
int head[maxn],cnt=1,s,t,dis[maxn],que[maxm],E[maxm];
int V[maxm],W[maxm],F[maxm],n,m,ci[15][65],pre[maxn],ans;
bool vis[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
inline void edge_add(int u,int v,int w,int f)
{
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,W[cnt]=-w,F[cnt]=0,head[v]=cnt;
}
bool spfa()
{
    for(int i=s;i<=t;i++) vis[i]=false,pre[i]=-1,dis[i]=INF;
    que[0]=s,dis[s]=0,vis[s]=true;int h=0,tail=1,now;
    while(h<tail)
    {
        now=que[h++],vis[now]=false;
        for(int i=head[now];i;i=E[i])
            if(F[i]&&dis[V[i]]>dis[now]+W[i])
            {
                dis[V[i]]=dis[now]+W[i],pre[V[i]]=i;
                if(!vis[V[i]]) que[tail++]=V[i],vis[V[i]]=true;
            }
    }
    return dis[t]!=INF;
}
int main()
{
    in(n),in(m),s=0,t=n*m+m+1;
    for(int i=1;i<=m;i++)
        for(int v=1;v<=n;v++) in(ci[v][i]);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
            for(int e=1;e<=m;e++)
                edge_add((i-1)*m+v,n*m+e,ci[i][e]*v,1);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++) edge_add(s,(i-1)*m+v,0,1);
    for(int i=1;i<=m;i++)
        edge_add(n*m+i,t,0,1);
    while(spfa())
    {
        int now=t,pos=INF;
        while(pre[now]!=-1) pos=min(pos,F[pre[now]]),now=V[pre[now]^1];
        now=t;while(pre[now]!=-1) F[pre[now]]-=pos,F[pre[now]^1]+=pos,now=V[pre[now]^1];
        ans+=dis[t]*pos;
    }
    printf("%.2lf",(double)ans/m);
    return 0;
}
