#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
struct EdgeType
{
    int u,v,w;
    bool operator<(const EdgeType &pos)const
    {
        return w<pos.w;
    }
};
struct EdgeType e1[maxn],e2[maxn];
int head[maxn],E[maxn],V[maxn],cnt,n,m,k,f[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int find(int x)
{
    if(f[x]==x) return f[x];
    return f[x]=find(f[x]);
}
bool check(int lit)
{
    for(int i=1;i<=n;i++) f[i]=i;
    int cnt=0,x,y;
    for(int i=1;i<=m;i++)
    {
        if(e1[i].w>lit) break;
        x=find(e1[i].u),y=find(e1[i].v);
        if(x!=y) f[x]=y,cnt++;
    }
    if(cnt<k) return false;
    for(int i=1;i<=m;i++)
    {
        if(e2[i].w>lit) break;
        x=find(e2[i].u),y=find(e2[i].v);
        if(x!=y) f[x]=y,cnt++;
    }
    return cnt==n-1;
}
int main()
{
    in(n),in(k),in(m);
    for(int i=1;i<m;i++)
    {
        in(e1[i].u),in(e1[i].v),in(e1[i].w);
        e2[i]=e1[i],in(e2[i].w);
    }
    sort(e1+1,e1+m+1);
    sort(e2+1,e2+m+1);
    int l=1,r=30000,mid,ans;
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;
    return 0;
}
