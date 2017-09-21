#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=50005;
struct node
{
    int x,y;
    bool operator<(const node &pos)const
    {
        if(x==pos.x) return y<pos.y;
        return x<pos.x;
    }
};
struct node ai[maxn];
int n,tot,que[maxn],cnt;
ll x[maxn],y[maxn],f[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
//  freopen("data.txt","r",stdin);
    in(n);
    for(int i=1;i<=n;i++) in(ai[i].x),in(ai[i].y);
    sort(ai+1,ai+n+1);
    for(int i=1;i<=n;i++)
    {
        while(cnt&&ai[i].y>y[cnt]) cnt--;
        x[++cnt]=ai[i].x,y[cnt]=ai[i].y;
    }
    int h=0,tail=0;
    for(int i=1;i<=cnt;i++)
    {
        while(h<tail&&f[que[h+1]]-f[que[h]]<=x[i]*(y[que[h]+1]-y[que[h+1]+1])) ++h;
        f[i]=f[que[h]]+y[que[h]+1]*x[i];
        while(h<tail&&(f[i]-f[que[tail]])*(y[que[tail-1]+1]-y[que[tail]+1])<=
            (f[que[tail]]-f[que[tail-1]])*(y[que[tail]+1]-y[i+1])) --tail;
        que[++tail]=i;
    }
    cout<<f[cnt];
    return 0;
}
