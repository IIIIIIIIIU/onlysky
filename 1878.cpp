#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=50005;
int pre[maxn],ai[maxn],bi[maxn],ci[maxn],size,n,m,tot;
int root[maxn],ch[maxn*20][2],val[maxn*20];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void add(int &now,int pre,int l,int r,int to)
{
    now=++tot,val[now]=val[pre]+1;
    if(l==r) return;
    int mid=l+r>>1;
    if(to<=mid) add(ch[now][0],ch[pre][0],l,mid,to),ch[now][1]=ch[pre][1];
    else add(ch[now][1],ch[pre][1],mid+1,r,to),ch[now][0]=ch[pre][0];
}
int query(int now,int pre,int l,int r,int tl,int tr)
{
    if(l>=tl&&r<=tr) return val[now]-val[pre];
    int mid=l+r>>1,res=0;
    if(tl<=mid) res+=query(ch[now][0],ch[pre][0],l,mid,tl,tr);
    if(tr>mid) res+=query(ch[now][1],ch[pre][1],mid+1,r,tl,tr);
    return res;
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++) in(ai[i]),bi[i]=ai[i];
    sort(bi+1,bi+n+1),size=unique(bi+1,bi+n+1)-bi-1;
    for(int i=1;i<=n;i++)
    {
        ai[i]=lower_bound(bi+1,bi+size+1,ai[i])-bi;
        ci[i]=pre[ai[i]],pre[ai[i]]=i;
        add(root[i],root[i-1],0,n,ci[i]);
    }
//  for(int i=1;i<=n;i++)
    in(m);int l,r;
    while(m--)
    {
        in(l),in(r);
        if(l>r) swap(l,r);
        printf("%d\n",query(root[r],root[l-1],0,n,0,l-1));
    }
    return 0;
}
