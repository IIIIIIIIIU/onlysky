#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int sum[105],ans,n,tmp,step;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&tmp),sum[i]=sum[i-1]+tmp;
    step=sum[n]/2;
    for(int i=1;i<=n;i++)
        if(sum[i]+step>sum[n]) break;
        else
            for(int v=i+1;v<=n;v++) if(sum[v]==step+sum[i]) ans++;
    cout<<ans*(ans-1)/2;
    return 0;
}
