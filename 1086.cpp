#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define maxn 1001
 
using namespace std;
 
struct EdgeType {
    int to,next;
};
struct EdgeType edge[maxn<<1];
 
int head[maxn],cnt,n,belong[maxn],root[maxn],b;
int stack[maxn],top;
 
inline void edge_add(int from,int to)
{
    edge[++cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt;
}
 
void search(int now,int fa)
{
    int bottom=top;
    for(int i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==fa) continue;
        search(edge[i].to,now);
        if(top-bottom>=b)
        {
            root[++cnt]=now;
            while(top!=bottom)
            {
                belong[stack[top--]]=cnt;
            }
        }
    }
    stack[++top]=now;
}
 
int main()
{
    scanf("%d%d",&n,&b);
    int from,to;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&from,&to);
        edge_add(from,to);
        edge_add(to,from);
    }
    cnt=0,search(1,0);
    while(top) belong[stack[top--]]=cnt;
    printf("%d\n",cnt);
    for(int i=1;i<=n;i++)
    {
        printf("%d ",belong[i]);
    }
    printf("\n");
    for(int i=1;i<=cnt;i++)
    {
        printf("%d ",root[i]);
    }
    return 0;
}
