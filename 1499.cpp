#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
struct node
{
    int val,p;
    node(int val_=0,int p_=0)
    {
        val=val_,p=p_;
    }
};
struct node que[100005];
int n,m,sx,sy,k,dp[205][205][205],ans=0;
char ch[205][205];
int main()
{
    scanf("%d%d%d%d%d",&n,&m,&sx,&sy,&k);
    for(int i=1;i<=n;i++)
        scanf("%s",ch[i]+1);
    memset(dp,-127/3,sizeof(dp));
    dp[0][sx][sy]=0;
    int s,t,dir,len;
    for(int r=1;r<=k;r++)
    {
        scanf("%d%d%d",&s,&t,&dir),len=t-s+1;
        if(dir==1)
        {
            for(int i=1;i<=m;i++)
            {
                int h=0,tail=-1,tmp;
                for(int v=n;v>=1;v--)
                {
                    if(ch[v][i]=='x')
                    {
                        h=0,tail=-1;
                        continue;
                    }
                    while(tail>=h&&que[h].p>v+len) ++h;
                    tmp=dp[r-1][v][i]-(n-v+1);
                    while(tail>=h&&que[tail].val<=tmp) --tail;
                    que[++tail]=node(tmp,v);
                    dp[r][v][i]=que[h].val+(n-v+1);
                }
            }
        }
        if(dir==2)
        {
            for(int i=1;i<=m;i++)
            {
                int h=0,tail=-1,tmp;
                for(int v=1;v<=n;v++)
                {
                    if(ch[v][i]=='x')
                    {
                        h=0,tail=-1;
                        continue;
                    }
                    while(tail>=h&&que[h].p<v-len) ++h;
                    tmp=dp[r-1][v][i]-v;
                    while(tail>=h&&que[tail].val<=tmp) --tail;
                    que[++tail]=node(tmp,v);
                    dp[r][v][i]=que[h].val+v;
                }
            }
        }
        if(dir==3)
        {
            for(int i=1;i<=n;i++)
            {
                int h=0,tail=-1,tmp;
                for(int v=m;v>=1;v--)
                {
                    if(ch[i][v]=='x')
                    {
                        h=0,tail=-1;
                        continue;
                    }
                    while(tail>=h&&que[h].p>v+len) ++h;
                    tmp=dp[r-1][i][v]-(m-v+1);
                    while(tail>=h&&que[tail].val<=tmp) --tail;
                    que[++tail]=node(tmp,v);
                    dp[r][i][v]=que[h].val+(m-v+1);
                }
            }
        }
        if(dir==4)
        {
            for(int i=1;i<=n;i++)
            {
                int h=0,tail=-1,tmp;
                for(int v=1;v<=m;v++)
                {
                    if(ch[i][v]=='x')
                    {
                        h=0,tail=-1;
                        continue;
                    }
                    while(tail>=h&&que[h].p<v-len) ++h;
                    tmp=dp[r-1][i][v]-v;
                    while(tail>=h&&que[tail].val<=tmp) --tail;
                    que[++tail]=node(tmp,v);
                    dp[r][i][v]=que[h].val+v;
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++) ans=max(ans,dp[k][i][v]);
    cout<<ans;
    return 0;
}
