#include <bits/stdc++.h>
using namespace std;
const int maxn=305,maxm=4005;
int head[maxn],E[maxm],V[maxm],cnt,n,m,T,dfn[maxn],bel[maxn],col,low[maxn],tag;
int sta[maxn],top;
char ch[maxn];
void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void read(int &now)
{
    int len=strlen(ch+1);now=0;
    for(int i=2;i<=len;i++)now=now*10+ch[i]-'0';
}
inline void edge_add(int u,int v)
{
    E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
}
void dfs(int now)
{
    dfn[now]=low[now]=++tag,sta[++top]=now;
    for(int i=head[now];i;i=E[i])
        if(!bel[V[i]])
            if(dfn[V[i]]) low[now]=min(low[now],dfn[V[i]]);
            else dfs(V[i]),low[now]=min(low[now],low[V[i]]);
    if(low[now]==dfn[now])
    {
        col++;
        while(sta[top]!=now) bel[sta[top]]=col,top--;
        bel[now]=col,top--;
    }
}
int main()
{
    in(T);
    while(T--)
    {
        in(n),in(m),cnt=tag=0,top=0;
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(bel,0,sizeof(bel));
        memset(head,0,sizeof(head));
        int x,y;
        while(m--)
        {
            scanf("%s",ch+1),read(x),x<<=1;
            if(ch[1]=='h') x|=1;
            scanf("%s",ch+1),read(y),y<<=1;
            if(ch[1]=='h') y|=1;
            edge_add(x^1,y),edge_add(y^1,x);
        }
        for(int i=1;i<=(n<<1|1);i++)
            if(!dfn[i])
                dfs(i);
        bool can=false;
        for(int i=1;i<=n;i++)
            if(bel[i<<1]==bel[i<<1|1])
            {
                can=true;
                break;
            }
        if(can) puts("BAD");
        else puts("GOOD");
    }
    return 0;
}
