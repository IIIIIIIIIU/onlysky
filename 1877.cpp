#include <cstdio>
#include <iostream>
 
using namespace std;
 
struct EdgeType {
    int v,w,f,e;
};
struct EdgeType edge[20005<<4];
 
int n,m,cnt=1,head[205<<4],que[777777],dis[205<<4];
int pre[205<<4],suc[205<<4],ans,ans_;
 
bool if_[205<<4];
 
char Cget;
 
inline void in(int &now)
{
    now=0,Cget=getchar();
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
 
inline void edge_add(int u,int v,int w,int f)
{
    edge[++cnt].v=v,edge[cnt].f=f,edge[cnt].w=w,edge[cnt].e=head[u],head[u]=cnt;
    edge[++cnt].v=u,edge[cnt].f=0,edge[cnt].w=-w,edge[cnt].e=head[v],head[v]=cnt;
}
 
bool spfa()
{
    int h=0,tail=0;
    for(int i=1;i<=n*2;i++)
    {
        pre[i]=-1;
        if_[i]=false;
        dis[i]=0x7ffffff;
    }
    que[tail++]=1,dis[1]=0,if_[1]=true;
    while(h<tail)
    {
        for(int i=head[que[h]];i;i=edge[i].e)
        {
            if(dis[edge[i].v]>dis[que[h]]+edge[i].w&&edge[i].f>0)
            {
                dis[edge[i].v]=dis[que[h]]+edge[i].w;
                pre[edge[i].v]=i;
                if(!if_[edge[i].v])
                {
                    if_[edge[i].v]=true;
                    que[tail++]=edge[i].v;
                }
            }
        }
        if_[que[h++]]=false;
    }
    return dis[n+n]<0x7ffffff;
}
 
int main()
{
    in(n),in(m);int u,v,w;
    edge_add(1,1+n,0,0x7ffffff),edge_add(n,n+n,0,0x7ffffff);
    for(int i=2;i<n;i++) edge_add(i,i+n,0,1);
    for(int i=1;i<=m;i++)
    {
        in(u),in(v),in(w);
        edge_add(u+n,v,w,1);
    }
    while(spfa())
    {
        int pos=n+n,pos_=0x7ffffff;
        while(pre[pos]!=-1)
        {
            pos_=min(pos_,edge[pre[pos]].f);
            pos=edge[pre[pos]^1].v;
        }
        ans_+=pos_;
        pos=n+n;
        while(pre[pos]!=-1)
        {
            ans+=edge[pre[pos]].w*pos_;
            edge[pre[pos]].f-=pos_;
            edge[pre[pos]^1].f+=pos_;
            pos=edge[pre[pos]^1].v;
        }
    }
    cout<<ans_<<' '<<ans;
    return 0;
}
