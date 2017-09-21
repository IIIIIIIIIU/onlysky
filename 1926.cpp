#include <bits/stdc++.h>
using namespace std;
#define maxn 500005
#define maxr 205
#define maxn_ maxn*13
#define FalseAns "Poor QLW"
int n,m,q,lc[maxn_],rc[maxn_],num[maxn_],ci[maxn_],tot,root[maxn];
int ai[maxn],bi[maxn],vi[maxn],size,ansnum,map_[maxr][maxr];
int sum[maxr][maxr][1002],sumn[maxr][maxr][1002];
inline void in (int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void build(int &now,int l,int r)
{
    now=++tot;
    if(l==r) return;
    int mid=l+r>>1;
    build(lc[now],l,mid);
    build(rc[now],mid+1,r);
}
void add(int &now,int pre,int l,int r,int to,int x)
{
    now=++tot,num[tot]=num[pre]+1,ci[tot]=ci[pre]+x;
    if(l==r) return;int mid=l+r>>1;
    if(to<=mid) add(lc[now],lc[pre],l,mid,to,x),rc[now]=rc[pre];
    else add(rc[now],rc[pre],mid+1,r,to,x),lc[now]=lc[pre];
}
void query(int now,int pre,int l,int r,int hi)
{
    if(l==r)
    {
        int pos=hi/bi[l];
        if(pos*bi[l]<hi) pos++;
        ansnum+=pos;
        return;
    }
    int mid=l+r>>1,dis=ci[rc[now]]-ci[rc[pre]];
    if(hi<=dis) query(rc[now],rc[pre],mid+1,r,hi);
    else
    {
        ansnum+=num[rc[now]]-num[rc[pre]];
        query(lc[now],lc[pre],l,mid,hi-dis);
    }
}
int main()
{
    in(n),in(m),in(q);
    if(n==1)
    {
        for(int i=1;i<=m;i++) in(ai[i]),bi[i]=ai[i],vi[i]=bi[i];
        sort(bi+1,bi+m+1),size=unique(bi+1,bi+m+1)-bi-1;
        build(root[0],1,size);
        for(int i=1;i<=m;i++)
        {
            ai[i]=lower_bound(bi+1,bi+size+1,ai[i])-bi;
            add(root[i],root[i-1],1,size,ai[i],vi[i]);
        }
        int x1,y1,x2,y2,hi,l,r;
        for(int i=1;i<=q;i++)
        {   
            in(x1),in(y1),in(x2),in(y2),in(hi);
            l=y1-1,r=y2;
            if(ci[root[r]]-ci[root[l]]<hi) puts(FalseAns);
            else ansnum=0,query(root[r],root[l],1,size,hi),printf("%d\n",ansnum);
        }
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                in(map_[i][j]);
                for(int v=map_[i][j];v>=1;v--)
                {
                    sum[i][j][v]++;
                    sumn[i][j][v]+=map_[i][j];
                }
                for(int v=1;v<=1000;v++)
                {
                    sum[i][j][v]+=sum[i-1][j][v]+sum[i][j-1][v]-sum[i-1][j-1][v];
                    sumn[i][j][v]+=sumn[i-1][j][v]+sumn[i][j-1][v]-sumn[i-1][j-1][v];
                }
            }
        }
        int x1,y1,x2,y2,hi,l,r,mid,ans,x_,y_,x__,y__,x___,y___;
        int pos1,pos1_,pos2,pos2_;
        for(int i=1;i<=q;i++)
        {
            in(x1),in(y1),in(x2),in(y2),in(hi);
            x_=x1-1,y_=y2,x__=x2,y__=y1-1,x___=x1-1,y___=y1-1;
            if(sumn[x2][y2][1]-sumn[x_][y_][1]-sumn[x__][y__][1]+sumn[x___][y___][1]<hi)
            {
                puts(FalseAns);
                continue;
            }
            l=1,r=1000,ans=-1;
            while(l<=r)
            {
                mid=l+r>>1;
                if(sumn[x2][y2][mid]-sumn[x_][y_][mid]-sumn[x__][y__][mid]+sumn[x___][y___][mid]>=hi) ans=mid,l=mid+1;
                else r=mid-1;
            }
            pos1=sum[x2][y2][ans+1]-sum[x_][y_][ans+1]-sum[x__][y__][ans+1]+sum[x___][y___][ans+1];
            pos1_=sum[x2][y2][ans]-sum[x_][y_][ans]-sum[x__][y__][ans]+sum[x___][y___][ans];
            pos2=sumn[x2][y2][ans+1]-sumn[x_][y_][ans+1]-sumn[x__][y__][ans+1]+sumn[x___][y___][ans+1];
            pos2_=sumn[x2][y2][ans]-sumn[x_][y_][ans]-sumn[x__][y__][ans]+sumn[x___][y___][ans];
            hi-=pos2,pos2_-=pos2,pos2=hi/ans;if(pos2*ans<hi) pos2++;
            printf("%d\n",pos2+pos1);
        }
    }
    return 0;
}
