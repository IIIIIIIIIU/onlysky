#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define maxn 1000001
#define INF 0x7fffffff
 
using namespace std;
 
struct EdgeType {
    int to,next,flow;
};
struct EdgeType edge[maxn<<3];
 
int if_z,n,m,cnt,s,t,deep[maxn],ans,head[maxn];
 
char Cget;
 
inline void read_int(int &now)
{
    now=0,if_z=1,Cget=getchar();
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
 
inline void edge_add(int from,int to,int flow)
{
    edge[++cnt].to=from,edge[cnt].next=head[to],edge[cnt].flow=flow,head[to]=cnt;
    edge[++cnt].to=to,edge[cnt].next=head[from],edge[cnt].flow=flow,head[from]=cnt;
}
 
bool search()
{
    memset(deep,0,sizeof(deep));
    queue<int>que;
    que.push(s);
    deep[s]=1;
    while(!que.empty())
    {
        int now=que.front();
        for(int i=head[now];i;i=edge[i].next)
        {
            if(edge[i].flow&&deep[edge[i].to]==0)
            {
                que.push(edge[i].to);
                deep[edge[i].to]=deep[now]+1;
            }
        }
        que.pop();
    }
    if(deep[t]==0) return false;
    else return true;
}
 
int Search(int now,int flow_)
{
    if(now==t) return flow_;
    int pos,Flow=0;
    for(int i=head[now];i;i=edge[i].next)
    {
        if(edge[i].flow&&deep[edge[i].to]==deep[now]+1)
        {
            pos=flow_-Flow;
            pos=Search(edge[i].to,min(pos,edge[i].flow));
            edge[i].flow-=pos;
            edge[i-1].flow+=pos;
            Flow+=pos;
            if(Flow==flow_) return flow_;
        }
    }
    if(Flow==0) deep[now]=0;
    return Flow;
}
 
int main()
{
    read_int(n),read_int(m);
    int pos;
    s=1,t=n*m;
    for(int i=0;i<n;i++)
    {
        for(int j=1;j<m;j++)
        {
            read_int(pos);
            edge_add(i*m+j,i*m+j+1,pos);
        }
    }
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            read_int(pos);
            edge_add((i-1)*m+j,i*m+j,pos);
        }
    }
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<m;j++)
        {
            read_int(pos);
            edge_add((i-1)*m+j,i*m+j+1,pos);
        }
    }
    while(search())
    {
        ans+=Search(s,INF);
    }
    printf("%d\n",ans);
    return 0;
}
