#include <bits/stdc++.h>
using namespace std;
#define maxn 10005
#define lowbit(x) (x&(-x))
int ai[maxn],bi[maxn],f[maxn],n,m,size;
int L[maxn<<2],R[maxn<<2],mid[maxn<<2],val[maxn<<2];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void build(int now,int l,int r)
{
    L[now]=l,R[now]=r;if(l==r) return;mid[now]=l+r>>1;
    build(now<<1,l,mid[now]),build(now<<1|1,mid[now]+1,r);
}
void add(int now,int to,int x)
{
    if(L[now]==R[now])
    {
        val[now]=x;
        return;
    }
    if(to<=mid[now]) add(now<<1,to,x);
    else add(now<<1|1,to,x);
    val[now]=max(val[now<<1],val[now<<1|1]);
}
int query(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r) return val[now];
    int res=0;
    if(l<=mid[now]) res=max(res,query(now<<1,l,r));
    if(r>mid[now]) res=max(res,query(now<<1|1,l,r));
    return res;
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++) in(ai[i]),bi[i]=ai[i];
    sort(bi+1,bi+n+1),size=unique(bi+1,bi+n+1)-bi-1;
    for(int i=1;i<=n;i++) ai[i]=lower_bound(bi+1,bi+size+1,ai[i])-bi;
    build(1,1,size);
    for(int i=n;i>0;i--)
    {
        f[i]=1;
        if(ai[i]<size) f[i]+=query(1,ai[i]+1,size);
        add(1,ai[i],f[i]);
    }
    in(m);int pos,tmp;
    for(int i=1;i<=m;i++)
    {
        in(pos);tmp=0;
        for(int v=1;v<=n;v++)
        {
            if(!pos) break;
            if(f[v]>=pos&&ai[v]>tmp)
            {
                pos--,tmp=ai[v];
                if(pos) printf("%d ",bi[ai[v]]);
                else printf("%d",bi[ai[v]]);
            }
        }
        if(tmp==0) printf("Impossible");
        printf("\n");
    }
    return 0;
}
