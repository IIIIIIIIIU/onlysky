#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=2005;
const int maxm=20005;
const int INF=0x3f3f3f3f;
int n,m,s,t,deep[maxn],head[maxn],E[maxm],V[maxm],F[maxm],ans;
int cnt=1,que[maxn],p1[maxn],p2[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1;
    int h=0,tail=1,now;que[0]=s,deep[s]=0;
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
    int oldflow=0,pos;
    for(int i=head[now];i;i=E[i])
        if(deep[V[i]]==deep[now]+1&&F[i])
        {
            pos=flowing(V[i],min(F[i],flow));
            F[i]-=pos,F[i^1]+=pos,flow-=pos,oldflow+=pos;
            if(!flow) return oldflow;
        }
    if(flow) deep[now]=-1;
    return oldflow;
}
bool check(int lit)
{
    s=0,t=lit+n+1,cnt=1;
    memset(head,0,sizeof(head));
    for(int i=1;i<=n;i++) edge_add(s,i,1);
    for(int i=1;i<=lit;i++)
    {
        edge_add(p1[i],i+n,1);
        edge_add(p2[i],i+n,1);
        edge_add(i+n,t,1);
    }
    int pos=0;
    while(bfs()) pos+=flowing(s,INF);
    if(pos==lit) return true;
    return false;
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=m;i++) in(p1[i]),in(p2[i]),p1[i]++,p2[i]++;
    int l=0,r=m,mid;ans=0;
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) l=mid+1,ans=mid;
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}
