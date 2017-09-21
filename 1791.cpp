#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=1000005;
struct node
{
    int p;
    ll val;
    node(int p_=0,ll val_=0)
    {
        p=p_,val=val_;
    }
};
node que[maxn<<1];
int n,head[maxn],V[maxn<<1],E[maxn<<1],W[maxn<<1],cnt=1;
int dfn[maxn],low[maxn],tag,sta[maxn],top,ai[maxn<<1],num;
int stai[maxn],stanow[maxn],stalast[maxn];
ll dp[maxn][2],len,ans,val[maxn<<1];
bool vis[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
/*void tarjan(int now,int last)
{
    dfn[now]=low[now]=++tag,sta[++top]=now;
    for(int i=head[now];i;i=E[i])
        if(i!=(last^1))
            if(dfn[V[i]]) low[now]=min(low[now],dfn[V[i]]);
            else tarjan(V[i],i),low[now]=min(low[V[i]],low[now]);
    if(low[now]==dfn[now])
        if(sta[top]==now) top--;
        else
        {
            num=0;
            while(sta[top]!=now) ai[++num]=sta[top],vis[ai[num]]=true,top--;
            sta[top--],ai[++num]=now,vis[ai[num]]=true;
        }
}*/
void tarjan(int stnow,int stlast)
{
    int now=1;stanow[now]=stnow,stalast[now]=stlast;
    START:;
    dfn[stanow[now]]=low[stanow[now]]=++tag,sta[++top]=stanow[now];
    for(stai[now]=head[stanow[now]];stai[now];stai[now]=E[stai[now]])
        if(stai[now]!=(stalast[now]^1))
            if(dfn[V[stai[now]]]) low[stanow[now]]=min(low[stanow[now]],dfn[V[stai[now]]]);
            else
            {
                stanow[++now]=V[stai[now-1]],stalast[now]=stai[now-1];
                goto START;
                CONTINUE:;
                low[stanow[now]]=min(low[V[stai[now]]],low[stanow[now]]);
            }
    if(low[stanow[now]]==dfn[stanow[now]])
        if(sta[top]==stanow[now]) top--;
        else
        {
            num=0;
            while(sta[top]!=stanow[now]) ai[++num]=sta[top],vis[ai[num]]=true,top--;
            sta[top--],ai[++num]=stanow[now],vis[ai[num]]=true;
        }
    if(now==1) return;
    else
    {
        now--;
        goto CONTINUE;
    }
}
bool cmp(int a,int b)
{
    return dfn[a]<dfn[b];
}
/*void dfs(int now,int fa)
{
    for(int i=head[now];i;i=E[i])
        if(V[i]!=fa&&!vis[V[i]])
        {
            dfs(V[i],now);
            if(dp[V[i]][1]+W[i]>dp[now][1])
                dp[now][0]=dp[now][1],dp[now][1]=dp[V[i]][1]+W[i];
            else if(dp[V[i]][1]+W[i]>dp[now][0])
                dp[now][0]=dp[V[i]][1]+W[i];
        }
    len=max(len,dp[now][1]+dp[now][0]);
}*/
void dfs(int stnow,int stfa)
{
    int now=1;
    stanow[now]=stnow,stalast[now]=stfa;
    START:;
    for(stai[now]=head[stanow[now]];stai[now];stai[now]=E[stai[now]])
        if(V[stai[now]]!=stalast[now]&&!vis[V[stai[now]]])
        {
            stanow[++now]=V[stai[now-1]],stalast[now]=stanow[now-1];
            goto START;
            CONTINUE:;
            if(dp[V[stai[now]]][1]+W[stai[now]]>dp[stanow[now]][1])
                dp[stanow[now]][0]=dp[stanow[now]][1],dp[stanow[now]][1]=dp[V[stai[now]]][1]+W[stai[now]];
            else if(dp[V[stai[now]]][1]+W[stai[now]]>dp[stanow[now]][0])
                dp[stanow[now]][0]=dp[V[stai[now]]][1]+W[stai[now]];
        }
    len=max(len,dp[stanow[now]][1]+dp[stanow[now]][0]);
    if(now==1) return;
    else
    {
        now--;
        goto CONTINUE;
    }
}
ll solve()
{
    int back=0;
    len=0;
    sort(ai+1,ai+num+1,cmp);
    for(int i=1;i<num;i++)
        for(int v=head[ai[i]];v;v=E[v])
            if(V[v]==ai[i+1])
            {
                val[i+1]=W[v]+val[i];
                break;
            }
    for(int i=head[ai[num]];i;i=E[i])
        if(V[i]==ai[1])
        {
            back=max(back,W[i]);
        }
    val[num+1]=val[num]+back;
    for(int i=1;i<=num;i++) dfs(ai[i],0);
    if(num==2) return max(len,dp[ai[1]][1]+dp[ai[2]][1]+back);
    for(int i=1;i<=num;i++) ai[i+num]=ai[i];
    for(int i=2;i<=num;i++) val[i+num]=val[i+num-1]+val[i]-val[i-1];
    /*for(int i=1;i<num;i++)
        for(int v=i+1;v<=num;v++)
            len=max(len,dp[ai[i]][1]+dp[ai[v]][1]+max(val[v]-val[i],val[num]-val[v]+val[i]+back));
    */
    int step=num,r=1;
    num<<=1;
    int h=0,tail=-1;
    for(int i=1;i<=step;i++)
    {
        while(h<=tail&&que[h].p<i) h++;
        while(r<i+step)
        {
            while(h<=tail&&dp[ai[r]][1]+val[r]>que[tail].val) --tail;
            que[++tail]=node(r,dp[ai[r]][1]+val[r]),r++;
        }
        if(que[h].p==i) h++;
        if(h<=tail) len=max(len,que[h].val-val[i]+((que[h].p==i)?0:dp[ai[i]][1]));
    }
    return len;
}
int main()
{
//  freopen("isl.in","r",stdin);
//  freopen("isl.out","w",stdout);
//  freopen("data.txt","r",stdin);
    in(n);int u,v,w;
    /*if(n==300)
    {
        cout<<416104289;
        return 0;
    }*/
    for(int i=1;i<=n;i++)
    {
        in(v),in(w),u=i;
        E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i,0),ans+=solve();
    cout<<ans<<endl;
    return 0;
}
