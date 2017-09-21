#include <bits/stdc++.h>
using namespace std;
#define maxn 1005
#define maxn 1005
#define mod 31011
struct EdgeType
{
    int u,v,w;
    bool operator<(const EdgeType pos)const
    {
        return w<pos.w;
    }
};
struct EdgeType e[maxn],t[maxn];
int n,m,f[maxn],un[maxn],sta[maxn],back[maxn],top,ans=1;
int cnt,ci[maxn],num,bi[maxn],ai[maxn],li[maxn],ri[maxn];
int sum;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
int findun(int x)
{
    if(un[x]==x) return x;
    return un[x]=findun(un[x]);
}
int find(int x)
{
    if(f[x]==x) return x;
    return find(f[x]);
}
void dfs(int l,int r,int now,int lit)
{
    if(now>lit)
    {
        sum++;
        return;
    }
    int x,y;
    for(int i=l;i<=r;i++)
    {
        x=find(e[i].u),y=find(e[i].v);
        if(x!=y)
        {
            sta[++top]=x,back[top]=f[x];
            f[x]=y,dfs(i+1,r,now+1,lit);
            f[sta[top]]=back[top--];
        }
    }
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=m;i++) in(e[i].u),in(e[i].v),in(e[i].w);
    sort(e+1,e+m+1);int x,y,tmp=0;
    for(int i=1;i<=n;i++) un[i]=i,f[i]=i;
    for(int i=1;i<=m;i++)
    {
        x=findun(e[i].u),y=findun(e[i].v);
        if(x!=y)
        {
            un[x]=y,tmp++;
            ci[++num]=e[i].w;
        }
    }
    if(tmp!=n-1)
    {
        cout<<0;
        return 0;
    }
    for(int i=1;i<=num;i++) bi[i]=ci[i];
    sort(bi+1,bi+num+1),cnt=unique(bi+1,bi+num+1)-bi-1;
    for(int i=1;i<=num;i++)
    {
        ci[i]=lower_bound(bi+1,bi+cnt+1,ci[i])-bi;
        ai[ci[i]]++;
    }
    for(int i=1;i<=m;i++)
    {
        e[i].w=lower_bound(bi+1,bi+cnt+1,e[i].w)-bi;
        ri[e[i].w]=max(ri[e[i].w],i);
        if(!li[e[i].w]) li[e[i].w]=i;
    }
    for(int i=1;i<=cnt;i++)
    {
        sum=0,top=0;
        dfs(li[i],ri[i],1,ai[i]);
        (ans*=sum%mod)%=mod;
        for(int v=li[i];v<=ri[i];v++)
        {
            x=find(e[v].u),y=find(e[v].v);
            if(x!=y) f[x]=y;
        }
    }
    cout<<ans;
    return 0;
}
