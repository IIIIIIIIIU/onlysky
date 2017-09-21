#include <bits/stdc++.h>
using namespace std;
const int maxn=6005;
const int maxm=60005;
const int INF=0x3f3f3f3f;
int n,m,head[maxn],s,t,E[maxm],V[maxm],W[maxm],F[maxm],win[maxn],lose[maxn];
int cnt=1,C[maxn],D[maxn],A[maxn],B[maxn],ans,que[maxm<<3],dis[maxn],pre[maxn];
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
    int h=0,tail=1,now=0;que[h]=s,dis[s]=0,vis[s]=1;
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
    in(n),in(m),s=0,t=n+m+1;
    for(int i=1;i<=n;i++) in(win[i]),in(lose[i]),in(C[i]),in(D[i]);
    for(int i=1;i<=m;i++) in(A[i]),in(B[i]),lose[A[i]]++,lose[B[i]]++;
    for(int i=1;i<=n;i++) ans+=C[i]*win[i]*win[i]+D[i]*lose[i]*lose[i];
    for(int i=1;i<=m;i++)
    {
        edge_add(s,i,0,1);
        edge_add(i,A[i]+m,0,1);
        edge_add(A[i]+m,t,C[A[i]]*(2*win[A[i]]+1)-D[A[i]]*(2*lose[A[i]]-1),1);
        win[A[i]]++,lose[A[i]]--;
        edge_add(i,B[i]+m,0,1);
        edge_add(B[i]+m,t,C[B[i]]*(2*win[B[i]]+1)-D[B[i]]*(2*lose[B[i]]-1),1);
        win[B[i]]++,lose[B[i]]--;
    }
    while(spfa())
    {
        int now=t,pos=INF;
        while(pre[now]!=-1) pos=min(F[pre[now]],pos),now=V[pre[now]^1];now=t;
        while(pre[now]!=-1) F[pre[now]]-=pos,F[pre[now]^1]+=pos,now=V[pre[now]^1];
        ans+=pos*dis[t];
    }
    cout<<ans;
    return 0;
}
