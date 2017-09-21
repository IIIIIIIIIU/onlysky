#include <bits/stdc++.h>
using namespace std;
#define maxn 1005
int num[maxn],n,m,bi[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
bool check()
{
    for(int i=1;i<=n;i++)
        if(num[i]>=2)
        {
            for(int v=1;v<=n+2;v++) bi[v]=num[v];
            bi[i]-=2;int tmp=0,pos=1;
            for(int v=1;v<=n+2;v++)
            {   
                if(bi[v]<0)
                {
                    pos=0;
                    break;
                }
                bi[v]%=3;
                bi[v+1]-=bi[v],bi[v+2]-=bi[v];
            }
            if(bi[n+1]<0||bi[n+2]<0) pos=0;
            if(pos) return true;
        }
    return false;
}
int main()
{
    in(n),in(m);int pos;
    for(int i=1;i<=m*3+1;i++) in(pos),num[pos]++;
    pos=1;
    for(int i=1;i<=n;i++)
    {
        num[i]++;
        if(check())
        {
            if(pos) printf("%d",i),pos=0;
            else printf(" %d",i);
        }
        num[i]--;
    }
    if(pos) cout<<"NO";
    return 0;
}
