#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define INF 10228745
typedef double real;
int n;
real x,y,S;
real dfs(real l1,real l2,int now)
{
    if(l1<l2) swap(l1,l2);
    real rate=l1/l2;
    if(now==1) return rate;
    real res=INF;
    for(int i=1;i<now;i++)
        res=min(res,max(dfs(S*i/l2,l2,i),dfs(S*(now-i)/l2,l2,now-i)));
    for(int i=1;i<now;i++)
        res=min(res,max(dfs(S*i/l1,l1,i),dfs(S*(now-i)/l1,l1,now-i)));
    return res;
}
int main()
{
    scanf("%lf%lf%d",&x,&y,&n),S=x*y/n;
    printf("%.6lf\n",dfs(x,y,n));
    return 0;
}
