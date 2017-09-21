#include <bits/stdc++.h>
using namespace std;
int num[5],to[5][17][2],len;
char ch[4],str[400];
bool dp[205][205][5];
int get(char x)
{
    if(x=='W') return 1;
    if(x=='I') return 2;
    if(x=='N') return 3;
    return 4;
}
int main()
{
    for(int i=1;i<=4;i++) scanf("%d",&num[i]);
    for(int i=1;i<=4;i++)
        for(int v=1;v<=num[i];v++)
        {
            scanf("%s",ch);
            to[i][v][0]=get(ch[0]);
            to[i][v][1]=get(ch[1]);
        }
    scanf("%s",str+1),len=strlen(str+1);
    for(int i=1;i<=len;i++) dp[i][i][get(str[i])]=true;
    for(int i=1;i<len;i++)
        for(int v=1;v+i<=len;v++)
            for(int e=v;e<v+i;e++)
                for(int a=1;a<=4;a++)
                    for(int b=1;b<=num[a];b++)
                        dp[v][v+i][a]|=dp[v][e][to[a][b][0]]&dp[e+1][v+i][to[a][b][1]];
    int pos=0;
    if(dp[1][len][1]) putchar('W'),pos=1;
    if(dp[1][len][2]) putchar('I'),pos=1;
    if(dp[1][len][3]) putchar('N'),pos=1;
    if(dp[1][len][4]) putchar('G'),pos=1;
    if(!pos) printf("The name is wrong!");
    return 0;
}
