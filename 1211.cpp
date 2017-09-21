#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,cnt[1005],tot;
ll ans=1;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void get(int x,int d)
{
    for(int i=2;i<=n;i++)
        while(x%i==0) x/=i,cnt[i]+=d;
}
int main()
{
    in(n);int tmp;
    for(int i=1;i<=n;i++)
    {
        in(tmp);
        if(tmp==0&&n!=1)
        {
            cout<<0;
            return 0;
        }
        tot+=tmp-1;
        for(int v=2;v<tmp;v++) get(v,-1);
    }
    if(tot!=n-2)
    {
        cout<<0;
        return 0;
    }
    for(int v=2;v<=n-2;v++) get(v,1);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=cnt[i];v++) ans*=i;
    cout<<ans;
    return 0;
}
