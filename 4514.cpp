#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define ll long long
#define INF 0x7ffffffffff
 
ll n,prime[1000050],num_prime=0,ai[205],bi[205],ci[205];
ll s,t,head[205],E[100005],V[100005],W[100005],F[100005];
ll cnt=1,pre[205],que[200005],dis[205];
 
bool if_prime[1000050],d1iv[205],if_[205];
 
inline void in(ll &now)
{
    ll if_z=1;now=0;
    char Cget=getchar();
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
 
void euler(ll limit)
{
    for(ll i=2;i<=limit;i++)
    {
        if(!if_prime[i]) prime[++num_prime]=i;
        for(ll j=1;prime[j]*i<=limit&&j<=num_prime;j++)
        {
            if_prime[i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
}
 
inline bool cut(ll op)
{
    ll res=0,now=0;
    while(op!=1&&now<10500)
    {
        now++;
        while(!(op%prime[now])) op/=prime[now],res++;
    }
    return res&1;
}
 
inline void edge_add(ll u,ll v,ll w,ll f)
{
    E[++cnt]=head[u],head[u]=cnt,W[cnt]=w,F[cnt]=f,V[cnt]=v;
    E[++cnt]=head[v],head[v]=cnt,W[cnt]=-w,F[cnt]=0,V[cnt]=u;
}
 
inline bool spfa()
{
    for(ll i=s;i<=t;i++) dis[i]=-INF,if_[i]=false,pre[i]=-1;
    ll h=0,tail=1;que[0]=s,if_[s]=true,dis[s]=0;
    while(h<tail)
    {
        ll now=que[h++];if_[now]=false;
        for(ll i=head[now];i;i=E[i])
        {
            if(F[i]>0&&dis[V[i]]<dis[now]+W[i])
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
    return dis[t]!=-INF;
}
 
int main()
{
    in(n);euler(1000040),t=n+1;
    for(ll i=1;i<=n;i++) in(ai[i]);
    for(ll i=1;i<=n;i++) in(bi[i]);
    for(ll i=1;i<=n;i++) in(ci[i]);
    for(ll i=1;i<=n;i++)
    {
        if(cut(ai[i]))
        {
            d1iv[i]=true;
            edge_add(i,t,0,bi[i]);
        }
        else edge_add(s,i,0,bi[i]);
    }
    for(ll i=1;i<=n;i++)
    {
        if(!d1iv[i])
        {
            for(ll j=1;j<=n;j++)
            {
                if(d1iv[j])
                {
                    ll a=max(ai[i],ai[j]),b=min(ai[i],ai[j]);
                    if(a==b||a%b) continue;
                    if(!if_prime[a/b]) edge_add(i,j,ci[i]*ci[j],INF);
                }
            }
        }
    }
    ll ans=0,cii=0;
    while(spfa())
    {
        ll now=t,pos=INF;
        while(pre[now]!=-1)
        {
            pos=min(pos,F[pre[now]]);
            now=V[pre[now]^1];
        }
        now=t;
        while(pre[now]!=-1)
        {
            F[pre[now]]-=pos;
            F[pre[now]^1]+=pos;
            now=V[pre[now]^1];
        }
        if(cii+dis[t]*pos<0)
        {
            ans+=cii/(-dis[t]);
            break;
        }
        ans+=pos,cii+=dis[t]*pos;
    }
    cout<<ans;
    return 0;
}
