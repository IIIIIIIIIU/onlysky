//#include <bits/stdc++.h>
//using namespace std;
#include <cstdio>
const int maxn=1000005;
int n,ai[maxn],cnt[maxn],ans[maxn],Max;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++)
    {
        in(ai[i]),cnt[ai[i]]++;
        if(ai[i]>Max) Max=ai[i];
    }
    for(int i=1,v,now;i<=Max;i++)
    {
        now=cnt[i];
        for(v=i;v<=Max;v+=i) ans[v]+=now;
    }
    for(int i=1;i<=n;i++) printf("%d\n",ans[ai[i]]-1);
    return 0;
}
