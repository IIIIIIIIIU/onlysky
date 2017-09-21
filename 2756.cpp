#include <bits/stdc++.h>
using namespace std;
#define INF 1e16
#define maxn 40005
#define ll long long
const ll dx[5]={0,-1,0,1,0};
const ll dy[5]={0,0,1,0,-1};
ll ai[45][45],id[45][45],suma,sumb,cnta,cntb,que[maxn],Max,ans;
ll deep[maxn],E[maxn],V[maxn],F[maxn],cnt,head[maxn],s,t,cntid;
ll n,m;
bool col[45][45];
inline void in(ll &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
inline void edge_add(ll u,ll v,ll f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
bool bfs()
{
    for(ll i=s;i<=t;i++) deep[i]=-1;
    deep[s]=0,que[0]=s;ll h=0,tail=1,now;
    while(h<tail)
    {
        now=que[h++];
        for(ll i=head[now];i;i=E[i])
            if(F[i]&&deep[V[i]]==-1)
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==t) return true;
                que[tail++]=V[i];
            }
    }
    return false;
}
ll flowing(ll now,ll flow)
{
    if(now==t||flow<=0) return flow;
    ll oldflow=0,pos;
    for(ll i=head[now];i;i=E[i])
    {
        if(!F[i]||deep[V[i]]!=deep[now]+1) continue;
        pos=flowing(V[i],min(flow,F[i]));
        F[i]-=pos,F[i^1]+=pos,oldflow+=pos,flow-=pos;
        if(!flow) return oldflow;
    }
    if(!oldflow) deep[now]=-1;
    return oldflow;
}
bool check(ll x)
{
    for(ll i=s;i<=t;i++) head[i]=0;cnt=1;
    for(ll i=1;i<=n;i++)
        for(ll v=1;v<=m;v++)
            if(col[i][v])
            {
                edge_add(s,id[i][v],x-ai[i][v]);
                for(ll e=1;e<=4;e++)
                    if(i+dx[e]>0&&i+dx[e]<=n&&v+dy[e]>0&&v+dy[e]<=m) edge_add(id[i][v],id[i+dx[e]][v+dy[e]],INF);
            }
            else edge_add(id[i][v],t,x-ai[i][v]);
    ll res=0;
    while(bfs()) res+=flowing(s,INF);
    return res==(x*cnta-suma);
}
int main()
{
    ll T;in(T);
    while(T--)
    {
        in(n),in(m),suma=0,sumb=0,cnta=0,cntb=0,cntid=0,Max=0;
        for(ll i=1;i<=n;i++)
            for(ll v=1;v<=m;v++)
            {
                in(ai[i][v]),col[i][v]=(i+v)%2;
                if(col[i][v]) suma+=ai[i][v],cnta++;
                else sumb+=ai[i][v],cntb++;
                id[i][v]=++cntid,Max=max(Max,ai[i][v]);
            }
        ans=-1,s=0,t=cntid+1;
        if(cnta!=cntb)
        {
            if((suma-sumb)%(cnta-cntb)==0)
            {
                ll x=(suma-sumb)/(cnta-cntb);
                if(x>=Max) if(check(x)) ans=x*cnta-suma;
            }
        }
        else
        {
            if(suma==sumb)
            {
                ll l=Max,r=INF,mid;
                while(l<=r)
                {
                    mid=l+r>>1;
                    if(check(mid)) r=mid-1,ans=mid;
                    else l=mid+1;
                }
                if(ans!=-1) ans=ans*cnta-suma;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
