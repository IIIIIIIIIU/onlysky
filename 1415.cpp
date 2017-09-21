#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const int maxn=1005;
const int maxm=2005;
int n,m,s,t,head[maxn],E[maxm],V[maxm],cnt,pre[maxn];
int dis[maxn],to[maxn][maxn],que[maxn<<4],num[maxn];
real dp[maxn][maxn];
bool vis[maxn],did[maxn][maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void SPFA(int S)
{
    memset(pre,-1,sizeof(pre));
    memset(dis,127/3,sizeof(dis));
    dis[S]=0;int now,h=0,tail=1;que[0]=S;
    while(h<tail)
    {
        now=que[h++],vis[now]=false;
        for(int i=head[now];i;i=E[i])
            if(dis[now]+1<dis[V[i]])
            {
                pre[V[i]]=now,dis[V[i]]=dis[now]+1;
                if(!vis[V[i]]) que[tail++]=V[i],vis[V[i]]=true;
            }
            else if(dis[now]+1==dis[V[i]]&&now<pre[V[i]]) pre[V[i]]=now;
    }
    for(int i=1;i<=n;i++)
    {
        if(pre[i]==S) to[i][S]=S;
        else to[i][S]=pre[pre[i]];
    }
}
real dfs(int S,int T)
{
    if(did[S][T]) return dp[S][T];
    did[S][T]=true;
    if(S==T) return dp[S][T]=0;
    if(to[S][T]==T) return dp[S][T]=1;
    dp[S][T]=dfs(to[S][T],T);
    for(int i=head[T];i;i=E[i]) dp[S][T]+=dfs(to[S][T],V[i]);
    return (dp[S][T]/=num[T])+=1;
}
int main()
{
    in(n),in(m),in(s),in(t);
    int u,v;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v),num[u]+=1,num[v]+=1;
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    for(int i=1;i<=n;i++) SPFA(i),num[i]+=1;
    printf("%.3lf",dfs(s,t));
    return 0;
}
