#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define M 30300
 
using namespace std;
 
struct Block{
    int a[210],size;
     
    void Insert(int x)
    {
        int i;
        ++size;
        for(i=size;i>1&&a[i-1]>x;i--) a[i]=a[i-1];
        a[i]=x;
    }
     
    void Modify(int x,int y)
    {
        int temp=lower_bound(a+1,a+size+1,x)-a;
        for(;temp<size&&a[temp+1]<y;temp++)
            a[temp]=a[temp+1];
        for(;temp>1&&a[temp-1]>y;temp--)
            a[temp]=a[temp-1];
        a[temp]=y;
    }
     
    int Query(int x)
    {
        int temp=upper_bound(a+1,a+size+1,x)-a;
        return size-temp+1;
    }
}blocks[10100];
 
struct abcd{
    int to,next;
}table[M<<2];
 
int head[M<<1],block_head[M],tot;
int n,m,block,ans,cnt;
int a[M<<1],fa[M<<1],belong[M<<1];
 
void Add(int _head[],int x,int y)
{
    table[++tot].to=y;
    table[tot].next=_head[x];
    _head[x]=tot;
}
 
void DFS(int x)
{
    int i;
    if(blocks[belong[fa[x]]].size==block)
        blocks[belong[x]=++cnt].Insert(a[x]),Add(block_head,belong[fa[x]],cnt);
    else
        blocks[belong[x]=belong[fa[x]]].Insert(a[x]);
    for(i=head[x];i;i=table[i].next)
        if(table[i].to!=fa[x])
            fa[table[i].to]=x,DFS(table[i].to);
}
 
void Block_DFS(int x,int y)
{
    int i;
    ans+=blocks[x].Query(y);
    for(i=block_head[x];i;i=table[i].next) Block_DFS(table[i].to,y);
}
 
void DFS(int x,int y)
{
    int i;
    if(a[x]>y) ++ans;
    for(i=head[x];i;i=table[i].next)
        if(table[i].to!=fa[x])
            if(belong[table[i].to]==belong[x])
                DFS(table[i].to,y);
            else
                Block_DFS(belong[table[i].to],y);
}
 
int main()
{
    int i,j,x,y,p;
    cin>>n;
    for(i=1;i<n;i++)
        scanf("%d%d",&x,&y),Add(head,x,y),Add(head,y,x);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    block=static_cast<int>(sqrt(n)+1e-7);
    DFS(1);
    cin>>m;
    for(i=1;i<=m;i++)
    {
        scanf("%d%d%d",&p,&x,&y);
        x^=ans;y^=ans;
        switch(p)
        {
            case 0:
                ans=0;
                DFS(x,y);
                printf("%d\n",ans);
                break;
            case 1:
                blocks[belong[x]].Modify(a[x],y);
                a[x]=y;
                break;
            case 2:
                a[++n]=y;
                Add(head,x,n);
                fa[n]=x;
                if(blocks[belong[x]].size==block)
                    blocks[belong[n]=++cnt].Insert(y),Add(block_head,belong[x],cnt);
                else
                    blocks[belong[n]=belong[x]].Insert(y);
                break;
        }
    }
    return 0;
}
