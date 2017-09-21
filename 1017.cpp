#include <bits/stdc++.h>
using namespace std;
#define maxm 20005
#define inf 1000000000
int n,m,cnt,tot,ans,P[55],L[55],M[55],head[55],deg[55];
int f[55][105][2005],g[55][2005],h[55][2005],E[maxm];
int V[maxm],W[maxm],tag;
char ch[5];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void edge_add(int u,int v,int w)
{
    E[++tag]=head[u],V[tag]=v,W[tag]=w,head[u]=tag,deg[v]++;
}
void dp(int x)
{
    if(!head[x])
    {
        L[x]=min(L[x],m/M[x]);
        for(int i=0;i<=L[x];i++)
            for(int v=i;v<=L[x];v++)
                f[x][i][v*M[x]]=(v-i)*P[x];
        return;
    }
    L[x]=inf;
    for(int i=head[x];i;i=E[i])
    {
        dp(V[i]);
        L[x]=min(L[x],L[V[i]]/W[i]);
        M[x]+=W[i]*M[V[i]];
    }
    L[x]=min(L[x],m/M[x]);
    memset(g,-0x3f3f3f3f,sizeof(g));
    g[0][0]=0;
    for(int l=L[x];l>=0;l--)
    {
        int tot=0;
        for(int i=head[x];i;i=E[i])
        {
            tot++;
            for(int v=0;v<=m;v++)
                for(int k=0;k<=v;k++)
                    g[tot][v]=max(g[tot][v],g[tot-1][v-k]+f[V[i]][l*W[i]][k]);
        }
        for(int v=0;v<=l;v++)
            for(int k=0;k<=m;k++)
                f[x][v][k]=max(f[x][v][k],g[tot][k]+P[x]*(l-v));
    }
}
int main()
{
    memset(f,-0x3f3f3f3f,sizeof(f));
    in(n),in(m);int x,u,w;
    for(int i=1;i<=n;i++)
    {
        in(P[i]),scanf("%s",ch);
        if(ch[0]=='A')
        {
            in(x);
            while(x--)
            {
                in(u),in(w);
                edge_add(i,u,w);
            }
        }
        else in(M[i]),in(L[i]);
    }
    for(int q=1;q<=n;q++)
        if(!deg[q])
        {
            dp(q),tot++;
            for(int i=0;i<=m;i++)
                for(int v=0;v<=i;v++)
                    for(int e=0;e<=L[q];e++)
                        h[tot][i]=max(h[tot][i],h[tot-1][v]+f[q][e][i-v]);
        }
    for(int i=0;i<=m;i++)
        ans=max(ans,h[tot][i]);
    printf("%d\n",ans);
    return 0;
}
