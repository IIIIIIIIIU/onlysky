#include <bits/stdc++.h>
using namespace std;
const int maxn=5005;
int n,A,B,C,Max,Min,l,r,cnt,ans;
struct AiType
{
    int h,v,s;
    void makeit()
    {
        s=A*h+B*v;
    }
} ai[2][maxn];
inline bool cmph(const AiType &a,const AiType &b)
{
    return a.h<b.h;
}
inline bool cmps(const AiType &a,const AiType &b)
{
    return a.s<b.s;
}
inline bool check(int id,int d)
{
    return ai[id][d].v<=Max&&ai[id][d].v>=Min;
}
int main()
{
    scanf("%d%d%d%d",&n,&A,&B,&C);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&ai[0][i].h,&ai[0][i].v);
        ai[0][i].makeit(),ai[1][i]=ai[0][i];
    }
    sort(ai[0]+1,ai[0]+n+1,cmph);
    sort(ai[1]+1,ai[1]+n+1,cmps);
    for(int i=1;i<=n;i++)
    {
        Min=ai[0][i].v,Max=Min+C/B;
        l=r=cnt=0;
        for(int v=1;v<=n;v++)
        {
            while(r<n&&ai[1][r+1].s-A*ai[0][v].h-B*ai[0][i].v<=C)
                cnt+=check(1,++r);
            while(l<n&&ai[0][l+1].h<ai[0][v].h) cnt-=check(0,++l);
            ans=max(ans,cnt);
        }
    }
    cout<<ans;
    return 0;
}
