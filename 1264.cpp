#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&(-x))
const int maxn=20005;
int tree[maxn*5],pi[maxn][5],num[maxn],dp[maxn*5],n;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int query(int pos)
{
    int res=0;
    while(pos) res=max(res,tree[pos]),pos-=lowbit(pos);
    return res;
}
void add(int pos,int x)
{
    while(pos<=n*5) tree[pos]=max(tree[pos],x),pos+=lowbit(pos);
}
int main()
{
    in(n);int tmp,pos;
    for(int i=1;i<=n*5;i++) in(tmp),pi[tmp][++num[tmp]]=i;
    for(int i=1;i<=n*5;i++)
    {
        in(tmp);
        for(int v=5;v>=1;v--)
        {
            pos=pi[tmp][v];
            int temp=query(pos-1);
            dp[pos]=max(dp[pos],temp+1);
            add(pos,dp[pos]);
        }
    }
    int ans=0;
    for(int i=1;i<=n*5;i++) ans=max(ans,dp[i]);
    cout<<ans;
    return 0;
}
