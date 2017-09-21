#include <cstdio>
#include <iostream>
#include <algorithm>
 
#define LL long long 
#define maxn 100005
 
using namespace std;
  
struct TreeNodeType {
    LL l,r,dis,sum;
};
struct TreeNodeType tree[maxn*25];
  
struct EdgeType {
    LL to,next;
};
struct EdgeType edge[maxn<<1];
  
LL if_z,n,m,head[maxn],cost[maxn],lead[maxn];
LL cnt,hash[maxn],root[maxn],tot,start[maxn],end[maxn];
LL ans=0,size;
  
char Cget;
  
inline void read_int(LL &now)
{
    if_z=1,Cget=getchar(),now=0;
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
  
inline void edge_add(LL from,LL to)
{
    cnt++;
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt;
}
  
void tree_build(LL now,LL l,LL r)
{
    if(l==r) return ;
    LL mid=(l+r)>>1;
    tree[now].l=++tot;
    tree_build(tree[now].l,l,mid);
    tree[now].r=++tot;
    tree_build(tree[now].r,mid+1,r);
}
  
void tree_add(LL pre,LL now,LL pos,LL l,LL r)
{
    tree[now].dis=tree[pre].dis+1;
    tree[now].sum=tree[pre].sum+hash[pos];
    if(l==r) return ;
    LL mid=(l+r)>>1;
    if(pos<=mid)
    {
        tree[now].l=++tot;
        tree_add(tree[pre].l,tree[now].l,pos,l,mid);
        tree[now].r=tree[pre].r;
    }
    else
    {
        tree[now].r=++tot;
        tree_add(tree[pre].r,tree[now].r,pos,mid+1,r);
        tree[now].l=tree[pre].l;
    }
}
  
void Search(LL now,LL fa)
{
    start[now]=cnt++,root[cnt]=++tot;
    LL pos=lower_bound(hash+1,hash+size+1,cost[now])-hash;
    tree_add(root[cnt-1],root[cnt],pos,1,size);
    for(LL i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==fa) continue;
        Search(edge[i].to,now);
    }
    end[now]=cnt;
}
  
LL tree_query(LL pre,LL now,LL pos,LL l,LL r)
{
    if(l==r) return min(pos/hash[l],tree[now].dis-tree[pre].dis);
    LL pos_=tree[tree[now].l].dis-tree[tree[pre].l].dis;
    LL mid=(l+r)>>1,dis_=tree[tree[now].l].sum-tree[tree[pre].l].sum;
    if(pos<=dis_) return tree_query(tree[pre].l,tree[now].l,pos,l,mid);
    else return tree_query(tree[pre].r,tree[now].r,pos-dis_,mid+1,r)+pos_;
}
  
int main()
{
    read_int(n),read_int(m);
    LL bi,master;
    for(LL i=1;i<=n;i++)
    {
        read_int(bi),read_int(cost[i]),read_int(lead[i]);
        edge_add(bi,i),edge_add(i,bi),hash[i]=cost[i];
        if(bi==0) master=i;
    }
    sort(hash+1,hash+n+1);
    size=unique(hash+1,hash+n+1)-hash-1;
    root[0]=++tot;
    tree_build(root[0],1,size);
    cnt=0,Search(master,0);
    for(LL i=1;i<=n;i++)
    {
        LL pos=tree_query(root[start[i]],root[end[i]],m,1,size);
        ans=max(ans,lead[i]*pos);
    }
    cout<<ans<<endl;
    return 0;
}
