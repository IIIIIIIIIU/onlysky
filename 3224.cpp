#include <bits/stdc++.h>
using namespace std;
#define maxn 1000005
int w[maxn],size[maxn],key[maxn],ch[maxn][2],f[maxn];
int root,tot,n;
inline void in(int &now)
{
    int if_z=1;now=0;
    char Cget=getchar();
    while(Cget>'9'||Cget<'0')
    {
        if(Cget=='-') if_z=-1;
        Cget=getchar();
    }
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
}
inline void updata(int now)
{
    size[now]=w[now];
    if(ch[now][0]) size[now]+=size[ch[now][0]];
    if(ch[now][1]) size[now]+=size[ch[now][1]];
}
inline void rotate(int now)
{
    int fa=f[now],ffa=f[fa],l=(ch[fa][1]==now),r=l^1;
    if(ffa) ch[ffa][ch[ffa][1]==fa]=now;
    ch[fa][l]=ch[now][r],ch[now][r]=fa,f[fa]=now,f[now]=ffa;
    if(ch[fa][l]) f[ch[fa][l]]=fa;updata(fa);
}
void splay(int now)
{
    int fa,ffa;
    while(f[now])
    {
        fa=f[now],ffa=f[fa];
        if(ffa)
        {
            if(ch[fa][1]==now^ch[ffa][1]==fa) rotate(fa);
            else rotate(now);
        }
        rotate(now);
    }
    root=now,updata(now);
}
void insert(int x)
{
    if(!root)
    {
        root=++tot,key[root]=x,w[tot]=size[tot]=1;
        return;
    }
    int now=root,fa=0;
    while(1)
    {
        if(key[now]==x)
        {
            size[now]++,w[now]++,splay(now);
            return;
        }
        fa=now;
        if(x<key[now]) now=ch[now][0];
        else now=ch[now][1];
        if(!now)
        {
            ch[fa][x>key[fa]]=++tot,size[tot]=1,w[tot]=1,key[tot]=x,f[tot]=fa;
            splay(tot);return;
        }
    }
}
void del()
{
    if(w[root]>1)
    {
        w[root]--,size[root]--;
        return;
    }
    int now=root;
    if(!ch[now][1]&&!ch[now][0]) root=0;
    else if(ch[now][1]&&ch[now][0])
    {
        int to=ch[now][0],tmp=ch[now][1];
        f[to]=0;while(ch[to][1]) to=ch[to][1];
        splay(to),ch[to][1]=tmp,f[tmp]=to,root=to,updata(to);
    }
    else if(ch[now][0]) root=ch[now][0],f[root]=0;
    else root=ch[now][1],f[root]=0;
}
int pre(int x)
{
    insert(x);
    int now=ch[root][0];
    while(ch[now][1]) now=ch[now][1];
    del();return key[now];
}
int suf(int x)
{
    insert(x);
    int now=ch[root][1];
    while(ch[now][0]) now=ch[now][0];
    del();return key[now];
}
int find(int x)
{
    int now=root;
    while(1)
    {
        if(key[now]==x)
        {
            splay(now);
            return size[ch[root][0]]+1;
        }
        if(x<key[now]) now=ch[now][0];
        else now=ch[now][1];
    }
}
int Rank(int x)
{
    int now=root;
    while(1)
    {
        if(x<=size[ch[now][0]]) now=ch[now][0];
        else
        {
            x-=size[ch[now][0]];
            if(x<=w[now])
            {
                splay(now);
                return key[now];
            }
            x-=w[now],now=ch[now][1];
        }
    }
}
int main()
{
    in(n);int op,x;
    while(n--)
    {
        in(op),in(x);
        if(op==1) insert(x);
        if(op==2) find(x),del();
        if(op==3) printf("%d\n",find(x));
        if(op==4) printf("%d\n",Rank(x));
        if(op==5) printf("%d\n",pre(x));
        if(op==6) printf("%d\n",suf(x));
    }
    return 0;
}
