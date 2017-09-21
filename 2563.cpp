#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 100005
#define ll long long
ll ai[maxn],ans,n,m;
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
bool cmp(ll a,ll b)
{
    return a>b;
}
int main()
{
in(n),in(m);ll u,v,w;
    for(int i=1;i<=n;++i) in(ai[i]),ans-=ai[i],ai[i]=ai[i]*2;
    for(int i=1;i<=m;++i) in(u),in(v),in(w),ai[u]+=w,ai[v]+=w,ans-=w;
    sort(ai+1,ai+n+1,cmp);
    for(int i=1;i<=n;++i) if(i&1) ans+=ai[i];
    cout<<ans;
    fclose(stdin),fclose(stdout);
    return 0;
}
