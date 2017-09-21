#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const int maxn=50005;
struct line
{
    real k,b;
    int id;
    bool operator<(const line &pos)const
    {
        if(k==pos.k) return b>pos.b;
        return k<pos.k;
    }
    real operator&(const line &pos)const
    {
        return (pos.b-b)/(k-pos.k);
    }
};
struct line li[maxn];
int n,sta[maxn],top;
bool cmp(int a,int b)
{
    return li[a].id<li[b].id;
}
int main()
{
//  freopen("bzoj_1007.in","r",stdin);
//  freopen("bzoj_1007.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf%lf",&li[i].k,&li[i].b),li[i].id=i;
    sort(li+1,li+n+1),sta[++top]=1;
    for(int i=2;i<=n;i++)
    {
        if(li[i].k==li[i-1].k) continue;
        while(top>1&&(li[i]&li[sta[top-1]])<=(li[sta[top-1]]&li[sta[top]])) top--;
        sta[++top]=i;
    }
    sort(sta+1,sta+top+1,cmp);
    for(int i=1;i<=top;i++) printf("%d ",li[sta[i]].id);
    return 0;
}
