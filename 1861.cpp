//#include <ctime>
#include <cstdio>
//#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=200005;
int n,m,key[maxn],tot,ch[maxn][2],f[maxn],size[maxn],root,id[maxn];
inline void in(int &now)
{
    char Cget;now=0;int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}
void updata(int x)
{
    size[x]=1;
    if(ch[x][0]) size[x]+=size[ch[x][0]];
    if(ch[x][1]) size[x]+=size[ch[x][1]];
}
int build(int fa,int l,int r)
{
    int mid=l+r>>1;f[mid]=fa;
    if(l<mid) ch[mid][0]=build(mid,l,mid-1);
    if(r>mid) ch[mid][1]=build(mid,mid+1,r);
    updata(mid);return mid;
}
void rotate(int x)
{
    int fa=f[x],ffa=f[fa],l=(ch[fa][1]==x),r=l^1;
    if(ffa) ch[ffa][ch[ffa][1]==fa]=x;
    ch[fa][l]=ch[x][r],ch[x][r]=fa,f[fa]=x,f[x]=ffa;
    if(ch[fa][l]) f[ch[fa][l]]=fa;updata(fa);
}
void splay(int x)
{
    int fa,ffa;
    while(f[x])
    {
        fa=f[x],ffa=f[fa];
        if(ffa)
        {
            if(ch[ffa][1]==fa^ch[fa][1]==x) rotate(fa);
            else rotate(x);
        }
        rotate(x);
    }
    updata(x),root=x;
}
void find(int x)
{
    int now=root;
    while(1)
    {
        if(size[ch[now][0]]>=x) now=ch[now][0];
        else
        {
            x-=size[ch[now][0]];
            if(x==1)
            {
                splay(now);
                return;
            }
            x--,now=ch[now][1];
        }
    }
}
void del()
{
    if(ch[root][1]&&ch[root][0])
    {
        int to=ch[root][0],tmp=ch[root][1];
        f[to]=0;while(ch[to][1]) to=ch[to][1];
        splay(to),ch[to][1]=tmp,f[tmp]=to,updata(to);
    }
    else if(ch[root][0]) root=ch[root][0],f[root]=0;
    else if(ch[root][1]) root=ch[root][1],f[root]=0;
    else root=0;
}
void top(int x)
{
    int tmp=id[x];
    splay(tmp);
    del();
    find(1);
    ch[root][0]=++tot,f[tot]=root,key[tot]=x;
    id[x]=tot,updata(tot),updata(root);
}
void bottom(int x)
{
    int tmp=id[x];
    splay(tmp),del();
    find(n-1);
    ch[root][1]=++tot,f[tot]=root,key[tot]=x;
    id[x]=tot,updata(tot),updata(root);
}
void insert(int x,int t)
{
    splay(id[x]);int s=size[ch[root][0]];
    if(s+t==0) top(x);
    else if(s+t==n-1) bottom(x);
    else
    {
        del();
        find(s+t);
        int tmp=ch[root][1];
        ch[root][1]=++tot,id[x]=tot;
        key[tot]=x,ch[tot][1]=tmp,f[tmp]=tot,f[tot]=root;
        updata(tot),updata(root);
    }
}
int main()
{
//  freopen("data.txt","r",stdin);
    in(n),in(m);
    for(int i=1;i<=n;i++) in(key[i]),id[key[i]]=i;
    root=build(0,1,n),tot=n;
    char op[20];int x,t;
//  srand(time(0));
    for(int i=1;i<=m;i++)
    {
//      if(i%25==0) find(rand()%n+1);
        scanf("%s",op);
        if(op[0]=='T')
        {
            in(x);
            top(x);
        }
        else if(op[0]=='B')
        {
            in(x);
            bottom(x);
        }
        else if(op[0]=='I')
        {
            in(x),in(t);
            if(t!=0) insert(x,t);
        }
        else if(op[0]=='A')
        {
            in(x);
            splay(id[x]);
            printf("%d\n",size[ch[root][0]]);
        }
        else
        {
            in(x);
            find(x);
            printf("%d\n",key[root]);
        }
    }
    return 0;
}
