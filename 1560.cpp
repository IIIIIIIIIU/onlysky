#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct point
{
    int x,y,v;
    bool operator<(const point &pos)const
    {
        if(y==pos.y) return x<pos.x;
        return y<pos.y;
    }
};
struct point ai[200005],ci[1005];
int n,m;
ll last[1005];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++) in(ai[i].x),in(ai[i].y),in(ai[i].v);
    sort(ai+1,ai+n+1);
    ci[1]=ai[1],last[1]=ai[1].v;
    ll tmp;
    for(int i=2,v;i<=n;i++)
    {
        tmp=-1e13;
        for(v=1;v<=ai[i].x;v++)
            if(ci[v].y!=0)
                tmp=max(tmp,ai[i].v+last[v]-(ai[i].x-ci[v].x)*(ai[i].x-ci[v].x)-(ai[i].y-ci[v].y)*(ai[i].y-ci[v].y));
        ci[ai[i].x]=ai[i],last[ai[i].x]=tmp;
    }
    cout<<last[m];
    return 0;
}
