#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1005;
int n,ai[maxn],pi[maxn*20],cnt,ans1[maxn*20],ans2[maxn*20],tot,t,d;
bool vis[maxn*20];
struct Bint
{
    int num[maxn*20],len;
    Bint()
    {
        memset(num,0,sizeof(num));
        len=1,num[1]=1;
    }
    void operator*=(const int pos)
    {
        ll tmp=0;
        for(int i=1;i<=len;i++) tmp+=pos*num[i],num[i]=tmp%10,tmp/=10;
        while(tmp) num[++len]=tmp%10,tmp/=10;
    }
} up,down;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void getans1(int x)
{
    for(int i=1;i<=cnt;i++)
        while(x%pi[i]==0)
            x/=pi[i],ans1[i]++;
}
void getans2(int x)
{
    for(int i=1;i<=cnt;i++)
        while(x%pi[i]==0)
            x/=pi[i],ans2[i]++;
}
int main()
{
    in(t),in(n),in(d);
    for(int i=1;i<=t;i++) in(ai[i]),tot+=ai[i];
    for(int i=2;i<maxn*20;i++)
    {
        if(!vis[i]) pi[++cnt]=i;
        for(int j=1;j<=cnt;j++)
        {
            if(pi[j]*i>=maxn*20) continue;
            vis[pi[j]*i]=true;
            if(i%pi[j]==0) break;
        }
    }
    int x,y;
    while(n--)
    {
        in(x),in(y);
        if(ai[y]==0)
        {
            puts("0/1");
            return 0;
        }
        getans1(ai[y]);
        getans2(tot);
        ai[y]+=d,tot+=d;
    }
    for(int i=1;i<=cnt;i++)
    {
        int tmp=min(ans1[i],ans2[i]);
        ans1[i]-=tmp;
        ans2[i]-=tmp;
        while(ans1[i]--) up*=pi[i];
        while(ans2[i]--) down*=pi[i];
    }
    for(int i=up.len;i>0;i--) putchar(up.num[i]+'0');
    putchar('/');
    for(int i=down.len;i>0;i--) putchar(down.num[i]+'0');
    return 0;
}
