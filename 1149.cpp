#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=100005;
const int INF=0x3f3f3f3f;
int ch[maxn][2],size[maxn],mindeep=INF,maxdeep,ans,n;
bool can=true;
inline void in(int &now)
{
    char Cget;now=0;int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
    while(Cget<='9'&&Cget>='0')now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}
void dfs(int now,int deep)
{
    if(ch[now][0]!=-1) dfs(ch[now][0],deep+1),size[now]+=size[ch[now][0]];
    else size[now]++,mindeep=min(mindeep,deep+1),maxdeep=max(maxdeep,deep+1);
    if(ch[now][1]!=-1) dfs(ch[now][1],deep+1),size[now]+=size[ch[now][1]];
    else size[now]++,mindeep=min(mindeep,deep+1),maxdeep=max(maxdeep,deep+1);
    if(ch[now][1]!=-1&&ch[now][0]==-1) swap(ch[now][0],ch[now][1]),ans++;
    else if(ch[now][1]!=-1&&ch[now][0]!=-1&&size[ch[now][0]]<size[ch[now][1]])
        swap(ch[now][0],ch[now][1]),ans++;
}
void dfs2(int now)
{
    if(ch[now][0]!=-1) dfs2(ch[now][0]);
    if(ch[now][1]!=-1) dfs2(ch[now][1]);
    if(ch[now][0]!=-1&&ch[now][1]!=-1)
    {
        int a=1,b=1,c=1;
        if(ch[ch[now][0]][0]!=-1) a=size[ch[ch[now][0]][0]];
        if(ch[ch[now][0]][1]!=-1) b=size[ch[ch[now][0]][1]];
        if(ch[ch[now][1]][0]!=-1) c=size[ch[ch[now][1]][0]];
        if(b<c) can=false;
    }
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++) in(ch[i][0]),in(ch[i][1]);
    dfs(1,1);
    dfs2(1);
    if(maxdeep-mindeep>1) can=false;
    if(can) cout<<ans;
    else cout<<-1;
    return 0;
}
