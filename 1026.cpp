#include <bits/stdc++.h>
using namespace std;
int f[12][10],num[12];
int prepare()
{
    for(int i=0;i<=9;i++) f[1][i]=1;
    for(int i=2;i<=10;i++)
        for(int v=0;v<=9;v++)
            for(int k=0;k<=9;k++)
                if(abs(v-k)>=2) f[i][v]+=f[i-1][k];
}
int get(int x)
{
    if(!x) return 0;
    int top=0,res=0;
    while(x) num[++top]=x%10,x/=10;
    for(int i=top;i;i--)
    {
        if(top-i>=2&&abs(num[i+1]-num[i+2])<=1) break;
        for(int v=0+(i==top);v<num[i]+(i==1);v++)
            if(i==top||abs(v-num[i+1])>=2) res+=f[i][v];
    }
    for(int i=top-1;i;i--)
        for(int v=1;v<=9;v++)
            res+=f[i][v];
    return res;
}
int main()
{
    int a,b;prepare();
    scanf("%d%d",&a,&b);
    cout<<get(b)-get(a-1);
    return 0;
}
