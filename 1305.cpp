#include <bits/stdc++.h>
using namespace std;
const int maxn=20005,INF=0x3f3f3f3f;
int n,k,s,t,head[maxn],E[maxn],V[maxn],F[maxn],cnt;
int deep[maxn],que[maxn];
char ch[105][105];
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1;
    int h=0,tail=1,now;deep[s]=0,que[h]=s;
    while(h<tail)
        for(int i=head[now=que[h++]];i;i=E[i])
            if(F[i]&&deep[V[i]]<0)
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
            F[i]-=tmp,F[i^1]+=tmp,oldflow+=tmp,flow-=tmp;
            if(!flow) return oldflow;
        }
    if(flow) deep[now]=-1;
    return oldflow;
}
bool check(int lit)
{
    s=0,t=n*4+1,cnt=1;
    for(int i=s;i<=t;i++) head[i]=0;
    for(int i=1;i<=n;i++)
    {
        edge_add(s,i,lit);
        edge_add(i+n+n,t,lit);
        edge_add(i,i+n,k);
        edge_add(i+n+n+n,i+n+n,k);
    }
    for(int i=1;i<=n;i++)
        for(int v=1;v<=n;v++)
            if(ch[i][v]=='Y') edge_add(i,v+n+n,1);
            else edge_add(i+n,v+n+n+n,1);
    int res=0;
    while(bfs()) res+=flowing(s,INF);
    return res==lit*n;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%s",ch[i]+1);
    int l=0,r=n,mid,ans=0;
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}
