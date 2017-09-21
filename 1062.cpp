#include <bits/stdc++.h>
using namespace std;
const int maxn=1000010;
#define lowbit(x) (x&(-x))
struct NodeType
{
    int x,y1,y2;
};
struct NodeType str[maxn];
int q,len,k,t,tree[2][2010][4010];
inline void add(int c,int det)
{
    for(int i=str[c].x+1;i<2010;i+=lowbit(i))
    {
        for(int v=str[c].y1+1;v<4010;v+=lowbit(v)) tree[0][i][v]+=det;
        for(int v=str[c].y2+1;v<4010;v+=lowbit(v)) tree[1][i][v]+=det;
    }
}
inline int sum(int x,int y,int jud)
{
    if(x<0||y<0) return 0;
    x++,y++;
    if(x>2*len) x=(2*len)+1;
    if(y>4*len) y=(4*len)+1;
    int tmp=0;
    for(int i=x;i>0;i-=lowbit(i))
        for(int v=y;v>0;v-=lowbit(v))
            tmp+=tree[jud][i][v];
    return tmp;
}
inline int area(int jud,int x1,int y1,int x2,int y2)
{
    return sum(x2,y2,jud)+sum(x1-1,y1-1,jud)-sum(x1-1,y2,jud)-sum(x2,y1-1,jud);
}
inline int solve(int t,int l,int r)
{
    int d=(r==len);
    return area(0,t,l+t,t+r,4*len)+area(0,0,l+t-2*len,t+r-2*len-d,4*len)+
            area(1,2*len-r+t+d,l-t,2*len,4*len)+area(1,t-r,l-t+2*len,t-1,4*len);
}
int main()
{
    scanf("%d%d",&q,&len);
    while(q--)
    {
        scanf("%d%d",&k,&t);
        if(k==1)
        {
            int l,r,c,d;scanf("%d%d%d%d",&c,&l,&r,&d);
            str[c].x=(t+(2*len)-(l*d))%(2*len);
            str[c].y1=r-l+str[c].x;
            str[c].y2=r-l-str[c].x+(2*len);
            add(c,1);
        }
        else if(k==2)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",solve(t%(2*len),l,r));
        }
        else
        {
            int c;scanf("%d",&c);
            add(c,-1);
        }
    }
    return 0;
}
