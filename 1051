#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=100050;
const int maxm=500050;
int n,m,du[maxn],dfn[maxn],low[maxn],tag,cnt,num,head[maxn];
int E[maxm],V[maxm],sta[maxn],top,bel[maxn],eu[maxn],ev[maxn];
int size[maxn];
map<int,bool>has;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void dfs(int now)
{
    dfn[now]=low[now]=++tag,sta[++top]=now;
    for(int i=head[now];i;i=E[i])
    {
        if(!dfn[V[i]]) dfs(V[i]),low[now]=min(low[now],low[V[i]]);
        else low[now]=min(low[now],dfn[V[i]]);
    }
    if(low[now]==dfn[now])
    {
        cnt++,size[cnt]++;
        while(sta[top]!=now) bel[sta[top--]]=cnt,size[cnt]++;
        bel[sta[top--]]=cnt;
    }
}
int main()
{
    in(n),in(m);int u,v;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v),eu[i]=u,ev[i]=v;
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
    }
    cnt=0;
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i);
    num=cnt,cnt=0,memset(head,0,sizeof(head));
    int tmp;
    for(int i=1;i<=m;i++)
    {
        u=bel[eu[i]],v=bel[ev[i]];
        if(u==v) continue;
        if(u>v) tmp=v*maxn+u;else tmp=u*maxn+v;
        if(!has[tmp]) du[u]++;
    }
    tmp=0;int pos;
    for(int i=1;i<=num;i++) if(!du[i]) tmp++,pos=i;
    if(tmp==1) printf("%d\n",size[pos]);
    else printf("0");
    return 0;
}
