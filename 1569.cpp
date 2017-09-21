#include <bits/stdc++.h>
using namespace std;
int n,x,y,z,A,B;
bool dp[51][51][51][51][3];
int main()
{
    scanf("%d%d%d%d%d%d",&n,&x,&y,&z,&A,&B);
    dp[0][n][0][0][0]=true;
    int lit=50;
    for(int a=0;a<lit;a++)
        for(int b=n;b<lit;b++)
            for(int c=0;c<lit;c++)
                for(int d=0;d<=lit;d++)
                    for(int e=0;e<3;e++)
                        if(dp[a][b][c][d][e])
                        {
//                          printf("%d %d %d %d %d\n",a,b,c,d,e);
                            if(a==2)
                            {
                                int ops=0;
                            }
                            if(c>=A&&d>=B)
                            {
                                cout<<a;
                                return 0;
                            }
                            if(e==2)
                            {
                                for(int i=0;i<=b;i++)
                                {
                                    if(i*x+c<lit&&(b-i)*y+d<lit)
                                        dp[a+1][b+1][c+i*x][d+(b-i)*y][0]=true;
                                }
                            }
                            else if(e==1)
                            {
                                for(int i=0;i<=b;i++)
                                {
                                    if(i*x+c<lit&&(b-i)*y+d<lit)
                                        dp[a+1][b][c+i*x][d+(b-i)*y][2]=true;
                                }
                            }
                            else
                            {
                                for(int i=0;i<=b;i++)
                                {
                                    if(i*x+c<lit&&(b-i)*y+d<lit)
                                        dp[a+1][b][c+i*x][d+(b-i)*y][0]=true;
                                }
                                for(int i=0;i<=b;i++)
                                {
                                    if(i*x+c<lit&&(b-i)*y+d<lit&&c>=z)
                                        dp[a+1][b][c+i*x-z][d+(b-i)*y][1]=true;
                                }
                            }
                        }
    return 0;
}
