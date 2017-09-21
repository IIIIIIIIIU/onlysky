#include <bits/stdc++.h>
using namespace std;
#define maxn 10005
#define maxm 100005
int n,m,s,t,k,head[maxn],E[maxm],V[maxm],W[maxm];
int dis[maxn][11],cnt;
bool vis[maxn][11];
queue<int>q1,qt;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(m),in(k),in(s),in(t);
    int u,v,w;
    for(int i=1;i<=m;++i)
    {
        in(u),in(v),in(w);
        E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
    }
    memset(dis,127/3,sizeof(dis));
    dis[s][0]=0,vis[s][0]=true;q1.push(s),qt.push(0);
    int now,nowt;
    while(!q1.empty())
    {
        now=q1.front(),nowt=qt.front(),q1.pop(),qt.pop();
        vis[now][nowt]=false;
        for(int i=head[now];i;i=E[i])
        {
            if(dis[V[i]][nowt]>dis[now][nowt]+W[i])
            {
                dis[V[i]][nowt]=dis[now][nowt]+W[i];
                if(!vis[V[i]][nowt]) vis[V[i]][nowt]=true,q1.push(V[i]),qt.push(nowt);
            }
            if(nowt<k)
            {
                if(dis[V[i]][nowt+1]>dis[now][nowt])
                {
                    dis[V[i]][nowt+1]=dis[now][nowt];
                    if(!vis[V[i]][nowt+1]) vis[V[i]][nowt+1]=true,q1.push(V[i]),qt.push(nowt+1);
                }
            }
        }
    }
    cout<<dis[t][k];
    return 0;
}
