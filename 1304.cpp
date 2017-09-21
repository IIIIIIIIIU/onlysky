#include <bits/stdc++.h>
using namespace std;
const int maxn=10005;
const int INF=0x3f3f3f3f;
int head[maxn],E[maxn<<1],V[maxn<<1],cnt,col[maxn],val[maxn][2][2];
int fval[maxn][2][2],ans=INF,n,m;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void dfs1(int now,int fa)
{
    if(now<=m)
    {
        if(col[now]) val[now][1][0]=0,val[now][1][1]=1;
        else val[now][0][0]=0,val[now][0][1]=1;
        return;
    }
    int tmp[2][2];memset(tmp,0,sizeof(tmp));
    for(int i=head[now];i;i=E[i])
        if(V[i]!=fa)
        {
            dfs1(V[i],now);
            tmp[0][0]+=min(min(val[V[i]][0][0],val[V[i]][0][1]),val[V[i]][1][1]);
            tmp[0][1]+=min(min(val[V[i]][0][0],val[V[i]][0][1]),val[V[i]][1][1]);
            tmp[1][0]+=min(min(val[V[i]][1][0],val[V[i]][1][1]),val[V[i]][0][1]);
            tmp[1][1]+=min(min(val[V[i]][1][0],val[V[i]][1][1]),val[V[i]][0][1]);
        }
    val[now][0][0]=tmp[0][0],val[now][0][1]=tmp[0][1]+1;
    val[now][1][0]=tmp[1][0],val[now][1][1]=tmp[1][1]+1;
}
void dfs2(int now,int fa)
{
    if(now<=m) return;   
    ans=min(ans,val[now][0][0]+fval[fa][0][1]);
    ans=min(ans,val[now][0][1]+min(min(fval[fa][0][1],fval[fa][0][0]),fval[fa][1][1]));
    ans=min(ans,val[now][1][0]+fval[fa][1][1]);
    ans=min(ans,val[now][1][1]+min(min(fval[fa][1][1],fval[fa][1][0]),fval[fa][0][1]));
    fval[now][1][1]=fval[now][0][1]=1;
    fval[now][0][0]+=min(min(fval[fa][0][0],fval[fa][0][1]),fval[fa][1][1]);
    fval[now][0][1]+=min(min(fval[fa][0][0],fval[fa][0][1]),fval[fa][1][1]);
    fval[now][1][0]+=min(min(fval[fa][1][0],fval[fa][1][1]),fval[fa][0][1]);
    fval[now][1][1]+=min(min(fval[fa][1][0],fval[fa][1][1]),fval[fa][0][1]);
    for(int i=head[now];i;i=E[i])
        if(V[i]!=fa)
        {
            int v=V[i];
            fval[now][0][0]+=min(min(val[v][0][0],val[v][0][1]),val[v][1][1]);
            fval[now][0][1]+=min(min(val[v][0][0],val[v][0][1]),val[v][1][1]);
            fval[now][1][0]+=min(min(val[v][1][0],val[v][1][1]),val[v][0][1]);
            fval[now][1][1]+=min(min(val[v][1][0],val[v][1][1]),val[v][0][1]);
        }
    for(int i=head[now];i;i=E[i])
        if(V[i]!=fa)
        {
            int v=V[i];
            fval[now][0][0]-=min(min(val[v][0][0],val[v][0][1]),val[v][1][1]);
            fval[now][0][1]-=min(min(val[v][0][0],val[v][0][1]),val[v][1][1]);
            fval[now][1][0]-=min(min(val[v][1][0],val[v][1][1]),val[v][0][1]);
            fval[now][1][1]-=min(min(val[v][1][0],val[v][1][1]),val[v][0][1]);
            dfs2(v,now);
            fval[now][0][0]+=min(min(val[v][0][0],val[v][0][1]),val[v][1][1]);
            fval[now][0][1]+=min(min(val[v][0][0],val[v][0][1]),val[v][1][1]);
            fval[now][1][0]+=min(min(val[v][1][0],val[v][1][1]),val[v][0][1]);
            fval[now][1][1]+=min(min(val[v][1][0],val[v][1][1]),val[v][0][1]);
        }
}
int main()
{
    in(n),in(m);
    memset(val,127/3,sizeof(val));
    for(int i=1;i<=m;i++) in(col[i]);
    int u,v;
    for(int i=1;i<n;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    fval[0][0][1]=fval[0][1][1]=1;
    dfs1(n,0),dfs2(n,0);
    cout<<ans;
    return 0;
}
