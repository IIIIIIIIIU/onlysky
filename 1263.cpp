#include <bits/stdc++.h>
using namespace std;
int n,ti,out[5005],len;
int main()
{
    cin>>n;len=1;
    if(n%3==0) out[1]=1,ti=n/3;
    if(n%3==1) out[1]=4,ti=n/3-1;
    if(n%3==2) out[1]=2,ti=n/3;
    while(ti--)
    {
        long long tmp=0;
        for(int i=1;i<=len;i++) tmp+=out[i]*3,out[i]=tmp%10,tmp/=10;
        while(tmp) out[++len]=tmp%10,tmp/=10;
    }
    printf("%d\n",len);
    for(int i=1;i<=min(len,100);i++) printf("%d",out[len-i+1]);
    return 0;
}
