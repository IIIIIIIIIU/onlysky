#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,ans;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int sg(int x,int y)
{
    if(x&y&1) return 0;
    ll i;int cnt;
    for(i=2,cnt=0;;i<<=1,cnt++)
        if((x%i<=i/2)&&(y%i<=i/2)&&(x%i)&&(y%i)) return cnt;
}
int main()
{
    int T;in(T);
    while(T--)
    {
        ans=0;
        in(n);int pos,pos2;
        for(int i=1;i<=(n>>1);i++)
        {
            in(pos),in(pos2);
            ans^=sg(pos,pos2);
        }
        if(ans) puts("YES");
        else puts("NO");
    }
    return 0;
}
