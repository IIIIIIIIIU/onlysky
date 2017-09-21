#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
int f[maxn][18],n,len[maxn];
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
        now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++) in(f[i][0]);
    for(int i=1,v=2;v<=n;i++,v<<=1)
        for(int k=1;k+v-1<=n;k++)
            f[k][i]=max(f[k][i-1],f[k+(v>>1)][i-1]);
    for(int i=1;i<=n;i++) len[i]=log2(i);
    for(int i=1;i<=n;i++)
    {
        int res=0,l=i+1,r,tmp;
        for(int v=1;true;v++)
        {
            if(r==n) break;
            r=i+v*v,r=min(r,n);
            tmp=len[r-l+1],res=max(res,max(f[r-(1<<tmp)+1][tmp],f[l][tmp])+v);
            l=r+1;
        }
        l=i,r=i-1;
        for(int v=1;true;v++)
        {
            if(l==1) break;
            l=i-v*v,l=max(l,1);
            tmp=len[r-l+1],res=max(res,max(f[r-(1<<tmp)+1][tmp],f[l][tmp])+v);
            r=l-1;
        }
        printf("%d\n",max(0,res-f[i][0]));
    }
    return 0;
}
