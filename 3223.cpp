#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 100005
 
struct TreeNodeType {
    int key,opi,size,ch[2],flag;
};
struct TreeNodeType tree[maxn];
 
int n,m,root,ans[maxn],tot;
 
inline void in(int &now)
{
    register char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
 
inline void updata(int now)
{
    tree[now].size=1;
    if(tree[now].ch[0]) tree[now].size+=tree[tree[now].ch[0]].size;
    if(tree[now].ch[1]) tree[now].size+=tree[tree[now].ch[1]].size;
}
 
inline void down(int now)
{
    tree[now].flag=0;
    swap(tree[now].ch[0],tree[now].ch[1]);
    if(tree[now].ch[0]) tree[tree[now].ch[0]].flag^=1;
    if(tree[now].ch[1]) tree[tree[now].ch[1]].flag^=1;
}
 
inline int getson(int now)
{
    return tree[tree[now].opi].ch[1]==now;
}
 
void rotate(int now)
{
    int opi=tree[now].opi,fopi=tree[opi].opi,pos=getson(now);
    if(tree[opi].flag&&opi) down(opi);
    if(tree[now].flag&&now) down(now);
    tree[opi].ch[pos]=tree[now].ch[!pos];
    tree[tree[now].ch[!pos]].opi=opi;
    tree[now].ch[!pos]=opi;
    tree[opi].opi=now;
    tree[now].opi=fopi;
    if(fopi) tree[fopi].ch[tree[fopi].ch[1]==opi]=now;
    updata(opi),updata(now);
}
 
inline void splay(int now,int to)
{
    for(int opi;(opi=tree[now].opi)!=to;rotate(now))
    {
        if(tree[opi].opi!=to) rotate(getson(now)==getson(opi)?opi:now);
    }
    if(!to) root=now;
}
 
int rank_(int x)
{
    int now=root;
    while(1)
    {
        if(tree[now].flag) down(now);
        if(tree[tree[now].ch[0]].size>=x) now=tree[now].ch[0];
        else
        {
            x-=tree[tree[now].ch[0]].size+1;
            if(!x) return now;
            now=tree[now].ch[1];
        }
    }
}
 
void print(int now)
{
    if(tree[now].flag) down(now);
    if(tree[now].ch[0]) print(tree[now].ch[0]);
    ans[++tot]=tree[now].key;
    if(tree[now].ch[1]) print(tree[now].ch[1]);
}
 
int build(int l,int r,int opi)
{
    int now=(l+r)>>1;
    tree[now].opi=opi;
    tree[now].key=ans[now];
    if(now>l) tree[now].ch[0]=build(l,now-1,now);
    if(now<r) tree[now].ch[1]=build(now+1,r,now);
    updata(now);return now;
}
 
int main()
{
    in(n),in(m),root=1;
    for(int i=1;i<=n+2;i++) ans[i]=i-1;
    root=build(1,n+2,0);
    int l,r;
    while(m--)
    {
        in(l),in(r);
        l,r+=2;
        int x=rank_(l),y=rank_(r);
        splay(x,0);
        splay(y,x);
        tree[tree[tree[root].ch[1]].ch[0]].flag^=1;
    }
    print(root);
    for(int i=1;i<=n;i++) printf("%d ",ans[i+1]);
    return 0;
}
