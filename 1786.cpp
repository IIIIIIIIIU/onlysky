#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&(-x))
typedef long long ll;
const int maxn=10005;
struct node
{
    int val,p;
    bool operator<(const node &pos)const
    {
        return p<pos.p;
    }
};
struct node pi[maxn];
int ai[maxn],p[maxn],cnt,val[maxn],bi[maxn],n,k,ans=0x3f3f3f3f;
int tree[maxn],tot;
ll dp[2][10005];
void add(int to)
{
    while(to<=k) tree[to]++,to+=lowbit(to);
}
ll query(int l,int r)
{
    ll res=0;
    while(r) res+=tree[r],r-=lowbit(r);
    while(l) res-=tree[l],l-=lowbit(l);
    return res;
}
ll get()
{
    ll res=0;
    for(int i=1;i<=n;i++)
        if(ai[i]>0) pi[++tot].val=ai[i],pi[tot].p=i;
    sort(pi+1,pi+tot+1);
    for(int i=1;i<=tot;i++)
    {
        res+=query(pi[i].val,k);
        add(pi[i].val);
    }
    return res;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&ai[i]);
        if(ai[i]==-1) p[++cnt]=i;
    }
    for(int i=1;i<=cnt;i++) dp[0][i]=1e12;
    for(int i=1;i<=k;i++)
    {
        for(int v=n,e=cnt;v>=1;v--)
        {
            val[v]=val[v+1];
            if(ai[v]==-1) bi[e--]=val[v];
            else if(ai[v]<i) val[v]++;
        }
        for(int v=1,e=1;v<=n;v++)
        {
            val[v]=val[v-1];
            if(ai[v]==-1) bi[e++]+=val[v];
            else if(ai[v]>i) val[v]++;
        }
        int now=i%2,last=now^1;
        for(int v=1;v<=cnt;v++)
            dp[now][v]=min(min(dp[last][v-1],dp[now][v-1])+bi[v],dp[last][v]);
    }
    cout<<dp[k%2][cnt]+get();
    return 0;
}
