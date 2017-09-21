#include <bits/stdc++.h>
using namespace std;
#define maxn 200005
int n,m,f[maxn],ch[maxn][2],rev[maxn],ki[maxn],sta[maxn],top,lit,size[maxn];
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void updata(int now)
{
    size[now]=size[ch[now][0]]+size[ch[now][1]]+1;
}
void downdata(int now)
{
    if(rev[now])
    {
        swap(ch[now][1],ch[now][0]);
        rev[now]^=1,rev[ch[now][1]]^=1,rev[ch[now][0]]^=1;
    }
}
bool isroot(int now)
{
    return (ch[f[now]][1]!=now)&&(ch[f[now]][0]!=now);
}
void rotate(int now)
{
    int fa=f[now],ffa=f[fa],l=(ch[fa][1]==now),r=l^1;
    if(!isroot(fa)) ch[ffa][ch[ffa][1]==fa]=now;
    f[now]=ffa,f[fa]=now,ch[fa][l]=ch[now][r],ch[now][r]=fa;
    if(ch[fa][l]) f[ch[fa][l]]=fa;
    updata(fa),updata(now);
}
void splay(int now)
{
    top=1,sta[1]=now;
    for(int i=now;!isroot(i);i=f[i]) sta[++top]=f[i];
    while(top) downdata(sta[top--]);
    int fa,ffa;
    while(!isroot(now))
    {
        fa=f[now],ffa=f[fa];
        if(!isroot(fa))
        {
            if((ch[fa][0]==now)^(ch[ffa][0]==fa)) rotate(fa);
            else rotate(now);
        }
        rotate(now);
    }
}
void access(int now)
{
    for(int i=0;now;i=now,now=f[now]) splay(now),ch[now][1]=i;
}
void makeroot(int now)
{
    access(now),splay(now),rev[now]^=1;
}
void split(int x,int y)
{
    makeroot(x),access(y),splay(y);
}
void cut(int x,int y)
{
    split(x,y),f[x]=ch[y][0]=0;
}
void link(int x,int y)
{
    makeroot(x),f[x]=y;
}
int ofans(int x)
{
    makeroot(lit),access(x),splay(x);
    return size[ch[x][0]];
}
int main()
{
    in(n),lit=n+1;int u,v,op;
    for(int i=1;i<=n;i++)
    {
        in(ki[i]);
        if(i+ki[i]<=n) link(i,i+ki[i]);
        else link(i,lit);
    }
    in(m);
    while(m--)
    {
        in(op);
        if(op==1) in(u),u++,printf("%d\n",ofans(u));
        else
        {
            in(u),in(v),u++;
            if(u+ki[u]<=n) cut(u,u+ki[u]);
            else cut(u,lit);
            ki[u]=v;
            if(u+v<=n) link(u,u+v);
            else link(u,lit);
        }
    }
    return 0;
}
