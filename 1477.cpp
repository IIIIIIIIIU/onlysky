#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
 
using namespace std;
 
long long n,m,a1,b1,l,xx,yy;
 
long long exgcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    long long r=exgcd(b,a%b,x,y),tmp=x;
    x=y,y=tmp-a/b*y;
    return r;
}
 
int main()
{
    scanf("%lld%lld%lld%lld%lld",&a1,&b1,&m,&n,&l);
    long long a=m-n,b=l,c=b1-a1;
    if(a<0) a=-a,c=-c;
    long long r=exgcd(a,b,xx,yy);
    if(c/r*r==c)
    {
        xx=xx*c/r,l=l/r;
        if(xx>0) xx=xx%l;
        else xx=xx%l+l;
        cout<<xx;
    }
    else cout<<"Impossible";
    return 0;
}
