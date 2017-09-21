#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 1000005
 
struct TreeNodeType {
    int w,key,opi,size,ch[2];
     
    void destroy()
    {
        w=key=opi=size=ch[0]=ch[1]=0;
    }
     
    void create(int x)
    {
        key=x;
        w=size=1;
        opi=ch[0]=ch[1]=0;
    }
};
struct TreeNodeType tree[maxn<<1];
 
int n,ko,root,tot,cur,ans,tot_;
 
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
    if(tree[tree[now].ch[pos^1]].opi)tree[tree[now].ch[pos^1]].opi=opi;
    tree[opi].ch[pos]=tree[now].ch[pos^1];
    if(fopi) tree[fopi].ch[getson(opi)]=now;
    tree[opi].opi=now;tree[now].opi=fopi;
    tree[now].ch[pos^1]=opi;
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
                break;
            }
            opi=now,now=tree[now].ch[x>tree[now].key];
            if(!now)
            {
                tot++;
                tree[tot].create(x);
                tree[tot].opi=opi;
                tree[opi].ch[x>tree[opi].key]=tot;
                splay(tot);break;
            }
        }
    }
}
 
void del()
{
    ans+=tree[root].size-1;
    if(!tree[root].ch[1]) tree[0].destroy(),root=0;
    else
    {
        int tmp=root;
        root=tree[root].ch[1];
        tree[tmp].destroy();
        tree[root].opi=0;
        ans-=tree[root].size;
    }
}
 
int rank(int x)
{
    int now=root;
    while(1)
    {
        if(tree[now].ch[0])
        {
            if(x>tree[tree[now].ch[0]].size) x-=tree[tree[now].ch[0]].size;
            else
            {
                now=tree[now].ch[0];
                continue;
            }
        }
        if(x<=tree[now].w)
        {
            splay(now);
            return tree[now].key;
        }
        else
        {
            x-=tree[now].w;
            now=tree[now].ch[1];
        }
    }
}
 
int main()
{
    in(n),in(ko),ko--;
    char ch[4];int pos;
    while(n--)
    {
        scanf("%s",ch);in(pos);
        if(ch[0]=='I') if(pos>ko) insert(pos+cur-ko),tot_++;
        if(ch[0]=='A') cur-=pos;
        if(ch[0]=='S') cur+=pos,insert(cur),del();
        if(ch[0]=='F')
        {
            if(tot_-ans>=pos) printf("%d\n",rank(tot_-ans-pos+1)-cur+ko);
            else printf("-1\n");
        }
    }
    printf("%d\n",ans);
    return 0;
}
