#include <cstdio>
const int maxn=25,maxm=110;
int n,m,i,e,x,y,z,A,B,T,g[maxn],v[maxm],w[maxm],nxt[maxm],ed;
struct P
{
    int x,y,h,v;
}a[maxn];
int getid(int x)
{
    for(int i=1;i<=n;i++)
        if(a[i].x==x) return i;
}
void add(int x,int y,int z)
{
    v[++ed]=y,w[ed]=z,nxt[ed]=g[x],g[x]=ed;
    v[++ed]=x,w[ed]=z,nxt[ed]=g[y],g[y]=ed;
}
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].h);
        a[i].h+=a[i].y,a[i].v=(i==1);
    }
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d%d%d",&x,&y,&z);
        add(getid(x-1),getid(x+z),y);
    }
    scanf("%d%d",&A,&B);
    while(1)
    {
        for(x=1;x;)
            for(x=0,i=1;i<=n;i++)
                if(a[i].v)
                    for(e=g[i];e;e=nxt[e])
                        if(a[i].h<=w[e]&&!a[v[e]].v)
                            a[v[e]].v=x=1;
        for(m=0,i=1;i<=n;i++)
            if(a[i].v&&a[i].h>m) m=a[i].h;
        if(a[A].v&&m==B) return printf("%d",T),0;
        for(i=1;i<=n;i++)
            if(a[i].v&&a[i].y==a[i].h&&a[i].y==m)
                return puts("-1"),0;
        for(i=1;i<=n;i++)
            if(a[i].v&&a[i].h==m) a[i].h--,T++;
    }
    return 0;
}
