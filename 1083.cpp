#include <bits/stdc++.h>
using namespace std;
const int maxn=305;
const int maxm=10005;
struct EdgeType
{
    int u,v,w;
    bool operator<(const EdgeType &pos)const
    {
        return w<pos.w;
    }
};
struct EdgeType e[maxm];
int n,m,f[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
int find(int x)
{
    if(x==f[x]) return f[x];
    return f[x]=find(f[x]);
}
bool check(int lit)
{
    int i=1,x,y,cnt=0;
    for(int v=1;v<=n;v++) f[v]=v;
    while(e[i].w<=lit&&i<=m)
    {
        x=find(e[i].u),y=find(e[i].v);
        if(x!=y) f[x]=y,cnt++;
        i++;
    }
    return cnt==n-1;
}
int main()
{
    in(n),in(m);int Max=0,Min=0x3f3f3f3f;
    for(int i=1;i<=m;i++)
        in(e[i].u),in(e[i].v),in(e[i].w),Max=max(Max,e[i].w),Min=min(Min,e[i].w);
    sort(e+1,e+m+1);
    int l=Min,r=Max,mid,ans;
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<n-1<<' '<<ans;
    return 0;
}
