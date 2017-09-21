#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
struct NumberType {
    int len;
     
    int ai[101];
     
    void print()
    {
        for(int i=len;i>0;i--) putchar(ai[i]+'0');
    }
     
    void mul(NumberType a)
    {
        len=a.len;
        for(int i=a.len;i>0;i--) ai[i]=a.ai[i]*3;
        for(int i=1;i<=a.len;i++) ai[i+1]+=ai[i]/10,ai[i]%=10;
        while(ai[len+1]) len++;
    }
     
    void minus(NumberType a)
    {
        for(int i=1;i<=len;i++)
        {
            if(ai[i]<a.ai[i]) ai[i]+=10,ai[i+1]--;
            ai[i]-=a.ai[i];
        }
        while(!ai[len]) len--;
    }
     
    void updata()
    {
        ai[1]+=2;
        for(int i=1;i<=len;i++)
        {
            if(ai[i]>9) ai[i]-=10,ai[i+1]+=1;
            else break;
        }
        while(ai[len+1]) len++;
    }
};
struct NumberType dp[106];
 
int n;
 
int main()
{
    scanf("%d",&n);
    dp[0].len=1,dp[1].len=1,dp[1].ai[1]=1;
    for(int i=2;i<=n;i++) dp[i].mul(dp[i-1]),dp[i].minus(dp[i-2]),dp[i].updata();
    dp[n].print();
    return 0;
}
