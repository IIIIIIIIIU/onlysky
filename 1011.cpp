#include <cmath>
#include <cstdio>
using namespace std;
#define maxn 100005
typedef double real;
int n;
real mi[maxn],sum[maxn],ans[maxn];
int main()
{
    real a;
    scanf("%d%lf",&n,&a);
    int lit=100;
    for(int i=1;i<=n;i++)
    {
        scanf("%lf",&mi[i]);
        sum[i]=sum[i-1]+mi[i];
        int pos=floor(i*a);
        if(pos)
        {
            int v=1,r,mid;
            while(pos-v>=lit)
            {
                r=v+lit-1;
                mid=v+r>>1;
                ans[i]+=(sum[r]-sum[v-1])*mi[i]/(i-mid);
                v+=lit;
            }
            while(v<=pos) ans[i]+=mi[v]*mi[i]/(i-v),v++;
        }
    }
    for(int i=1;i<=n;i++) printf("%lf\n",ans[i]);
    return 0;
}
