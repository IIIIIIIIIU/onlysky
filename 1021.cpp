#include <bits/stdc++.h>
using namespace std;
#define maxn 1005
#define INF 0x3f3f3f3f
int dp[7][maxn][maxn],n,ai[4][7],wi[7],tot,x1,x2,x3,tot2[4],ed[4];
inline void in(int &now)
{
    char Cget;now=0;int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0') if(Cget=='-') if_z=-1;
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}
inline void R(int &a,int b)
{
    if(b<a) a=b;
}
int main()
{
    in(x1),in(x2),in(x3);
    wi[1]=100,wi[2]=50,wi[3]=20,wi[4]=10,wi[5]=5,wi[6]=1;
    for(int i=1;i<=3;i++)
        for(int v=1;v<=6;v++) in(ai[i][v]),tot2[i]+=ai[i][v]*wi[v];
    memset(dp,127/3,sizeof(dp)),dp[0][tot2[1]][tot2[2]]=0;
    tot=tot2[1]+tot2[2]+tot2[3];int pos=dp[0][1000][1000];
    for(int i=1;i<=6;i++)
        for(int v1=0;v1<=tot;v1++)
            for(int v2=0;v2<=tot-v1;v2++)
            {
                if(dp[i-1][v1][v2]==pos) continue;
                int t=tot-v1-v2;
                for(int e=0;e<=ai[1][i];e++)
                    if(v1-wi[i]*e>=0)
                    {
                        for(int f=0;f<=e;f++)
                            if(wi[i]*f+v2<=tot&&wi[i]*(e-f)+t<=tot)
                                R(dp[i][v1-wi[i]*e][wi[i]*f+v2],dp[i-1][v1][v2]+e);
                    }
                    else break;
                for(int e=0;e<=ai[2][i];e++)
                    if(v2-wi[i]*e>=0)
                    {
                        for(int f=0;f<=e;f++)
                            if(wi[i]*f+v1<=tot&&wi[i]*(e-f)+t<=tot)
                                R(dp[i][v1+wi[i]*f][v2-wi[i]*e],dp[i-1][v1][v2]+e);
                    }
                    else break;
                for(int e=0;e<=ai[3][i];e++)
                    if(t-wi[i]*e>=0)
                    {
                        for(int f=0;f<=e;f++)
                            if(wi[i]*f+v1<=tot&&wi[i]*(e-f)+v2<=tot)
                                R(dp[i][v1+wi[i]*f][v2+wi[i]*(e-f)],dp[i-1][v1][v2]+e);
                    }
                    else break;
                for(int e=0;e<=ai[1][i];e++)
                    if(v1-wi[i]*e>=0)
                        for(int f=0;f<=ai[2][i];f++)
                            if(v2-wi[i]*f>=0&&t+wi[i]*(e+f)<=tot)
                                R(dp[i][v1-wi[i]*e][v2-wi[i]*f],dp[i-1][v1][v2]+e+f);
                            else break;
                    else break;
                for(int e=0;e<=ai[1][i];e++)
                    if(v1-wi[i]*e>=0)
                        for(int f=0;f<=ai[3][i];f++)
                            if(t-wi[i]*f>=0&&v2+wi[i]*(e+f)<=tot)
                                R(dp[i][v1-wi[i]*e][v2+wi[i]*(e+f)],dp[i-1][v1][v2]+e+f);
                            else break;
                    else break;
                for(int e=0;e<=ai[2][i];e++)
                    if(v2-wi[i]*e>=0)
                        for(int f=0;f<=ai[3][i];f++)
                            if(t-wi[i]*f>=0&&v1+wi[i]*(e+f)<=tot)
                                R(dp[i][v1+wi[i]*(e+f)][v2-wi[i]*e],dp[i-1][v1][v2]+e+f);
                            else break;
                    else break;
            }
    ed[1]=tot2[1]-x1+x3,ed[2]=tot2[2]-x2+x1,ed[3]=tot2[3]-x3+x2;
    if(ed[1]<0||ed[2]<0||ed[3]<0||dp[6][ed[1]][ed[2]]>10000) cout<<"impossible";
    else cout<<dp[6][ed[1]][ed[2]];
    return 0;
}
