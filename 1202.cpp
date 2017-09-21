#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
int n,m,f[maxn],c[maxn];
inline void in(int &now)
{
    char Cget;now=0;int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}
int find(int x)
{
    if(x==f[x]) return x;
    int tmp=find(f[x]);
    c[x]+=c[f[x]],f[x]=tmp;
    return tmp;
}
int main()
{
    int T;in(T);
    while(T--)
    {
        in(n),in(m);int x,y,z,tag=0;
        for(int i=0;i<=n;i++) f[i]=i,c[i]=0;
        while(m--)
        {
            in(x),in(y),in(z),x--;
            if(find(x)!=find(y))
            {
                c[f[x]]=c[y]-c[x]-z;
                f[f[x]]=f[y];
            }
            else if(c[y]-c[x]!=z)
                tag=true;
        }
        if(tag) puts("false");
        else puts("true");
    }
    return 0;
}
