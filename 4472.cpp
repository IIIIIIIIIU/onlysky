#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
typedef long long ll;
 
const ll maxn=1e5+5;
 
ll n,val[maxn],ti[maxn],head[maxn],E[maxn<<1],V[maxn<<1];
ll cnt,seq[maxn],Uni[maxn];
 
inline void read(ll &now)
{
    char Cget;
    now=0;
    ll if_z=1;
    while(!isdigit(Cget=getchar()))
        if(Cget=='-')
            if_z=-1;
    while(isdigit(Cget))
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
}
 
inline bool cmp(const ll &x,const ll &y)
{
    return val[x]>val[y];
}
 
void dfs(ll now,ll fa)
{
    ll num=0;
    for(ll i=head[now];i!=0;i=E[i])
        if(V[i]!=fa)
            dfs(V[i],now);
    for(ll i=head[now];i!=0;i=E[i])
        if(V[i]!=fa)
            seq[++num]=V[i];
    if(!num||!(ti[now]-1))
        return ;
    std::sort(seq+1,seq+num+1,cmp);
    ll lit=std::min(ti[now]-1,num);
    int t=0;
    for(ll i=1;i<=lit;i++)
    {
        if(val[seq[i]]==0)
            Uni[now]=true;
        if(val[seq[i]]<0)
            return;
        val[now]+=val[seq[i]];
        Uni[now]|=Uni[seq[i]];
        t++;
    }
    if(lit&&lit<num&&val[seq[lit]]==val[seq[lit+1]])
        Uni[now]=true;
    if(seq[t+1]&&val[seq[t+1]]==0)
        Uni[now]=true;
}
 
int main()
{
    read(n);
    for(ll i=2;i<=n;i++)
        read(val[i]);
    for(ll i=2;i<=n;i++)
        read(ti[i]);
    ti[1]=n;
    for(ll i=1,u,v;i<n;i++)
    {
        read(u);
        read(v);
        E[++cnt]=head[u];
        V[cnt]=v;
        head[u]=cnt;
        E[++cnt]=head[v];
        V[cnt]=u;
        head[v]=cnt;
    }
    dfs(1,0);
    std::cout<<val[1]<<std::endl;
    if(Uni[1])
        puts("solution is not unique");
    else
        puts("solution is unique");
    return 0;
}
