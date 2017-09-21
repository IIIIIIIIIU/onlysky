#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const int INF=1e8;
const int maxn=505;
const int maxm=5005;
struct EdgeType
{
    int u,v,w;
    bool operator<(const EdgeType pos)const
    {
        return w<pos.w;
    }
};
struct EdgeType e[maxm];
int f[maxn],n,m,down,up,s,t;
real ans=INF;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
int find(int x)
{
    if(x==f[x]) return x;
    return f[x]=find(f[x]);
}
int gcd(int x,int y)
{
    if(!y) return x;
    return gcd(y,x%y);
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=m;i++) in(e[i].u),in(e[i].v),in(e[i].w);
    sort(e+1,e+m+1),in(s),in(t);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        for(int v=1;v<=n;v++) f[v]=v;
        for(int v=i;v<=m;v++)
        {
            x=e[v].u,y=e[v].v;
            x=find(x),y=find(y);
            if(x!=y) f[x]=f[y];
            if(find(s)==find(t))
            {
                real tmp=(real)e[v].w/e[i].w;
                if(tmp<ans) ans=tmp,up=e[v].w,down=e[i].w;
                break;
            }
        }
    }
    if(ans==INF)
    {
        printf("IMPOSSIBLE");
        return 0;
    }
    int p=gcd(up,down);
    up/=p,down/=p;
    if(down!=1) printf("%d/%d",up,down);
    else printf("%d",up);
    return 0;
}
