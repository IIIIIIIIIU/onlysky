#include <cstdio>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 80005
#define mod 1000000
#define INF 0x7fffffff
 
struct TreeNodeType {
    int w,key,opi,size,ch[2];
     
    void destroy()
    {
        w=key=opi=size=ch[0]=ch[1]=0;
    }
     
    void create(int x)
    {
        destroy();
        key=x;
    }
};
struct TreeNodeType tree[maxn<<1];
 
int n,tot,flag,root;
 
long long ans;
 
inline int getson(int now)
{
    return tree[tree[now].opi].ch[1]==now;
}
 
inline void updata(int now)
{
    tree[now].size=tree[now].w;
    if(tree[now].ch[0]) tree[now].size+=tree[tree[now].ch[0]].size;
    if(tree[now].ch[1]) tree[now].size+=tree[tree[now].ch[1]].size;
}
 
inline void rotate(int now)
{
    int opi=tree[now].opi,fopi=tree[opi].opi,pos=getson(now);
    tree[opi].ch[pos]=tree[now].ch[pos^1];
    tree[tree[opi].ch[pos]].opi=opi,tree[now].opi=fopi;
    if(fopi) tree[fopi].ch[getson(opi)]=now;
    tree[opi].opi=now,tree[now].ch[pos^1]=opi;
    updata(opi),updata(now);
}
 
void splay(int now)
{
    for(int opi;opi=tree[now].opi;rotate(now))
    {
        if(tree[opi].opi) rotate(getson(now)==getson(opi)?opi:now);
    }
    root=now;
}
 
void insert(int x)
{
    if(!root) tree[++tot].create(x),root=tot;
    else
    {
        int now=root,opi=0;
        while(1)
        {
            if(tree[now].key==x)
            {
                tree[now].w++;
                tree[now].size++;
                splay(now);
                return ;
            }
            opi=now,now=tree[now].ch[x>tree[now].key];
            if(!now)
            {
                tree[++tot].create(x);
                tree[tot].opi=opi;
                tree[opi].ch[x>tree[opi].key]=tot;
                splay(tot);
                return ;
            }
        }
    }
}
 
inline int pre()
{
    if(tree[root].w>1) return root;
    if(!tree[root].ch[0]) return 0;
    int now=tree[root].ch[0];
    while(tree[now].ch[1]) now=tree[now].ch[1];
    return now;
}
 
inline int suc()
{
    if(tree[root].w>1) return root;
    if(!tree[root].ch[1]) return 0;
    int now=tree[root].ch[1];
    while(tree[now].ch[0]) now=tree[now].ch[0];
    return now;
}
 
void del()
{
    if(tree[root].w>1)
    {
        tree[root].w--;
        tree[root].size--;
        return ;
    }
    if(!tree[root].ch[0]&&!tree[root].ch[1])
    {
        tree[root].destroy();
        root=0;tree[root].destroy();return ;
    }
    if(tree[root].ch[0]&&!tree[root].ch[1])
    {
        int tmp=root;
        root=tree[root].ch[0];
        tree[tmp].destroy();
        tree[root].opi=0;
        return ;
    }
    if(!tree[root].ch[0]&&tree[root].ch[1])
    {
        int tmp=root;
        root=tree[root].ch[1];
        tree[tmp].destroy();
        tree[root].opi=0;
        return ;
    }
    int tmp=pre(),pos=root;
    tree[tmp].ch[1]=tree[root].ch[1];
    tree[tree[tmp].ch[1]].opi=tmp;
    root=tree[root].ch[0],tree[root].opi=0;
    tree[pos].destroy();
    splay(tree[tmp].ch[1]);
}
 
int main()
{
    scanf("%d",&n);int ty,x;
    while(n--)
    {
        scanf("%d%d",&ty,&x);
        if(!root)
        {
            flag=ty;
            insert(x);
        }
        else
        {
            if(ty==flag) insert(x);
            else
            {
                insert(x);
                int pr=pre(),su=suc(),to;
                if(!pr) ans+=abs(tree[su].key-x),to=su;
                else if(!su) ans+=abs(tree[pr].key-x),to=pr;
                else
                {
                    if(abs(tree[pr].key-x)<=abs(tree[su].key-x)) ans+=abs(tree[pr].key-x),to=pr;
                    else ans+=abs(tree[su].key-x),to=su;
                }
                del(),splay(to),del();
            }
        }
    }
    cout<<ans%mod;
    return 0;
}
