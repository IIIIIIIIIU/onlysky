#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 100005
int n,ai[maxn];
char ch[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n);
    bool vis[30];
    for(int i=1;i<=n;i++) in(ai[i]),ai[i]=i-ai[i];
    ch[1]='a';int now=1;
    for(int i=2;i<=n;i++)
    {
        if(!ai[i])
        {
            int now=ai[i-1];
            for(int v=0;v<=30;v++) vis[v]=true;
            while(now) vis[ch[now+1]-'a']=false,now=ai[now];
            for(int v=1;v<26;v++)
                if(vis[v])
                {
                    ch[i]='a'+v;
                    break;
                }
        }
        else ch[i]=ch[ai[i]];
    }
    for(int i=1;i<=n;i++) putchar(ch[i]);
    return 0;
}
