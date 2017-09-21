#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define ll long long
struct QueryType
{
    ll l,r,id,bel;
    bool operator<(const QueryType &pos) const
    {
        if(bel==pos.bel) return r<pos.r;
        return bel<pos.bel;
    }
};
struct QueryType qu[maxn];
ll n,m,mod,sum[maxn],bi[maxn],size,ans[maxn],cnt,num[maxn],ai[maxn];
char ch[maxn];
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
inline void updata(ll x,bool di)
{
    x=sum[x];
    if(di) num[x]++,cnt+=num[x]-1;
    else num[x]--,cnt-=num[x];
}
void updatar(int l,int r,bool di)
{
    int x=ch[r]-'0';
    if(di)
    {
        if(x%mod==0)
        {
            num[0]++;
            cnt+=r-l+1;
        }
    }
    else
    {
        if(x%mod==0)
        {
            cnt-=r-l+1;
            num[0]--;
        }
    }
}
void updatal(int l,int r,int di)
{
    int x=ch[l]-'0';
    if(di)
    {
        if(x%mod==0) num[0]++;
        cnt+=num[0];
    }
    else
    {
        if(x%mod==0)
        {
            num[0]--;
            cnt--;
        }
        cnt-=num[0];
    }
}
int main()
{
    in(mod),scanf("%s",ch+1),n=strlen(ch+1),in(m);
    ll blo=sqrt(n);n++,ch[n]='0';
    for(ll i=1;i<=m;i++)
    {
        in(qu[i].l),in(qu[i].r);
        if(mod!=5&&mod!=2) qu[i].r++;
        qu[i].id=i,qu[i].bel=qu[i].l/blo;
    }
    sort(qu+1,qu+m+1);ll t=1;
    if(mod==2||mod==5)
    {
        int l=1,r=0;
        for(int i=1;i<=m;i++)
        {
            while(r<qu[i].r) updatar(l,++r,true);
            while(r>qu[i].r) updatar(l,r--,false);
            while(l<qu[i].l) updatal(l++,r,false);
            while(l>qu[i].l) updatal(--l,r,true);
            ans[qu[i].id]=cnt;
        }
        for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
        return 0;
    }
    for(ll i=n;i>0;i--) sum[i]=(sum[i+1]+(ch[i]-'0')*t)%mod,bi[i]=sum[i],t=t*10%mod;
    sort(bi+1,bi+n+1),size=unique(bi+1,bi+n+1)-bi-1;
    for(ll i=1;i<=n;i++) sum[i]=lower_bound(bi+1,bi+size+1,sum[i])-bi;
    ll l=1,r=0;
    for(ll no=1;no<=m;no++)
    {
        while(r<qu[no].r) updata(++r,true);
        while(r>qu[no].r) updata(r--,false);
        while(l<qu[no].l) updata(l++,false);
        while(l>qu[no].l) updata(--l,true);
        ans[qu[no].id]=cnt;
    }
    for(ll i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
