#include <bits/stdc++.h>
using namespace std;
#define maxa 262143
#define maxn 200005
#define maxtree maxa*40
int n,m,ch[maxtree][2],val[maxtree],L[maxtree],R[maxtree];
int root[maxn],mid[maxtree],tot;
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void build(int &now,int l,int r)
{
    now=++tot,L[now]=l,R[now]=r;
    if(l==r) return;mid[now]=l+r>>1;
    build(ch[now][0],l,mid[now]);
    build(ch[now][1],mid[now]+1,r);
}
void add(int &now,int pre,int x)
{
    now=++tot,val[now]=val[pre]+1,L[now]=L[pre],R[now]=R[pre];
    if(L[now]==R[now]) return ;mid[now]=mid[pre];
    if(x<=mid[now]) add(ch[now][0],ch[pre][0],x),ch[now][1]=ch[pre][1];
    else add(ch[now][1],ch[pre][1],x),ch[now][0]=ch[pre][0];
}
bool query(int now,int pre,int l,int r)
{
    if(L[now]>=l&&R[now]<=r) return (val[now]-val[pre])?true:false;
    if(l<=mid[now]) if(query(ch[now][0],ch[pre][0],l,r)) return true;
    if(r>mid[now]) if(query(ch[now][1],ch[pre][1],l,r)) return true;
    return false;
}
int solve(int now,int pre,int deep,int b,int x,int l,int r)
{
    if(deep<0) return 0;int mi=l+r>>1;
    if(b<(1<<deep))
    {
        if(query(root[now],root[pre],max(0,mi+1-x),r-x)) return solve(now,pre,deep-1,b,x,mi+1,r)+(1<<deep);
        else return solve(now,pre,deep-1,b,x,l,mi);
    }
    else
    {
        if(mi-x<0||query(root[now],root[pre],max(l-x,0),mi-x)) return solve(now,pre,deep-1,b-(1<<deep),x,l,mi)+(1<<deep);
        else return solve(now,pre,deep-1,b-(1<<deep),x,mi+1,r);
    }
}
int main()
{
    in(n),in(m),build(root[0],0,maxa);int pos,b,x,l,r;
    for(int i=1;i<=n;i++) in(pos),add(root[i],root[i-1],pos);
    while(m--) in(b),in(x),in(l),in(r),printf("%d\n",solve(r,l-1,17,b,x,0,maxa));
    return 0;
}
