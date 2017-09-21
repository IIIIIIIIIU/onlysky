#include <iostream>
using namespace std;
typedef long long ll;
ll f[105][105],n,m;
int main()
{
    cin>>m>>n;
    for(int i=1;i<=m;i++) f[1][i]=i*2;
    for(int i=1;i<=n;i++) f[i][1]=2;
    for(int i=2;i<=n;i++)
        for(int v=2;v<=m;v++)
            f[i][v]=f[i][v-1]+f[i-1][v-1];
    cout<<f[n][m];
    return 0;
}
