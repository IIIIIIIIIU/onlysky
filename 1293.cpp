#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 1000005
struct AiType
{
    int pi,ci;
    bool operator<(const AiType pos)const
    {
        return pi<pos.pi;
    }
};
struct AiType ai[maxn];
int cnt,n,k,num[maxn],cur,ans;
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void updata(int now,bool di)
{
    now=ai[now].ci;
    if(di)
    {
        if(!num[now]) cur++;
        num[now]++;
    }
    else
    {
        if(num[now]==1) cur--;
        num[now]--;
    }
}
int main()
{
    in(n),in(k);int op;
    for(int i=1;i<=k;i++)
    {
        in(op);
        for(int v=1;v<=op;v++)
        {
            in(ai[++cnt].pi);
            ai[cnt].ci=i;
        }
    }
    sort(ai+1,ai+cnt+1);
    cur=0,ans=ai[n].pi-ai[1].pi+1;int now=0,last=1,lastp=ai[1].pi;
    for(int i=1;i<=n;i++)
    {
        updata(i,true);
        while(lastp<ai[i].pi-ans+1)
                lastp=ai[last+1].pi,updata(last++,false);
        while(cur>=k)
                ans=min(ai[i].pi-lastp,ans),lastp=ai[last+1].pi,updata(last++,false);
    }
    cout<<ans;
    return 0;
}
