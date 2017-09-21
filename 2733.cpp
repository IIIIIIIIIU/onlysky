#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 100001
 
int n,q,tot,ch[maxn*40][2],key[maxn*40],w[maxn*40],opi[maxn*40],m;
int size[maxn*40],root[maxn],id[maxn*40],f[maxn],cnt,dis[maxn*40],lar[maxn];
 
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
 
inline int getson(int now)
{
    return ch[opi[now]][1]==now;
}
 
inline void updata(int now)
{
    size[now]=w[now];
    if(ch[now][0]) size[now]+=size[ch[now][0]];
    if(ch[now][1]) size[now]+=size[ch[now][1]];
}
 
inline void rotate(int now)
{
    int fa=opi[now],ffa=opi[fa],pos=getson(now);
    ch[fa][pos]=ch[now][pos^1];
    if(ch[fa][pos]) opi[ch[fa][pos]]=fa;
    if(ffa) ch[ffa][getson(fa)]=now;
    ch[now][pos^1]=fa,opi[fa]=now,opi[now]=ffa;
    updata(fa),updata(now);
}
 
inline void splay(int now,int to)
{
    for(int fa;fa=opi[now];rotate(now))
    {
        if(opi[fa]) rotate(getson(now)==getson(fa)?fa:now);
    }
    root[to]=now;
}
 
inline void insert(int x,int y,int to)
{
    if(!root[to])
    {
        root[to]=++tot,key[tot]=x,w[tot]=size[tot]=1,id[tot]=y;
        return ;
    }
    int now=root[to],fa=0;
    while(1)
    {
        fa=now;
        if(x<key[now]) now=ch[now][0];
        else now=ch[now][1];
        if(!now)
        {
            now=ch[fa][x>key[fa]]=++tot;
            key[now]=x,id[now]=y,w[now]=size[now]=1,opi[now]=fa;
            splay(now,to);break;
        }
    }
}
 
inline int find(int x)
{
    if(x==f[x]) return x;
    return f[x]=find(f[x]);
}
 
inline int irank(int k,int to)
{
    int now=root[to];
    while(1)
    {
        int dis=size[ch[now][0]];
        if(k<=dis) now=ch[now][0];
        else
        {
            k-=dis;
            if(k<=w[now])
            {
                splay(now,to);
                return id[now];
            }
            else k-=w[now],now=ch[now][1];
        }
    }
}
 
inline void merge(int noww,int now)
{
    if(!now) return ;
    if(ch[now][0]) merge(noww,ch[now][0]);
    insert(key[now],id[now],noww);
    if(ch[now][1]) merge(noww,ch[now][1]);
}
 
int main()
{
    in(n),in(m);int x,y;char ch[4];
    for(int i=1;i<=n;i++) in(dis[i]),f[i]=i,insert(dis[i],i,i),lar[i]=1;
    for(;m--;)
    {
        in(x),in(y);
        x=find(x),y=find(y);
        if(lar[x]<lar[y]) swap(x,y);lar[x]+=lar[y];
        if(x!=y) f[y]=x,merge(x,root[y]);
    }
    in(q);
    for(;q--;)
    {
        scanf("%s",ch);in(x),in(y);
        if(ch[0]=='Q')
        {
            x=find(x);
            if(y<=size[root[x]]) printf("%d\n",irank(y,x));
            else printf("-1\n");
        }
        else
        {
            x=find(x),y=find(y);
            if(lar[x]<lar[y]) swap(x,y);lar[x]+=lar[y];
            if(x!=y) f[y]=x,merge(x,root[y]);
        }
    }
    return 0;
}
