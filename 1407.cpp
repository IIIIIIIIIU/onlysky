/**************************************************************
    Problem: 1407
    User: onlysky
    Language: C++
    Result: Accepted
    Time:1020 ms
    Memory:1288 kb
****************************************************************/
 
#include <bits/stdc++.h>
using namespace std;
int n,ci[100],pi[100],li[100],st;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
void exgcd(int a,int b,int &x,int &y)
{
    if(!b)
    {
        x=1,y=0;
        return;
    }
    exgcd(b,a%b,x,y);
    int t=x;x=y;y=t-a/b*y;
}
bool check(int m)
{
    for(int i=1;i<=n;i++)
        for(int v=i+1;v<=n;v++)
        {
            int a=pi[i]-pi[v],b=m,c=ci[v]-ci[i];
            int r=gcd(a,b),x,y;
            if(c%r==0)
            {
                a/=r,b/=r,c/=r;
                exgcd(a,b,x,y);
                b=abs(b);
                x=((x*c)%b+b)%b;
                if(!x) x+=b;
                if(x<=min(li[i],li[v])) return false;
            }
        }
    return true;
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++) in(ci[i]),in(pi[i]),in(li[i]),st=max(ci[i],st);
    for(int i=st;true;i++)
        if(check(i))
        {
            cout<<i;
            return 0;
        }
    return 0;
}
