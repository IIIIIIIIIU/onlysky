#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n,ch[1005][2],ans[1005],cnt,root;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void doit(int now,int fa)
{
    if((ch[now][1]==-1&&ch[now][0]==-1)||(ch[now][1]==-1&&ch[now][0]!=-1&&ch[ch[now][0]][0]!=-1))
    {
        ans[cnt]=now;
        ch[fa][0]=ch[now][0];
        if(fa==-1) root=ch[now][0];
        return;
    }
    doit(ch[now][0],now);
    swap(ch[now][0],ch[now][1]);
}
int main()
{
    in(n),memset(ch,-1,sizeof(ch));
    int pos;cnt=n+1;
    for(int i=1;i<=n;i++)
    {
        in(pos);
        if(pos<100) ch[pos][0]=i;
        else ch[pos-100][1]=i;
    }
    for(cnt=n+1;cnt>=1;cnt--)
        doit(root,-1);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    cout<<ans[n+1];
    return 0;
}
