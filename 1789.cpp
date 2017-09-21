#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;
char s[3][55];
int len[3],m,same,d;
inline int get(int x,int y){
    int pop=same+1;
    while (pop<=len[x]&&pop<=len[y]&&s[x][pop]==s[y][pop]) pop++;
    return pop-same-1;
}
int main(){
    for (int i=0;i<3;i++) scanf("%d%s",&len[i],s[i]+1);
    m=min(len[0],min(len[1],len[2]));
    for (int i=1;i<=m;i++)
        if (s[0][i]!=s[2][i]||s[0][i]!=s[1][i]||s[1][i]!=s[2][i]) break;
        else same=i;
    int d=max(get(0,1),max(get(0,2),get(1,2)));
    printf("%d",len[1]+len[2]+len[0]-3*same-d);
}
