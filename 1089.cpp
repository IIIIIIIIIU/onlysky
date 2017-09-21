#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
struct vlint
{
    int len,num[5005];
    void mem()
    {
        len=0;
        memset(num,0,sizeof(num));
    }
    vlint operator*(const vlint pos)const
    {
        vlint res;res.mem();
        for(int i=1;i<=len;i++)
            for(int v=1;v<=pos.len;v++) res.num[v+i-1]+=num[i]*pos.num[v];
        ll tmp=0;res.len=pos.len+len-1;
        for(int i=1;i<=res.len;i++) tmp+=res.num[i],res.num[i]=tmp%10,tmp/=10;
        while(tmp) res.num[++res.len]=tmp%10,tmp/=10;
        return res;
    }
    void add()
    {
        int tmp=1;
        for(int i=1;i<=len;i++) tmp+=num[i],num[i]=tmp%10,tmp/=10;
        while(tmp) num[++len]=tmp%10,tmp/=10;
    }
    vlint operator-(const vlint pos)const
    {
        vlint res;res.mem();ll tmp=0,cur=0;
        res.len=len;
        for(int i=1;i<=res.len;i++)
        {
            tmp=num[i]-cur,cur=0;
            if(tmp<pos.num[i]) cur++,tmp+=10;
            res.num[i]=tmp-pos.num[i];
        }
        res.len=len;
        while(!res.num[res.len]&&res.len>1) res.len--;
        return res;
    }
    void print()
    {
        for(int i=len;i;i--) putchar('0'+num[i]);
    }
};
vlint dp[17];
int n,d;
vlint poww(int k)
{
    int mi=n-1;vlint res=dp[k],pos=dp[k];
    while(mi)
    {
        if(mi&1) res=res*pos;
        mi>>=1,pos=pos*pos;
    }
    return res;
}
int main()
{
    scanf("%d%d",&n,&d);
    if(d==0)
    {
        cout<<1;
        return 0;
    }
    dp[0].mem(),dp[0].len=1,dp[0].num[1]=1;
    for(int i=1;i<=d;i++)
        dp[i]=poww(i-1),dp[i].add();
    dp[d]=dp[d]-dp[d-1];
    dp[d].print();
    return 0;
}
