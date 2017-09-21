#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const int maxn=101,maxk=1<<16;
int n,k,pi[maxn],ci[maxn];
real dp[maxn][maxk];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1,t;i<=k;i++)
    {
        scanf("%d%d",&ci[i],&t);
        for(;t;scanf("%d",&t)) pi[i]|=1<<t-1;
    }
    int all=(1<<k)-1;
    for(int i=n;i;i--)
    {
        for(int v=0;v<=all;v++)
        {
            for(int h=1;h<=k;h++)
            {
                if((pi[h]&v)==pi[h])
                    dp[i][v]+=max(dp[i+1][v],dp[i+1][v|(1<<h-1)]+ci[h]);
                else
                    dp[i][v]+=dp[i+1][v];
            }
            dp[i][v]/=(real)k;
        }
    }
    printf("%.6lf\n",dp[1][0]);
    return 0;
}
