#include <bits/stdc++.h>
using namespace std;
int n,sumd[1005][1005],suml[1005][1005],sumr[1005][1005],ans;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n);int pos;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=i;v++)
        {
            in(pos),suml[v][i]=suml[v][i-1]+pos;
            in(pos),sumr[i-v+1][i]=sumr[i-v+1][i-1]+pos;
            in(pos),sumd[i][v]=sumd[i][v-1]+pos;
        }
    for(int i=1;i<=n;i++)
        for(int l=1;l<=i;l++)
            for(int r=l;r<=i;r++)
            {
                if(sumd[i][r]-sumd[i][l-1]==(r-l+1)
                    &&suml[l][i]-suml[l][i-r+l-1]==(r-l+1)
                    &&sumr[i-r+1][i]-sumr[i-r+1][i-r+l-1]==(r-l+1)) ans++;
                if(n-i>=r-l+1&&sumd[i][r]-sumd[i][l-1]==(r-l+1)
                    &&sumr[i-l+2][i+r-l+1]-sumr[i-l+2][i]==(r-l+1)
                    &&suml[r+1][i+r-l+1]-suml[r+1][i]==(r-l+1)) ans++;
            }
    cout<<ans;
    return 0;
}
