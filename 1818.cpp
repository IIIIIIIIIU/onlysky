#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
struct point
{
    int x,y;
    bool operator<(const point &pos)const
    {
        if(y==pos.y) return x<pos.x;
        return y<pos.y;
    }
    point(int x_=0,int y_=0)
    {
        x=x_,y=y_;
    }
};
struct point pi[maxn];
int tree[maxn],bix[maxn],cntx,biy[maxn],cnty,n,last[maxn],ans;
vector<int>add[maxn],del[maxn];
inline void in(int &now)
{
    char Cget;now=0;int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}
#define lowbit(x) (x&(-x))
void updata(int to,int di)
{
    while(to<=n) tree[to]+=di,to+=lowbit(to);
}
int query(int l,int r)
{
    int res=0;l--;
    while(r) res+=tree[r],r-=lowbit(r);
    while(l) res-=tree[l],l-=lowbit(l);
    return res;
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++)
    {
        in(pi[i].x),in(pi[i].y);
        bix[++cntx]=pi[i].x,biy[++cnty]=pi[i].y;
    }
    sort(bix+1,bix+cntx+1),cntx=unique(bix+1,bix+cntx+1)-bix-1;
    sort(biy+1,biy+cnty+1),cnty=unique(biy+1,biy+cnty+1)-biy-1;
    for(int i=1;i<=n;i++)
    {
        pi[i].x=lower_bound(bix+1,bix+cntx+1,pi[i].x)-bix;
        pi[i].y=lower_bound(biy+1,biy+cnty+1,pi[i].y)-biy;
    }
    sort(pi+1,pi+n+1);
    for(int i=1;i<=n;i++)
        if(!last[pi[i].x]) last[pi[i].x]=pi[i].y;
        else
        {
            add[last[pi[i].x]].push_back(pi[i].x);
            del[pi[i].y-1].push_back(pi[i].x);
            last[pi[i].x]=pi[i].y;
        }
    for(int i=2;i<=n;i++)
        if(pi[i].y!=pi[i-1].y)
        {
            for(int v=0;v<add[pi[i-1].y].size();v++) updata(add[pi[i-1].y][v],1);
            for(int v=0;v<del[pi[i-1].y].size();v++) updata(del[pi[i-1].y][v],-1);
        }
        else
            if(pi[i].x>pi[i-1].x+1) ans+=query(pi[i-1].x+1,pi[i].x-1);
    cout<<ans+n;
    return 0;
}
