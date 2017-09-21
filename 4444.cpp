#include <cstdio>
#include <algorithm>
#define maxn 800010
int n,m,ai[maxn][2],bi[maxn],f[maxn<<1],st[maxn];
int g[maxn],nxt[maxn<<1],q[maxn<<1],t,ans[maxn],L,x,y,i;
inline void in(int&a)
{
    char c;
    while(!(((c=getchar())>='0')&&(c<='9')));
    a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';
}
inline int lower(int x)
{
    int l=1,r=m,mid,t;
    while(l<=r) if(bi[mid=(l+r)>>1]<=x) l=(t=mid)+1;else r=mid-1;
    return t;
}
inline void up(int &x,int y)
{
    if(x<y) x=y;
}
void dfs(int x)
{
    q[++t]=x;
    if(x<=m)
        for(int i=L;;i++)
            if(q[t-i]>=x+m)
            {
                ans[x]=i;
                break;
            }
    for(int i=g[x];i;i=nxt[i]) dfs(i);
    t--;
}
int main()
{
    in(n),in(m);
    for(m=0,i=1;i<=n;i++) in(ai[i][0]),in(ai[i][1]),bi[++m]=ai[i][0],bi[++m]=ai[i][1];
    for(std::sort(bi+1,bi+m+1),i=1;i<=n;i++)
    {
        st[i]=x=lower(ai[i][0]),y=lower(ai[i][1]);
        if(x<y) up(f[x],y),up(f[x+m],y+m);
        else up(f[1],y),up(f[x],y+m),up(f[x+m],m+m);
    }
    for(i=1;i<=m+m;i++) up(f[i],f[i-1]);
    for(i=1;i<m+m;i++) nxt[i]=g[f[i]],g[f[i]]=i;
    for(L=-1,i=1;i<=m;i=f[i])L++;
    dfs(m+m);
    for(i=1;i<=n;i++) printf("%d ",ans[st[i]]);
    return 0;
}
