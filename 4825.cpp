#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxtree maxn<<2
int val[maxtree],tag[maxtree],L[maxtree],R[maxtree],mid[maxtree];
int op[maxn],ki[maxn],bi[maxn],cnt,size,n,ch[maxn][2],f[maxn],root;
set<int>Set;
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void build(int now,int l,int r)
{
    L[now]=l,R[now]=r;if(l==r) return;mid[now]=l+r>>1;
    build(now<<1,l,mid[now]),build(now<<1|1,mid[now]+1,r);
}
inline void pushdown(int now)
{
    val[now<<1]+=tag[now],tag[now<<1]+=tag[now];
    val[now<<1|1]+=tag[now],tag[now<<1|1]+=tag[now];
    tag[now]=0;
}
void add(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r)
    {
        val[now]++,tag[now]++;
        return;
    }
    if(tag[now]!=0) pushdown(now);
    if(l<=mid[now]) add(now<<1,l,r);
    if(r>mid[now]) add(now<<1|1,l,r);
}
void Minus(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r)
    {
        val[now]--,tag[now]--;
        return;
    }
    if(tag[now]!=0) pushdown(now);
    if(l<=mid[now]) Minus(now<<1,l,r);
    if(r>mid[now]) Minus(now<<1|1,l,r);
}
int get(int to)
{
    int l=1,r=size,now=1;
    while(l!=r)
    {
        if(tag[now]!=0) pushdown(now);
        if(to<=mid[now]) r=mid[now],now=now<<1;
        else l=mid[now]+1,now=now<<1|1;
    }
    return val[now];
}
void era(int to,int justval)
{
    int l=1,r=size,now=1;
    while(l!=r)
    {
        if(tag[now]!=0) pushdown(now);
        if(to<=mid[now]) r=mid[now],now=now<<1;
        else l=mid[now]+1,now=now<<1|1;
    }
    val[now]=justval;
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++)
    {
        in(op[i]);
        if(op[i]==1) in(ki[i]),bi[++cnt]=ki[i];
    }
    sort(bi+1,bi+cnt+1),size=unique(bi+1,bi+cnt+1)-bi-1,build(1,1,size);
    int l,r,x,fa,cost;set<int>::iterator it,it_;
    for(int i=1;i<=n;i++)
    {
        if(op[i]==1)
        {
            x=lower_bound(bi+1,bi+size+1,ki[i])-bi;
            l=0,r=0,it=it_=Set.insert(x).first;
            if(it!=Set.begin()) l=*(--it);
            if(x!=*Set.rbegin()) r=*(++it_);
            if(!l&&!r) root=x,cost=1;
            else if(l&&ch[l][1]==0) ch[l][1]=x,f[x]=l,cost=get(l)+1;
            else if(r&&ch[r][0]==0) ch[r][0]=x,f[x]=r,cost=get(r)+1;
            printf("%d\n",cost),era(x,cost);
        }
        if(op[i]==2||op[i]==4)
        {
            it=Set.begin(),x=*it;
            if(x!=root)
            {
                printf("%d\n",get(x));
                if(ch[x][1]) Minus(1,x+1,f[x]-1),ch[f[x]][0]=ch[x][1],f[ch[x][1]]=f[x];
                else ch[f[x]][0]=0;
                ch[x][1]=root,f[root]=x,f[x]=0,root=x;
                add(1,1,size),era(x,1);
            }
            else printf("1\n");
            if(op[i]==4) root=ch[root][1],f[root]=0,Minus(1,1,size),Set.erase(it);
        }
        if(op[i]==3||op[i]==5)
        {
            it=Set.end(),x=*(--it);
            if(x!=root)
            {
                printf("%d\n",get(x));
                if(ch[x][0]) Minus(1,f[x]+1,x-1),ch[f[x]][1]=ch[x][0],f[ch[x][0]]=f[x];
                else ch[f[x]][1]=0;
                ch[x][0]=root,f[root]=x,f[x]=0,root=x;
                add(1,1,size),era(x,1);
            }
            else printf("1\n");
            if(op[i]==5) root=ch[root][0],f[root]=0,Minus(1,1,size),Set.erase(it);
        }
    }
    return 0;
}
