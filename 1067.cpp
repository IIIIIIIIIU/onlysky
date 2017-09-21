#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=50005;
const int maxtree=maxn<<2;
int n,bi[maxn],ri[maxn],L[maxtree],R[maxtree],mid[maxtree];
int val[maxtree],m;
inline void in(int &now)
{
    char Cget;int if_z=1;now=0;
    while((Cget=getchar())>'9'||Cget<'0') if(Cget=='-') if_z=-1;
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}
void build(int now,int l,int r)
{
    L[now]=l,R[now]=r;
    if(l==r)
    {
        val[now]=ri[l];
        return;
    }
    mid[now]=l+r>>1;
    build(now<<1,l,mid[now]);
    build(now<<1|1,mid[now]+1,r);
    val[now]=max(val[now<<1],val[now<<1|1]);
}
int query(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r) return val[now];
    int res=0;
    if(l<=mid[now]) res=query(now<<1,l,r);
    if(r>mid[now]) res=max(res,query(now<<1|1,l,r));
    return res;
}
int get(int k)
{
    int l=0,r=n+1,mid,res=0;
    while(l<=r)
    {
        mid=l+r>>1;
        if(bi[mid]>=k) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++) in(bi[i]),in(ri[i]);
    build(1,0,n+1);
    bi[0]=-2e9,bi[n+1]=2e9;
    in(m);int x,y,idx,idy,tmp1,tmp2,tmp3;
    while(m--)
    {
        in(x),in(y);
        idx=get(x),idy=get(y);
        tmp1=query(1,idx,idx);
        tmp2=query(1,idy,idy);
        if(idy>idx+1) tmp3=query(1,idx+1,idy-1);
        else tmp3=0;
        if(x!=bi[idx]&&y!=bi[idy])
        {
            printf("maybe\n");
            continue;
        }
        if(x!=bi[idx])
        {
            if(idy>idx) tmp3=query(1,idx,idy-1);
            else tmp3=0;
            if(tmp3<tmp2) printf("maybe\n");
            else printf("false\n");
            continue;
        }
        if(y!=bi[idy])
        {
            if(idy>idx+1) tmp3=query(1,idx+1,idy-1);
            else tmp3=0;
            if(tmp3<tmp1) printf("maybe\n");
            else printf("false\n");
            continue;
        }
        if(tmp2<=tmp1&&tmp3<tmp2)
        {
            if(y-x==idy-idx) printf("true\n");
            else printf("maybe\n");
        }
        else printf("false\n");
    }
    return 0;
}
