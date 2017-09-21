#include <bits/stdc++.h>
using namespace std;
#define maxn 2005
#define ll long long
struct Int
{
    int len;
    char ai[maxn];
    Int operator+(const Int &pos)const
    {
        Int res;memset(res.ai,0,sizeof(res.ai));
        res.len=max(pos.len,len);ll tmp=0;
        for(int i=1;i<=res.len;i++)
        {
            tmp+=pos.ai[i]+ai[i];
            res.ai[i]=tmp%10,tmp/=10;
        }
        while(tmp) res.ai[++res.len]=(tmp%10),tmp/=10;
        return res;
    }
    Int operator*(const int pos)const
    {
        ll tmp=0;Int res;memset(res.ai,0,sizeof(res.ai)),res.len=len;
        for(int i=1;i<=res.len;i++) tmp+=ai[i]*pos,res.ai[i]=tmp%10,tmp/=10;
        while(tmp) res.ai[++res.len]=tmp%10,tmp/=10;
        return res;
    }
    void print()
    {
        for(int i=len;i;i--) putchar(ai[i]+'0');
    }
};
Int f[205];
int main()
{
    int n;
    scanf("%d",&n);
    if(n==1)
    {
        cout<<0;
        return 0;
    }
    f[0].len=1,memset(f[0].ai,0,sizeof(f[0].ai)),f[0].ai[1]=1;
    f[1].len=1,memset(f[1].ai,0,sizeof(f[1].ai));
    for(int i=2;i<=n;i++) f[i]=(f[i-1]+f[i-2])*(i-1);
    f[n].print();
    return 0;
}
