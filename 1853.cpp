#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
long long int l,r,table[40000],num,ans;
 
void pdfs(long long int now)
{
    if(now>r) return ;
    table[++num]=now;
    pdfs(now*10+6),pdfs(now*10+8);
}
 
void pre()
{
    pdfs(6),pdfs(8);
    sort(table+1,table+num+1);
    long long new_table[40000],new_num=0;
    for(int i=1;i<=num;i++)
    {
        for(int j=1;j<i;j++)
        {
            if(table[j]==0) continue;
            if(table[i]%table[j]==0)
            {
                table[i]=0;
                break;
            }
        }
        if(table[i]) new_table[++new_num]=table[i];
    }
    num=new_num;
    for(int i=1;i<=num;i++) table[num-i+1]=new_table[i];
    return ;
}
 
inline long long int gcd(long long int x,long long int y)
{
    return y?gcd(y,x%y):x;
}
 
void dfs(long long int now,int p,bool lev)
{
    if(now>r) return ;
    if(lev) ans+=r/now,ans-=l/now;
    else ans-=r/now,ans+=l/now;
    for(int i=p;i<=num;i++)
    {
        double pos=now/gcd(now,table[i]);
        if(pos<=r/table[i]) dfs(pos*table[i],i+1,lev^1);
    }
}
 
int main()
{
    cin>>l>>r;
    pre(),l--;
    for(int i=1;i<=num;i++) dfs(table[i],i+1,true);
    cout<<ans;
    return 0;
}
