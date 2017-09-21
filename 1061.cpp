#include <bits/stdc++.h>
using namespace std;
const int maxn=2005;
const int maxm=20005;
const int maxedge=300005;
const int INF=0x7fffffff;
int s,t,n,m,num[maxn],cnt=1,pre[maxn],dis[maxn],ans,que[maxedge];
int head[maxn],E[maxedge],V[maxedge],W[maxedge],F[maxedge];
bool vis[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void edge_add(int u,int v,int w,int f)
{
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,W[cnt]=-w,F[cnt]=0,head[v]=cnt;
}
bool spfa()
{
    for(int i=s;i<=t;i++) dis[i]=INF,pre[i]=-1,vis[i]=false;
    dis[s]=0,que[0]=s,vis[s]=true;int h=0,tail=1,now;
    while(h<tail)
    {
        now=que[h++],vis[now]=false;
        for(int i=head[now];i;i=E[i])
            if(F[i]&&dis[V[i]]>dis[now]+W[i])
            {
                dis[V[i]]=dis[now]+W[i],pre[V[i]]=i;
                if(!vis[V[i]]) vis[V[i]]=true,que[tail++]=V[i];
            }
    }
    return dis[t]!=INF;
}
int main()
{
    in(n),in(m),s=0,t=n+2;
    for(int i=1;i<=n;i++) in(num[i]);
    for(int i=1;i<=n+1;i++)
        if(num[i]-num[i-1]>=0) edge_add(s,i,0,num[i]-num[i-1]);
        else edge_add(i,t,0,num[i-1]-num[i]);
    int si,ti,ci;
    for(int i=1;i<=m;i++)
    {
        in(si),in(ti),in(ci);
        edge_add(si,ti+1,ci,INF);
    }
    for(int i=n+1;i>1;i--) edge_add(i,i-1,0,INF);
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
