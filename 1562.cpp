#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=1000000000;
int n,d[10005],lk[10005],ans[10005];
bool vis[10005];
vector<int>e[10005];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int dis(int x,int y)
{
    return min(abs(x-y),n-abs(x-y));
}
bool find(int x)
{
    for(int i=0;i<e[x].size();i++)
        if(!vis[e[x][i]])
        {
            vis[e[x][i]]=1;
            if(!lk[e[x][i]]||find(lk[e[x][i]]))
            {
                lk[e[x][i]]=x;
                return 1;
            }
        }
    return 0;
}
int main()
{
    in(n);
    for(int i=0;i<n;i++) in(d[i]);
    for(int i=0;i<n;i++)
    {
        int x=i+d[i],y=i-d[i]+n;
        x%=n,y%=n;
        if(dis(x,i)!=d[i]) x=-1;
        if(dis(y,i)!=d[i]) y=-1;
        if(x>y) swap(x,y);
        if(x!=-1) e[i].push_back(x);
        if(y!=-1) e[i].push_back(y);
    }
    for(int i=n-1;i>=0;i--)
    {
        memset(vis,0,sizeof(vis));
        if(!find(i))
        {
            puts("No Answer");
            return 0;
        }
    }
    for(int i=0;i<n;i++) ans[lk[i]]=i;
    for(int i=0;i<n-1;i++) printf("%d ",ans[i]);
    printf("%d\n",ans[n-1]);
    return 0;
}
