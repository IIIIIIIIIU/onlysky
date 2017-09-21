#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n,dp[2][4][4][4][4],ans;
char ch[100005];
int get(char a)
{
    if(a=='M') return 1;
    else if(a=='B') return 2;
    else return 3;
}
int get(int a,int b,int c)
{
    int res=0;
    if(a==1||b==1||c==1) ++res;
    if(a==2||b==2||c==2) ++res;
    if(a==3||b==3||c==3) ++res;
    return res;
}
int main()
{
    scanf("%d",&n);
    scanf("%s",ch+1);
    int now=1,last=0;
    memset(dp[last],-127/3,sizeof(dp[last]));
    dp[last][0][0][0][0]=0;
    for(int i=1;i<=n;++i,now^=1,last^=1)
    {
        int tmp=get(ch[i]);
        //cout<<tmp<<endl;
        memset(dp[now],-127/3,sizeof(dp[now]));
        for(int a=0;a<=3;a++)
            for(int b=0;b<=3;b++)
                for(int c=0;c<=3;c++)
                    for(int d=0;d<=3;d++)
                    {
                        if(a==0&&b==0&&c==0&&d==1&&i==2)
                        {
                            int pos=2;
                        }
                        dp[now][b][tmp][c][d]=max(dp[last][a][b][c][d]+get(a,b,tmp),dp[now][b][tmp][c][d]);
                        dp[now][a][b][d][tmp]=max(dp[last][a][b][c][d]+get(c,d,tmp),dp[now][a][b][d][tmp]);
                        //if(dp[now][b][tmp][c][d]>0) printf("%d %d %d %d %d %d\n",now,b,tmp,c,d,dp[now][b][tmp][c][d]);
                        //if(dp[now][a][b][d][tmp]>0) printf("%d %d %d %d %d %d\n",now,a,b,d,tmp,dp[now][a][b][d][tmp]);
                    }
    }
    for(int a=0;a<=3;a++)
        for(int b=0;b<=3;b++)
            for(int c=0;c<=3;c++)
                for(int d=0;d<=3;d++)
                    ans=max(ans,dp[last][a][b][c][d]);
    cout<<ans;
    return 0;
}
