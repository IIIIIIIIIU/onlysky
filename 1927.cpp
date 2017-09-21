#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 805
#define maxm 7000000
#define INF 0x7fffffff
 
int dis[maxn<<1],cnt=1,s,t,que[maxm],pre[maxn<<1],ans;
int n,m,head[maxn<<1],E[maxm],V[maxm],F[maxm],W[maxm];
 
bool if_[maxn<<1];
 
inline void in(int &now)
{
    register int if_z=1;now=0;
    register char Cget=getchar();
    while(Cget>'9'||Cget<'0')
    {
        if(Cget=='-') if_z=-1;
        Cget=getchar();
    }
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
}
 
bool spfa()
{
    for(int i=s;i<=t;i++) dis[i]=INF,pre[i]=-1,if_[i]=false;
    int h=0,tail=1;dis[s]=0,if_[s]=true,que[0]=s;
    while(h<tail)
    {
        int now=que[h++];if_[now]=false;
        for(int i=head[now];i;i=E[i])
        {
            if(F[i]>0&&dis[V[i]]>dis[now]+W[i])
            {
                pre[V[i]]=i;
                dis[V[i]]=dis[now]+W[i];
                if(!if_[V[i]])
                {
                    if_[V[i]]=true;
                    que[tail++]=V[i];
                }
            }
        }
    }
    return dis[t]!=INF;
}
 
int main()
{
    in(n),in(m);
    t=n*2+1;int u,v,pos;
    for(int i=1;i<=n;i++)
    {
        in(pos);
        E[++cnt]=head[s],V[cnt]=i,F[cnt]=1,W[cnt]=0,head[s]=cnt;
        E[++cnt]=head[i],V[cnt]=s,F[cnt]=0,W[cnt]=0,head[i]=cnt;
        E[++cnt]=head[s],V[cnt]=i+n,F[cnt]=1,W[cnt]=pos,head[s]=cnt;
        E[++cnt]=head[i+n],V[cnt]=s,F[cnt]=0,W[cnt]=-pos,head[i+n]=cnt;
        E[++cnt]=head[i+n],V[cnt]=t,F[cnt]=1,W[cnt]=0,head[i+n]=cnt;
        E[++cnt]=head[t],V[cnt]=i+n,F[cnt]=0,W[cnt]=0,head[t]=cnt;
    }
    while(m--)
    {
        in(u),in(v),in(pos);
        if(u>v) swap(u,v);
        E[++cnt]=head[u],V[cnt]=v+n,F[cnt]=1,W[cnt]=pos,head[u]=cnt;
        E[++cnt]=head[v+n],V[cnt]=u,F[cnt]=0,W[cnt]=-pos,head[v+n]=cnt;
    }
    while(spfa())
    {
        int now=t;pos=INF;
        while(pre[now]!=-1) pos=min(pos,F[pre[now]]),now=V[pre[now]^1];now=t;
        while(pre[now]!=-1) F[pre[now]]-=pos,F[pre[now]^1]+=pos,now=V[pre[now]^1];
        ans+=pos*dis[t];
    }
    cout<<ans;
    return 0;
}
