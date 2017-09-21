#include <cstdio>
#define lowbit(x) (x&(-x))
int q,n,m,ai[301][301];
short tree[101][301][301];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void add(int c,int x,int y,int d)
{
    int tmp;
    while(y<=m)
    {
        tmp=x;
        while(tmp<=n) tree[c][tmp][y]+=d,tmp+=lowbit(tmp);
        y+=lowbit(y);
    }
}
int query(int c,int sx,int sy,int ex,int ey)
{
    int res=0,tmp;sx--,sy--;
    while(ey)
    {
        tmp=ex;
        while(tmp) res+=tree[c][tmp][ey],tmp-=lowbit(tmp);
        tmp=sx;
        while(tmp) res-=tree[c][tmp][ey],tmp-=lowbit(tmp);
        ey-=lowbit(ey);
    }
    while(sy)
    {
        tmp=ex;
        while(tmp) res-=tree[c][tmp][sy],tmp-=lowbit(tmp);
        tmp=sx;
        while(tmp) res+=tree[c][tmp][sy],tmp-=lowbit(tmp);
        sy-=lowbit(sy);
    }
    return res;
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
        {
            in(ai[i][v]);
            add(ai[i][v],i,v,1);
        }
    in(q);int op,sx,sy,ex,ey,d;
    while(q--)
    {
        in(op);
        if(op==1)
        {
            in(sx),in(sy),in(d);
            add(ai[sx][sy],sx,sy,-1);
            add(d,sx,sy,1);
            ai[sx][sy]=d;
        }
        else
        {
            in(sx),in(ex),in(sy),in(ey),in(d);
            printf("%d\n",query(d,sx,sy,ex,ey));
        }
    }
    return 0;
}
