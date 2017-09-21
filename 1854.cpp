#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define maxn 100005
 
using namespace std;
 
int n,f[maxn];
 
bool if_[maxn];
 
char Cget;
 
inline void in(int &now)
{
    now=0,Cget=getchar();
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    return ;
}
 
int find(int x)
{
    if(x==f[x]) return x;
    f[x]=find(f[x]);
    return f[x];
}
 
int main()
{
//  freopen("game.in","r",stdin);
//  freopen("game.out","w",stdout);
    in(n);int x,y;
    for(int i=1;i<=10000;i++) f[i]=i;
    for(int i=1;i<=n;i++)
    {
        in(x),in(y);
        x=find(x),y=find(y);
        if(x==y) if_[x]=true;
        else
        {
            if(x>y) swap(x,y);
            f[x]=y;
            if_[x]=true;
        }
    }
    for(int i=1;i<=10001;i++)
    {
        if(!if_[i])
        {
            printf("%d\n",i-1);
            break;
        }
    }
    return 0;
//  fclose(stdin);
//  fclose(stdout);
}
