#include <bits/stdc++.h>
using namespace std;
#define maxn 500005
#define maxm maxn<<1
#define maxtree maxn<<2
int head[maxn],V[maxm],E[maxm],f[maxn],m,n;
int deep[maxn],size[maxn],lar[maxn],stanow[maxn],statype[maxn];
int stafa[maxn],stai[maxn],top[maxn],cnt,id[maxn],stachain[maxn];
int dis[maxn],dis_[maxn],tree[maxn];
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
/*void dfs(int now,int fa)
{
    size[now]=1,deep[now]=deep[fa]+1,f[now]=fa;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs(V[i],now),size[now]+=size[V[i]];
        if(size[V[i]]>size[lar[now]]) lar[now]=V[i];
    }
}*/
void dfs1()
{
    int now=1;stanow[now]=1,stafa[now]=0;
    flag1:
    deep[stanow[now]]=deep[stafa[now]]+1,size[stanow[now]]=1,f[stanow[now]]=stafa[now];
    for(stai[now]=head[stanow[now]];stai[now];stai[now]=E[stai[now]])
    {
        if(V[stai[now]]==stafa[now]) continue;
        now++,stanow[now]=V[stai[now-1]],stafa[now]=stanow[now-1];
        goto flag1;
        flag2:
        size[stanow[now]]+=size[V[stai[now]]];
        if(size[V[stai[now]]]>size[lar[stanow[now]]]) lar[stanow[now]]=V[stai[now]];
    }
    if(now==1) return;
    else
    {
        now--;
        goto flag2;
    }
}
/*
void dfs2(int now,int chain)
{
    top[now]=chain,id[now]=++cnt;
    if(lar[now]) dfs2(lar[now],now);
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==f[now]||V[i]==lar[now]) continue;
        dfs2(V[i],V[i]);
    }
}
*/
void dfs2()
{
    int now=1;stanow[now]=1,stachain[now]=1;
flag1:
    top[stanow[now]]=stachain[now],id[stanow[now]]=++cnt;
    if(lar[stanow[now]])
    {
        now++,stanow[now]=lar[stanow[now-1]],stachain[now]=stachain[now-1],statype[now]=1;
        goto flag1;
flag2:;
    }
    for(stai[now]=head[stanow[now]];stai[now];stai[now]=E[stai[now]])
    {
        if(V[stai[now]]==f[stanow[now]]||V[stai[now]]==lar[stanow[now]]) continue;
        now++,stanow[now]=V[stai[now-1]],stachain[now]=V[stai[now-1]],statype[now]=2;
        goto flag1;
flag3:;
    }
    if(now==1) return;
    else
    {
        now--;
        if(statype[now+1]==1) goto flag2;
        else goto flag3;
    }
}
#define lowbit(x) x&(-x)
int change(int to,int x)
{
    int d=to,tmp=x^dis_[to];
    while(d<=n) tree[d]^=tmp,d+=lowbit(d);
    dis_[to]=x;
}
int Query(int l,int r)
{
    int res=0;l--;
    while(r) res^=tree[r],r-=lowbit(r);
    while(l) res^=tree[l],l-=lowbit(l);
    return res;
}
int query(int x,int y)
{
    int res=0;
    while(top[x]!=top[y])
        if(deep[top[x]]>deep[top[y]]) res^=Query(id[top[x]],id[x]),x=f[top[x]];
        else res^=Query(id[top[y]],id[y]),y=f[top[y]];
    if(deep[x]>deep[y]) swap(x,y);
    return res^Query(id[x],id[y]);
}
int main()
{
    in(n);int u,v;
    for(int i=1;i<=n;i++) in(dis[i]);
    for(int i=1;i<n;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    cnt=0,dfs1(),dfs2();
    for(int i=1;i<=n;i++) change(id[i],dis[i]);
    in(m);char op[3];
    for(int i=1;i<=m;i++)
    {
        scanf("%s",op),in(u),in(v);
        if(op[0]=='C') change(id[u],v);
        else if(query(u,v)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
