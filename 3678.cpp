#include<cstdio>
 
#include<cstdlib>
 
#include<cmath>
 
#include<cstring>
 
#include<algorithm>
 
#include<iostream>
 
#include<vector>
 
#include<map>
 
#include<set>
 
#include<queue>
 
#include<string>
 
#define inf 1000000000
 
#define maxn 1000000+5
 
#define maxm 20000000+5
 
#define eps 1e-10
 
#define ll long long
 
#define pa pair<int,int>
 
#define for0(i,n) for(int i=0;i<=(n);i++)
 
#define for1(i,n) for(int i=1;i<=(n);i++)
 
#define for2(i,x,y) for(int i=(x);i<=(y);i++)
 
#define for3(i,x,y) for(int i=(x);i>=(y);i--)
 
#define mod 1000000007
 
using namespace std;
 
inline int read()
 
{
 
    int x=0,f=1;char ch=getchar();
 
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
 
    while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}
 
    return x*f;
 
}
int n,m,t1,t2,rt,tot,fa[maxn],c[maxn][2],s[maxn],v[maxn][2];
int a[20];
inline void pushup(int x)
{
    s[x]=s[c[x][0]]+s[c[x][1]]+v[x][1]-v[x][0]+1;
}
inline void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y],l=c[y][1]==x,r=l^1;
    if(y!=k)c[z][c[z][1]==y]=x;else k=x;
    fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
    c[y][l]=c[x][r];c[x][r]=y;
    pushup(y);pushup(x);
}
inline void splay(int x,int &k)
{
    while(x!=k)
    {
        int y=fa[x],z=fa[y];
        if(y!=k)
        {
            if(c[z][0]==y^c[y][0]==x)rotate(x,k);else rotate(y,k);
        }
        rotate(x,k);
    }
}
inline int find(int x,int k)
{
     
    if(s[c[x][0]]>=k)return find(c[x][0],k);
    else if(s[x]-s[c[x][1]]<k)return find(c[x][1],k-s[x]+s[c[x][1]]);
    else
    {
        k-=s[c[x][0]];
        if(k!=1)
        {
            fa[c[++tot][0]=c[x][0]]=tot;fa[c[x][0]=tot]=x;
            v[tot][0]=v[x][0];v[tot][1]=v[x][0]+k-2;v[x][0]=v[tot][1]+1;
            pushup(tot);
            k=1;
        }
        if(k!=v[x][1]-v[x][0]+1)
        {
            fa[c[++tot][1]=c[x][1]]=tot;fa[c[x][1]=tot]=x;
            v[tot][1]=v[x][1];v[tot][0]=v[x][0]+k;v[x][1]=v[tot][0]-1;
            pushup(tot);
        }
        return x;
    }
}
inline void split(int l,int r)
{
    t1=find(rt,l);
    t2=find(rt,r);
    splay(t1,rt);splay(t2,c[t1][1]);
}
inline void build(int l,int r,int f)
{
    if(l>r)return;
    int x=(l+r)>>1;
    fa[x]=f;c[f][x>f]=x;
    if(l==r){s[x]=1;return;}
    build(l,x-1,x);build(x+1,r,x);
    pushup(x);
}
 
int main()
 
{
    n=read();m=read();
    for2(i,2,n+1)v[i][0]=v[i][1]=read();
    build(1,n+2,0);rt=(1+n+2)>>1;tot=n+2;
    while(m--)
    {
        int ch=read();//cout<<ch<<endl;
        if(!ch)
        {
            int p=read(),x=read(),y=read();
            split(p+1,p+2);
            fa[c[t2][0]=++tot]=t2;v[tot][0]=x;v[tot][1]=y;s[tot]=y-x+1;
            pushup(t2);pushup(t1);
        }else if(ch==1)
        {
            int x=read(),y=read();
            split(x,y+2);
            c[t2][0]=0;
            pushup(t2);pushup(t1);
        }else printf("%d\n",v[find(rt,read()+1)][0]);
    }
 
    return 0;
 
}
