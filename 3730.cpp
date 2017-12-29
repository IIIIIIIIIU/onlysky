#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e5+5;
const int maxtree=maxn*100;
int n,m,ai[maxn],ch[maxtree][2],val[maxtree],f[maxn];
int head[maxn],E[maxn<<1],V[maxn<<1],cnt,root,size[maxn],lar[maxn];
int tot,SIZE,Root[maxn][2],tag,deep[maxn],dist[maxn][35];
bool vis[maxn];
inline void read(int &now)
{
    char Cget;
    now=0;
    while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void add(int &now,int l,int r,int to,int x)
{
    if(!now)
        now=++tot;
    val[now]+=x;
    if(l==r)
        return;
    int mid=l+r>>1;
    if(to<=mid)
        add(ch[now][0],l,mid,to,x);
    else
        add(ch[now][1],mid+1,r,to,x);
}
int query(int now,int l,int r,int tl,int tr)
{
    if(!now)
        return 0;
    if(l>=tl&&r<=tr)
        return val[now];
    int mid=l+r>>1,res=0;
    if(tl<=mid)
        res+=query(ch[now][0],l,mid,tl,tr);
    if(tr>mid)
        res+=query(ch[now][1],mid+1,r,tl,tr);
    return res;
}
void find(int now,int fa)
{
    size[now]=1;
    lar[now]=0;
    for(int i=head[now];i!=0;i=E[i])
        if(V[i]!=fa&&!vis[V[i]])
        {
            find(V[i],now);
            size[now]+=size[V[i]];
            if(size[V[i]]>lar[now])
                lar[now]=size[V[i]];
        }
    if(SIZE-size[now]>lar[now])
        lar[now]=SIZE-size[now];
    if(lar[now]<lar[root])
        root=now;
}
void dfs(int now,int fa,int dis)
{
    add(Root[tag][0],1,n,dis,ai[now]);
    dist[now][deep[tag]]=dis;
    for(int i=head[now];i!=0;i=E[i])
        if(V[i]!=fa&&!vis[V[i]])
            dfs(V[i],now,dis+1);
}
void dfs2(int now,int fa,int dis)
{
    add(Root[tag][1],1,n,dis,ai[now]);
    for(int i=head[now];i!=0;i=E[i])
        if(V[i]!=fa&&!vis[V[i]])
            dfs2(V[i],now,dis+1);
}
void build(int now,int dep)
{
    root=0;
    find(now,0);
    int t=root;
    deep[t]=dep;
    tag=t;
    dist[t][dep]=0;
    for(int i=head[t];i!=0;i=E[i])
        if(!vis[V[i]])
            dfs(V[i],t,1);
    vis[t]=true;
    int tmp=SIZE;
    for(int i=head[t];i!=0;i=E[i])
        if(!vis[V[i]])
        {
            SIZE=size[V[i]];
	    if(size[V[i]]>size[t])
		    SIZE=tmp-size[t];
            build(V[i],dep+1);
            f[root]=t;
            tag=root;
            dfs2(V[i],t,1);
        }
    root=t;
    vis[t]=false;
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
    read(n);
    read(m);
    lar[0]=0x3f3f3f3f;
    for(int i=1;i<=n;i++)
        read(ai[i]);
    for(int i=1,u,v;i<n;i++)
    {
        read(u);
        read(v);
        E[++cnt]=head[u];
        V[cnt]=v;
        head[u]=cnt;
        E[++cnt]=head[v];
        V[cnt]=u;
        head[v]=cnt;
    }
    SIZE=n;
    build(1,1);
    int op,x,y,t,out=0;
    for(int i=1;i<=m;i++)
    {
        read(op);
        read(x);
        read(y);
        x^=out;
        y^=out;
        if(op)
        {
            t=y;
            y=y-ai[x];
            ai[x]=t;
            t=x;
            while(t)
            {
                if(dist[x][deep[t]])
                    add(Root[t][0],1,n,dist[x][deep[t]],y);
                if(f[t])
                    add(Root[t][1],1,n,dist[x][deep[t]-1],y);
                t=f[t];
            }
        }
        else
        {
		out=query(Root[x][0],1,n,1,y)+ai[x];
            t=x;
            while(f[t])
            {
		   if(dist[x][deep[f[t]]]<=y)
			   out+=query(Root[f[t]][0],1,n,1,y-dist[x][deep[f[t]]])+ai[f[t]]-query(Root[t][1],1,n,1,y-dist[x][deep[f[t]]]);
		   t=f[t];
            }
            printf("%d\n",out);
        }
    }
    return 0;
}
