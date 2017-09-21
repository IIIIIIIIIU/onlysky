#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&(-x))
const int maxn=100005;
struct lazy
{
    int now,to;
    int val;
    bool operator<(const lazy pos)const
    {
        return now<pos.now;
    }
};
struct lazy addy[maxn],miy[maxn];
struct node
{
    int x,y;
};
struct node pi[maxn];
int n,m,w,bix[maxn],biy[maxn],k,cntx,cnty,cnt,sum[maxn];
int c[maxn][11],tree[maxn],ans;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
bool cmpys(const node &pos1,const node &pos2)
{
    if(pos1.x==pos2.x) return pos1.y<pos2.y;
    return pos1.x<pos2.x;
}
bool cmpx(const node &pos1,const node &pos2)
{
    if(pos1.y==pos2.y) return pos1.x<pos2.x;
    return pos1.y<pos2.y;
}
void add(int to,int x)
{
    while(to<=cnty) tree[to]+=x,to+=lowbit(to);
}
void minu(int to,int x)
{
    while(to<=cnty) tree[to]-=x,to+=lowbit(to);
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
    in(n),in(m),in(w);
    for(int i=1;i<=w;i++)
    {
        in(pi[i].x),in(pi[i].y);
        bix[++cntx]=pi[i].x;
        biy[++cnty]=pi[i].y;
    }
    in(k),c[1][1]=1;
    for(int i=1;i<=w;i++) c[i][0]=1;
    for(int i=2;i<=w;i++)
        for(int v=1;v<=k;v++)
            c[i][v]=c[i-1][v]+c[i-1][v-1];
    sort(bix+1,bix+cntx+1);
    sort(biy+1,biy+cnty+1);
    cntx=unique(bix+1,bix+cntx+1)-bix-1;
    cnty=unique(biy+1,biy+cnty+1)-biy-1;
    for(int i=1;i<=w;i++)
    {
        pi[i].x=lower_bound(bix+1,bix+cntx+1,pi[i].x)-bix;
        pi[i].y=lower_bound(biy+1,biy+cnty+1,pi[i].y)-biy;
    }
    sort(pi+1,pi+w+1,cmpx);
    int posi=1;
    while(posi<=w)
    {
        int posy=pi[posi].y,p=posi;
        sum[posi]=1;
        while(p<w&&pi[p+1].y==posy) p++,sum[p]=sum[p-1]+1;
        int len=sum[p]-sum[posi]+1;
        for(int i=posi;i<p;i++)
            if(sum[i]>=k&&(len-sum[i]>=k))
            {
                cnt++;
                addy[cnt].now=pi[i].x+1,addy[cnt].to=posy,addy[cnt].val=c[sum[i]][k]*c[len-sum[i]][k];
                miy[cnt].now=pi[i+1].x,miy[cnt].to=posy,miy[cnt].val=c[sum[i]][k]*c[len-sum[i]][k];
            }
        posi=p+1;
    }
    sort(addy+1,addy+cnt+1);
    sort(miy+1,miy+cnt+1);
    sort(pi+1,pi+w+1,cmpys);
    posi=1;int poso=1,poso2=1;
    while(posi<=w)
    {
        int posx=pi[posi].x,p=posi;
        sum[posi]=1;
        while(posx==addy[poso].now) add(addy[poso].to,addy[poso].val),poso++;
        while(posx==miy[poso2].now) minu(miy[poso2].to,miy[poso2].val),poso2++;
        while(p<w&&pi[p+1].x==posx) p++,sum[p]=sum[p-1]+1;
        int len=sum[p]-sum[posi]+1;
        for(int i=posi;i<p;i++)
            if(sum[i]>=k&&(len-sum[i]>=k))
                if(pi[i].y<pi[i+1].y) ans+=query(pi[i].y+1,pi[i+1].y)*c[sum[i]][k]*c[len-sum[i]][k];
        posi=p+1;
    }
    if(ans<0) cout<<(long long)ans+2147483648LL;
    else cout<<ans;
    return 0;
}
