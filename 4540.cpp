#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define ll long long
ll bel[maxn];
struct QueryType
{
    ll l,r,id;
    bool operator<(const QueryType &pos)const
    {
        if(bel[l]==bel[pos.l]) return r<pos.r;
        return bel[l]<bel[pos.l];
    }
};
struct QueryType qu[maxn];
ll ai[maxn],li[maxn],ri[maxn],sta[maxn],n,m,st[maxn][22];
ll bit[22],lg[maxn];
ll sumr[maxn],suml[maxn],ans[maxn],now;
ll minn(ll x,ll y)
{
    return ai[x]<ai[y]?x:y;
}
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
inline ll get(ll x,ll y)
{
    if(x>y) swap(x,y);
    ll l=lg[y-x+1];
    return minn(st[x][l],st[y-bit[l]+1][l]);
}
inline void updatal(ll l,ll r,bool di)
{
    ll p=get(l,r);
    if(di) now+=1LL*ai[p]*(r-p+1)+sumr[l]-sumr[p];
    else now-=1LL*ai[p]*(r-p+1)+sumr[l]-sumr[p];
}
inline void updatar(ll l,ll r,bool di)
{
    ll p=get(l,r);
    if(di) now+=1LL*ai[p]*(p-l+1)+suml[r]-suml[p];
    else now-=1LL*ai[p]*(p-l+1)+suml[r]-suml[p];
}
int main()
{
    in(n),in(m);ll blo=sqrt(n);lg[0]=-1;
    for(ll i=1;i<=n;i++) bel[i]=(i-1)/blo+1,in(ai[i]);
    for(ll i=1;i<=m;i++) in(qu[i].l),in(qu[i].r),qu[i].id=i;
    bit[0]=1;for(ll i=1;i<=18;i++) bit[i]=bit[i-1]<<1;
    for(ll i=1;i<=n;i++) lg[i]=lg[i>>1]+1,st[i][0]=i;
    for(ll v=1;v<=18;v++)
        for(ll i=1;i<=n;i++)
        {
            st[i][v]=st[i][v-1];
            if(i+bit[v-1]<=n) st[i][v]=minn(st[i][v-1],st[i+bit[v-1]][v-1]);
        }
    ll top=0;
    for(ll i=1;i<=n;i++)
    {
        while(top&&ai[sta[top]]>=ai[i]) ri[sta[top--]]=i;
        sta[++top]=i;
    }
    while(top) ri[sta[top--]]=n+1;
    for(ll i=n;i;i--)
    {
        while(top&&ai[sta[top]]>ai[i]) li[sta[top--]]=i;
        sta[++top]=i;
    }
    while(top) li[sta[top--]]=0;
    for(ll i=n;i;i--) sumr[i]=sumr[ri[i]]+1LL*(ri[i]-i)*ai[i];
    for(ll i=1;i<=n;i++) suml[i]=suml[li[i]]+1LL*(i-li[i])*ai[i];
    sort(qu+1,qu+m+1);now=ai[1];
    for(ll l=1,r=1,no=1;no<=m;no++)
    {
        for(;r<qu[no].r;r++) updatar(l,r+1,true);
        for(;l>qu[no].l;l--) updatal(l-1,r,true);
        for(;r>qu[no].r;r--) updatar(l,r,false);
        for(;l<qu[no].l;l++) updatal(l,r,false);
        ans[qu[no].id]=now;
    }
    for(ll i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
