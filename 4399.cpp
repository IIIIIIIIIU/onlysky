#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 400005
#define maxm 7000000
 
int ch[maxm][2],X,dis[maxm],tot,n,ai[maxn];
int size,f[maxn],cnt,op[maxn],x[maxn],y[maxn],root[maxn];
 
double lo[maxm],logg[maxn],XX;
 
inline int lower_bound(int pos)
{
    int l=1,r=size,mid,res;
    while(l<=r)
    {
        mid=l+r>>1;
        if(pos>=ai[mid]) l=(res=mid)+1;
        else r=mid-1;
    }
    return res;
}
 
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
 
void tree_query(int now,int l,int r,int li,int ri)
{
    if(!dis[now]) return ;
    if(l==r)
    {
        X+=dis[now],dis[now]=0,lo[now]=0;
        return ;
    }
    int mid=l+r>>1;
    if(li<=mid) tree_query(ch[now][0],l,mid,li,ri);
    if(ri>mid) tree_query(ch[now][1],mid+1,r,li,ri);
    dis[now]=dis[ch[now][0]]+dis[ch[now][1]],lo[now]=lo[ch[now][0]]+lo[ch[now][1]];
}
 
void tree_add(int &now,int l,int r,int to)
{
    if(!now) now=++tot;
    dis[now]+=X,lo[now]+=XX;
    if(l==r) return ;
    int mid=l+r>>1;
    if(to<=mid) tree_add(ch[now][0],l,mid,to);
    else tree_add(ch[now][1],mid+1,r,to);
}
 
int merge(int now,int pre,int l,int r)
{
    if(!now) return pre;
    if(!pre) return now;
    if(l==r)
    {
        lo[now]+=lo[pre];
        dis[now]+=dis[pre];
        return now;
    }
    int mid=l+r>>1;
    ch[now][0]=merge(ch[now][0],ch[pre][0],l,mid);
    ch[now][1]=merge(ch[now][1],ch[pre][1],mid+1,r);
    lo[now]=lo[ch[now][0]]+lo[ch[now][1]];
    dis[now]=dis[ch[now][0]]+dis[ch[now][1]];
    return now;
}
 
int irank(int now,int k)
{
    int l=1,r=size,mid;
    while(l<r)
    {
        mid=l+r>>1;
        if(dis[ch[now][0]]>=k) r=mid,now=ch[now][0];
        else k-=dis[ch[now][0]],l=mid+1,now=ch[now][1];
    }
    return ai[l];
}
 
inline int find(int j)
{
    return f[j]==j?j:f[j]=find(f[j]);
}
 
int main()
{
    in(n);
    for(int i=1;i<=n;i++)
    {
        in(op[i]),in(x[i]);
        if(op[i]>1&&op[i]<7) in(y[i]);
        if(op[i]==1) ai[++size]=x[i];
        if(op[i]==3||op[i]==4) ai[++size]=y[i];
    }
    sort(ai+1,ai+size+1),size=unique(ai+1,ai+size+1)-ai-1;
    for(int i=1;i<=size;i++) logg[i]=log(ai[i]);
    for(int i=1;i<=n;i++)
    {
        if(op[i]==1) x[i]=lower_bound(x[i]),X=1,XX=logg[x[i]],tree_add(root[++cnt],1,size,x[i]),f[cnt]=cnt;
        else if(op[i]==2)
        {
            x[i]=find(x[i]),y[i]=find(y[i]);
            if(x[i]==y[i]) continue;
            root[y[i]]=merge(root[x[i]],root[y[i]],1,size),f[x[i]]=y[i];
        }
        else if(op[i]==3)
        {
            y[i]=lower_bound(y[i]),x[i]=find(x[i]),X=0;
            if(y[i]>1) tree_query(root[x[i]],1,size,1,y[i]-1),XX=logg[y[i]]*X;
            if(X) tree_add(root[x[i]],1,size,y[i]);
        }
        else if(op[i]==4)
        {
            y[i]=lower_bound(y[i]),x[i]=find(x[i]),X=0;
            if(y[i]<size) tree_query(root[x[i]],1,size,y[i]+1,size),XX=logg[y[i]]*X;
            if(X) tree_add(root[x[i]],1,size,y[i]);
        }
        else if(op[i]==5) printf("%d\n",irank(root[find(x[i])],y[i]));
        else if(op[i]==6) puts(lo[root[find(x[i])]]>lo[root[find(y[i])]]?"1":"0");
        else if(op[i]==7) printf("%d\n",dis[root[find(x[i])]]);
        else printf("Orz\n");
    }
    return 0;
}
