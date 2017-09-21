#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
struct QueryType
{
    int l,r,id,key,op,x;
    bool operator<(const QueryType pos)const
    {
        if(key==pos.key) return r<pos.r;
        return key<pos.key;
    }
};
struct QueryType qu[maxn];
int n,m,ai[maxn],cnt[maxn];
bool ans[maxn];
bitset<100001>a,b;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
bool get(int x)
{
    if(qu[x].op==1)
    {
        return (a&(a>>qu[x].x)).any();
    }
    if(qu[x].op==2)
    {
        return (a&(b>>(100000-qu[x].x))).any();
    }
    int dis=qu[x].x;
    if(!dis) return cnt[0];
    for(int i=1;i*i<=qu[x].x;i++)
        if(dis%i==0&&cnt[i]&&cnt[dis/i]) return true;
    return false;
}
void updata(int x,bool di)
{
    x=ai[x];
    if(di) cnt[x]++,a[x]=true,b[100000-x]=true;
    else
    {
        cnt[x]--;
        if(!cnt[x]) a[x]=false,b[100000-x]=false;
    }
}
int main()
{
    in(n),in(m);int blo=sqrt(n);
    for(int i=1;i<=n;i++) in(ai[i]);
    for(int i=1;i<=m;i++)
    {
        in(qu[i].op),in(qu[i].l),in(qu[i].r),in(qu[i].x);
        qu[i].id=i,qu[i].key=qu[i].l/blo;
    }
    sort(qu+1,qu+m+1);
    int l=1,r=0;
    for(int i=1;i<=m;i++)
    {
        while(r<qu[i].r) updata(++r,true);
        while(r>qu[i].r) updata(r--,false);
        while(l<qu[i].l) updata(l++,false);
        while(l>qu[i].l) updata(--l,true);
        ans[qu[i].id]=get(i);
    }
    for(int i=1;i<=m;i++) puts(ans[i]?"yuno":"yumi");
    return 0;
}
