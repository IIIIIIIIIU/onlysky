#include <cstdio>
#include <algorithm>
using namespace std;
typedef double real;
int n;
real ki[12],ai[12][12],bi[12],ans[12];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n+1;i++)
        for(int v=1;v<=n;v++)
            scanf("%lf",&ai[i][v]);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=n;v++)
        {
            bi[i]+=ai[i][v]*ai[i][v]-ai[i+1][v]*ai[i+1][v];
            ai[i][v]=2*(ai[i][v]-ai[i+1][v]);
        }
    for(int i=1;i<=n;i++)
    {
        if(ai[i][i]==0)
            for(int v=i+1;v<=n;v++) if(ai[v][i]) swap(ai[i],ai[v]);
        for(int v=i+1;v<=n;v++)
        {
            real tmp=ai[v][i]/ai[i][i];
            for(int e=i;e<=n;e++)
                ai[v][e]=ai[i][e]*tmp-ai[v][e];
            bi[v]=bi[i]*tmp-bi[v];
        }
    }
    for(int i=n;i>=1;i--)
    {
        for(int v=n;v>i;v--) bi[i]-=ans[v]*ai[i][v];
        ans[i]=bi[i]/ai[i][i];
    }
    printf("%.3lf",ans[1]);
    for(int i=2;i<=n;i++) printf(" %.3lf",ans[i]);
    return 0;
}
