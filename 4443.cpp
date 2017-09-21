#include <bits/stdc++.h>
using namespace std;
#define maxn 300
#define maxque 666666
#define INF 0x3f3f3f3f
int n,m,k,ai[maxn][maxn],E[maxque],V[maxque],head[maxn*maxn*2],cnt,s,t;
int F[maxque],deep[maxn*maxn*2],que[maxque<<1];
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
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
inline bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1;
    int h=0,tail=1,now;deep[s]=0,que[h]=s;
    while(h<tail)
    {
        now=que[h++];
        for(int i=head[now];i;i=E[i])
        {
            if(F[i]&&deep[V[i]]<0)
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==t) return true;
                que[tail++]=V[i];
            }
        }
    }
    return false;
}
inline int flowing(int now,int flow)
{
    if(now==t||flow<=0) return flow;
    int oldflow=0;
    for(int i=head[now];i;i=E[i])
    {
        if(!F[i]||deep[V[i]]!=deep[now]+1) continue;
        int pos=flowing(V[i],min(flow,F[i]));
        F[i]-=pos,flow-=pos,oldflow+=pos,F[i^1]+=pos;
        if(!flow) return oldflow;
    }
    if(!oldflow) deep[now]=-1;
    return oldflow;
}
bool check(int lit)
{
    cnt=1,s=0,t=n+m+maxn*maxn+1;
    for(int i=s;i<=t;i++) head[i]=0;
    for(int i=1;i<=n;i++)
    {
        edge_add(s,i,1);
        for(int v=1;v<=m;v++)
        {
            if(ai[i][v]<=lit)
            {
                edge_add(i,i*m+v-m,INF);
                edge_add(i*m+v-m,v+n,INF);
            }
        }
    }
    for(int i=1;i<=m;i++) edge_add(i+n,t,1);
    int pos=0;
    while(bfs()) pos+=flowing(s,INF);
    return pos>=k;
}
int main()
{
    in(n),in(m),in(k),k=n-k+1;
    int l=1,r=0,mid,ans=0;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++) in(ai[i][v]),r=max(ai[i][v],r);
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;
    return 0;
}
