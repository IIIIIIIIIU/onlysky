#include <cstdio>
#include <algorithm>

#define maxn 300005

using namespace std;

struct EdgeType {
    int to,next;
};
struct EdgeType edge[maxn<<1];

int if_z,n,m,path[maxn],head[maxn],cnt;
int deep[maxn],size[maxn],top[maxn];
int f[maxn],flag[maxn],tag[maxn];

char Cget;

inline void in(int &now)
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

void search_1(int now,int fa)
{
    int pos=cnt++;
    deep[now]=deep[fa]+1,f[now]=fa;
    for(int i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==fa) continue;
        search_1(edge[i].to,now);
    }
    size[now]=cnt-pos;
}

void search_2(int now,int chain)
{
    int pos=0;
    top[now]=chain;
    for(int i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==f[now]) continue;
        if(size[edge[i].to]>size[pos]) pos=edge[i].to;
    }
    if(pos==0) return ;
    search_2(pos,chain);
    for(int i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==pos||edge[i].to==f[now]) continue;
        search_2(edge[i].to,edge[i].to);
    }
}

void solve(int x,int y)
{
    tag[x]++,tag[y]++;
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]]) swap(x,y);
        x=f[top[x]];
    }
    if(deep[x]>deep[y]) swap(x,y);
    tag[x]--,tag[f[x]]--;
}

void search_3(int now)
{
    for(int i=head[now];i;i=edge[i].next)
    {
        if(edge[i].to==f[now]) continue;
        search_3(edge[i].to),tag[now]+=tag[edge[i].to];
    }
}

int main()
{
    in(n);int u,v;
    for(int i=1;i<=n;i++) in(path[i]);
    for(int i=1;i<n;i++)
    {
        in(u),in(v);
        edge[++cnt].to=v,edge[cnt].next=head[u],head[u]=cnt;
        edge[++cnt].to=u,edge[cnt].next=head[v],head[v]=cnt;
    }
    cnt=0,search_1(1,0),search_2(1,1);
    for(int i=2;i<=n;i++) solve(path[i-1],path[i]);
    search_3(1);
    for(int i=1;i<=n;i++)
    {
        if(i==path[1]) printf("%d\n",tag[i]);
        else printf("%d\n",tag[i]-1);
    }
    return 0;
}
