#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=200005;
struct node
{
    int A,B,C,D,id;
    bool operator<(const node &pos)const
    {
        return A<pos.A;
    }
};
struct node ai[maxn],tmps[maxn];
int n,biA[maxn],biB[maxn],biC[maxn],biD[maxn],cntx,cnty,tot;
int ch[maxn*18][2],root[maxn],val[maxn*18];
bool vis[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void add(int &now,int pre,int l,int r,int to,int x)
{
    now=++tot,ch[now][0]=ch[now][1]=val[now]=0;
    if(l==r)
    {
        val[now]=x;
        return;
    }
    int mid=l+r>>1;
    if(to<=mid) add(ch[now][0],ch[pre][0],l,mid,to,x),ch[now][1]=ch[pre][1];
    else add(ch[now][1],ch[pre][1],mid+1,r,to,x),ch[now][0]=ch[pre][0];
    val[now]=max(val[ch[now][0]],val[ch[now][1]]);
}
int query(int now,int l,int r,int tl,int tr)
{
    if(!now) return 0;
    if(l>=tl&&r<=tr) return val[now];
    int res=0,mid=l+r>>1;
    if(tl<=mid) res=max(res,query(ch[now][0],l,mid,tl,tr));
    if(tr>mid) res=max(res,query(ch[now][1],mid+1,r,tl,tr));
    return res;
}
int find(int l,int r,int to)
{
    int mid,res=0;
    while(l<=r)
    {
        mid=l+r>>1;
        if(ai[mid].B<to) res=mid,l=mid+1;
        else r=mid-1;
    }
    return res;
}
void solve(int l,int r)
{
    if(l==r) return;
    int mid=l+r>>1;
    solve(l,mid);
    root[l-1]=tot=0;
    for(int i=l;i<=mid;i++)
        add(root[i],root[i-1],1,n,ai[i].C,ai[i].D);
    for(int i=mid+1,tmp;i<=r;i++)
    {
        if(vis[ai[i].id]) continue;
        tmp=find(l,mid,ai[i].B);
        if(!tmp||ai[i].C==n) continue;
        tmp=query(root[tmp],1,n,ai[i].C+1,n);
        if(tmp>ai[i].D) vis[ai[i].id]=true;
    }
    solve(mid+1,r);int i,posl,posr;
    for(i=l,posl=l,posr=mid+1;i<=r;i++)
    {
        if(posl==mid+1||posr==r+1) break;
        if(ai[posl].B<ai[posr].B) tmps[i]=ai[posl++];
        else tmps[i]=ai[posr++];
    }
    while(posl<=mid) tmps[i++]=ai[posl++];
    while(posr<=r) tmps[i++]=ai[posr++];
    for(i=l;i<=r;i++) ai[i]=tmps[i];
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++)
    {
        in(ai[i].A),in(ai[i].B),in(ai[i].C),in(ai[i].D),ai[i].id=i;
        biA[i]=ai[i].A,biB[i]=ai[i].B,biC[i]=ai[i].C,biD[i]=ai[i].D;
    }
    sort(biA+1,biA+n+1);
    sort(biB+1,biB+n+1);
    sort(biC+1,biC+n+1);
    sort(biD+1,biD+n+1);
    for(int i=1;i<=n;i++)
    {
        ai[i].A=lower_bound(biA+1,biA+n+1,ai[i].A)-biA;
        ai[i].B=lower_bound(biB+1,biB+n+1,ai[i].B)-biB;
        ai[i].C=lower_bound(biC+1,biC+n+1,ai[i].C)-biC;
        ai[i].D=lower_bound(biD+1,biD+n+1,ai[i].D)-biD;
    }
    sort(ai+1,ai+n+1);
    solve(1,n);
    int ans=0;
    for(int i=1;i<=n;i++) ans+=vis[i];
    cout<<ans;
    return 0;
}
