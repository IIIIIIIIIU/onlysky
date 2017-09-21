#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const real INF=1e9;
const int pi[16]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
int n,pa1[16],pa2[16],out[500005],len;
real lg[16],ans=INF;
void dfs(int now,int Max,int pos,real sum)
{
    if(sum>=ans) return;
    if(pos==1)
    {
        ans=sum;
        for(int i=1;i<=15;i++) pa2[i]=pa1[i];
        return;
    }
    if(now==16) return;
    for(int i=pos;i>=1;i--)
        if(pos%i==0)
        {
            pa1[now]+=i-1;
            dfs(now+1,i,pos/i,sum+lg[now]*(i-1));
            pa1[now]-=i-1;
        }
}
void mul(int x)
{
    long long tmp=0;
    for(int i=1;i<=len;i++) tmp+=out[i]*x,out[i]=tmp%10,tmp/=10;
    while(tmp) out[++len]=tmp%10,tmp/=10;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=15;i++) lg[i]=log2(pi[i]);
    dfs(1,n,n,0);
    out[1]=1,len=1;
    for(int i=1;i<=15;i++)
        for(int v=1;v<=pa2[i];v++) mul(pi[i]);
    for(int i=len;i>=1;i--) putchar(out[i]+'0');
    return 0;
}
