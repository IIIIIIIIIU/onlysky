#include <bits/stdc++.h>
using namespace std;
int ans,ti[12][40],can[15][121],n,m,l[17],r[17],val[17];
int bit[11],num[17],pi[17][100],need[17];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
inline int get(int x)
{
    int res=0;
    while(x) res+=x&1,x>>=1;
    return res;
}
void dfs(int now,int vall)
{
    ans=max(ans,vall);
    if(now==m+1) return;
    bool tag;int tmp;
    for(int i=(1<<need[now])-1;i<=(1<<num[now])-1;i++)
        if(get(i)==need[now])
        {
            tag=true;
            for(int v=1;v<=num[now];v++)
                if((i&bit[v])==bit[v])
                {
                    tmp=pi[now][v];
                    for(int e=l[now];e<=r[now];e++)
                    {
                        if(ti[tmp][e])
                        {
                            tag=false;
                            break;
                        }
                    }
                    if(!tag) break;
                }
            if(tag)
            {
                for(int v=1;v<=num[now];v++)
                    if((i&bit[v])==bit[v])
                    {
                        tmp=pi[now][v];
                        for(int e=l[now];e<=r[now];e++) ti[tmp][e]=true;
                    }
                dfs(now+1,vall+val[now]);
                for(int v=1;v<=num[now];v++)
                    if((i&bit[v])==bit[v])
                    {
                        tmp=pi[now][v];
                        for(int e=l[now];e<=r[now];e++) ti[tmp][e]=false;
                    }
            }
        }
    dfs(now+1,vall);
}
int main()
{
    scanf("%d%d",&n,&m);
    int pos,tmp;
    bit[1]=1;for(int i=2;i<=12;i++) bit[i]=bit[i-1]<<1;
    for(int i=1;i<=n;i++)
    {
        in(pos);
        for(int v=1;v<=pos;v++) in(tmp),pi[tmp][++num[tmp]]=i;
    }
    for(int i=1;i<=m;i++) in(l[i]),in(r[i]),in(need[i]),in(val[i]);
    dfs(1,0);
    cout<<ans;
    return 0;
}
