#include <bits/stdc++.h>
using namespace std;
#define maxn 205
#define maxm 6005
#define INF 0x7fffffff
int n,m,q,head[maxn],E[maxm],V[maxm],F[maxm],cnt;
int que[maxn],ans[maxn][maxn],s,t,ai[maxn],bi[maxn];
int deep[maxn];
bool has[maxn];
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
bool bfs()
{
    for(int i=1;i<=n;i++) deep[i]=-1;
    deep[s]=0,que[0]=s;int h=0,tail=1,now;
    while(h<tail)
    {
        now=que[h++];
        for(int i=head[now];i;i=E[i])
            if(F[i]&&deep[V[i]]<0)
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==t) return true;
                que[tail++]=V[i];
            }
    }
    return false;
}
int flowing(int now,int flow)
{
    if(now==t||flow<=0) return flow;
    int oldflow=0,pos;
    for(int i=head[now];i;i=E[i])
        if(F[i]&&deep[V[i]]==deep[now]+1)
        {
            pos=flowing(V[i],min(flow,F[i]));
            F[i]-=pos,F[i^1]+=pos,oldflow+=pos,flow-=pos;
            if(!flow) return oldflow;
        }
    if(!oldflow) deep[now]=-1;
    return oldflow;
}
void dfs(int now)
{
    has[now]=true;
    for(int i=head[now];i;i=E[i]) if(!has[V[i]]&&F[i]) dfs(V[i]);
}
void get(int l,int r)
{
    if(l==r) return;
    for(int i=2;i<=cnt;i+=2) F[i]=F[i^1]=(F[i]+F[i^1])>>1;
    s=ai[l],t=ai[r];int pos=0;
    while(bfs()) pos+=flowing(s,INF);
    memset(has,0,sizeof(has)),dfs(s);
    for(int i=1;i<=n;i++)
        if(has[i]) for(int v=1;v<=n;v++)
            if(!has[v]) ans[v][i]=ans[i][v]=min(ans[i][v],pos);
    int L=l,R=r;
    for(int i=l;i<=r;i++)
        if(has[ai[i]]) bi[L++]=ai[i];
        else bi[R--]=ai[i];
    for(int i=l;i<=r;i++) ai[i]=bi[i];
    get(l,L-1),get(R+1,r);
}
int main()
{
    int T;in(T);
    while(T--)
    {
        in(n),in(m),cnt=1;int u,v,w;
        for(int i=1;i<=n;i++)
            for(int e=1;e<=n;e++) ans[i][e]=INF;
        for(int i=1;i<=n;i++) head[i]=0,ai[i]=i;
        while(m--)
        {
            in(u),in(v),in(w);
            E[++cnt]=head[u],V[cnt]=v,F[cnt]=w,head[u]=cnt;
            E[++cnt]=head[v],V[cnt]=u,F[cnt]=w,head[v]=cnt;
        }
        get(1,n),in(q);
        while(q--)
        {
            in(u),w=0;
            for(int i=1;i<=n;i++)
                for(int e=i+1;e<=n;e++) if(ans[i][e]<=u) w++;
            printf("%d\n",w);
        }
        if(T) printf("\n");
    }
    return 0;
}
