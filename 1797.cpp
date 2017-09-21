#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=4005,maxm=120005,INF=0x3f3f3f3f;
int n,m,dfn[maxn],low[maxn],sta[maxn],bel[maxn],col,tag,top;
int deep[maxn],head[maxn],E[maxm],V[maxm],F[maxm],cnt=1,que[maxn],s,t;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
bool bfs()
{
    for(int i=1;i<=n;i++) deep[i]=-1;
    deep[s]=0,que[0]=s;int h=0,tail=1,now;
    while(h<tail)
        for(int i=head[now=que[h++]];i;i=E[i])
            if(deep[V[i]]<0&&F[i])
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==t) return true;
                que[tail++]=V[i];
            }
    return false;
}
int flowing(int now,int flow)
{
    if(now==t||flow<=0) return flow;
    int oldflow=0,tmp;
    for(int i=head[now];i;i=E[i])
        if(F[i]&&deep[V[i]]==deep[now]+1)
        {
            tmp=flowing(V[i],min(F[i],flow));
            F[i]-=tmp,F[i^1]+=tmp,flow-=tmp,oldflow+=tmp;
            if(!flow) return oldflow;
        }
    if(flow) deep[now]=-1;
    return oldflow;
}
void dfs(int now)
{
    dfn[now]=low[now]=++tag,sta[++top]=now;
    for(int i=head[now];i;i=E[i])
        if(!bel[V[i]]&&F[i])
            if(dfn[V[i]]) low[now]=min(low[now],dfn[V[i]]);
            else dfs(V[i]),low[now]=min(low[V[i]],low[now]);
    if(dfn[now]==low[now])
    {
        col++;
        while(sta[top]!=now) bel[sta[top--]]=col;
        bel[now]=col,top--;
    }
}
int main()
{
    in(n),in(m),in(s),in(t);int u,v,f;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v),in(f);
        E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
    }
    while(bfs()) flowing(s,INF);
    for(int i=1;i<=n;i++)
        if(!dfn[i]) dfs(i);
    for(int i=2;i<=m*2;i+=2)
        if(F[i]) puts("0 0");
        else printf("%d %d\n",bel[V[i^1]]!=bel[V[i]],bel[V[i^1]]!=bel[V[i]]&&
                    bel[V[i^1]]==bel[s]&&bel[V[i]]==bel[t]);
    return 0;
}
