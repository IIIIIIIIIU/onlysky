#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 3005
#define ll long long
ll s[maxn],q[maxn],f[maxn][maxn];
bool getx(int i,int x1,int x2,int x3)
{
    return (-s[x2]*s[x2]-f[i-1][x2]+s[x1]*s[x1]+f[i-1][x1])*
    (2*s[x2]-2*s[x3])>(-s[x3]*s[x3]-f[i-1][x3]+s[x2]*s[x2]+
    f[i-1][x2])*(2*s[x1]-2*s[x2]);
}
ll getans(int i,int v,int k)
{
    return -2*s[v]*s[k]+s[k]*s[k]+f[i-1][k]+s[v]*s[v];
}
int main()
{
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&s[i]),s[i]+=s[i-1];
    memset(f,127,sizeof(f)),f[0][0]=0;
    for(int i=1;i<=m;i++)
    {
        int head=0,tail=1;
        for(int v=1;v<=n;v++)
        {
            while(head+2<=tail&&getx(i,q[tail-2],q[tail-1],q[tail]))
                q[tail-1]=q[tail],tail--;
            while(head<tail&&getans(i,v,q[head])>=getans(i,v,q[head+1])) head++;
            f[i][v]=getans(i,v,q[head]),q[++tail]=v;
        }
    }
    printf("%lld\n",f[m][n]*m-s[n]*s[n]);
    return 0;
}
