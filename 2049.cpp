#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 100005
 
int n,m,ch[maxn][2],f[maxn],st[maxn];
 
bool rev[maxn];
 
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
 
inline bool root(int now)
{
    return ch[f[now]][0]!=now&&ch[f[now]][1]!=now;
}
 
inline void pushdown(int k)
{
    int l=ch[k][0],r=ch[k][1];
    if(rev[k])
    {
        rev[k]^=1,rev[l]^=1,rev[r]^=1;
        swap(ch[k][0],ch[k][1]);
    }
}
 
inline void rotate(int now)
{
    int fa=f[now],ffa=f[fa],l,r;
    l=(ch[fa][1]==now),r=l^1;
    if(!root(fa)) ch[ffa][ch[ffa][1]==fa]=now;
    f[now]=ffa,f[fa]=now,f[ch[now][r]]=fa;
    ch[fa][l]=ch[now][r],ch[now][r]=fa;
}
 
void splay(int now)
{
    int top=0;st[++top]=now;
    for(int i=now;!root(i);i=f[i]) st[++top]=f[i];
    for(int i=top;i;i--) pushdown(st[i]);
    while(!root(now))
    {
        int fa=f[now],ffa=f[fa];
        if(!root(fa))
        {
            if((ch[fa][0]==now)^(ch[ffa][0]==fa)) rotate(now);
            else rotate(fa);
        }
        rotate(now);
    }
}
 
void access(int now)
{
    for(int i=0;now;now=f[now]) splay(now),ch[now][1]=i,i=now;
}
 
void rever(int now)
{
    access(now),splay(now),rev[now]^=1;
}
 
void link(int x,int y)
{
    rever(x),f[x]=y,splay(x);
}
 
void cut(int x,int y)
{
    rever(x),access(y),splay(y);ch[y][0]=f[x]=0;
}
 
int find(int now)
{
    access(now);splay(now);
    int pos=now;
    while(ch[pos][0]) pos=ch[pos][0];
    return pos;
}
 
int main()
{
    int u,v;char ch[10];
    in(n),in(m);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",ch);in(u),in(v);
        if(ch[0]=='C') link(u,v);
        else if(ch[0]=='D') cut(u,v);
        else if(find(u)==find(v)) puts("Yes");else puts("No");
    }
    return 0;
}
