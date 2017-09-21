#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1e5+5;
int inline swp(int &a,int &b){
    a^=b^=a^=b;
}
int inline readint(){
    int Num;char ch;
    while((ch=getchar())<'0'||ch>'9');Num=ch-'0';
    while((ch=getchar())>='0'&&ch<='9') Num=Num*10+ch-'0';
    return Num;
}
void outint(int x){
    if(x>=10) outint(x/10);
    putchar(x%10+'0');
}
int n,m,data[MAXN];
int v[MAXN<<1],ne[MAXN<<1],fir[MAXN],cnt=0;
void add(int a,int b){
    v[++cnt]=b,ne[cnt]=fir[a],fir[a]=cnt;
    v[++cnt]=a,ne[cnt]=fir[b],fir[b]=cnt;
}
int siz[MAXN],fa[MAXN],dep[MAXN];
int top[MAXN],son[MAXN],pos[MAXN],fp[MAXN],pcnt=0;
void dfs1(int x){
    siz[x]=1,son[x]=0;
    for(int i=fir[x];i!=-1;i=ne[i]) if(v[i]!=fa[x]){
        fa[v[i]]=x,dep[v[i]]=dep[x]+1;dfs1(v[i]);
        siz[x]+=siz[v[i]];
        if(siz[son[x]]<siz[v[i]]) son[x]=v[i];
    }
}
void dfs2(int x){
    pos[x]=++pcnt,fp[pcnt]=x;
    if(!son[x]) return;
    top[son[x]]=top[x],dfs2(son[x]);
    for(int i=fir[x];i!=-1;i=ne[i]) if(v[i]!=fa[x]&&v[i]!=son[x]){top[v[i]]=v[i];dfs2(v[i]);}
}
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
int sum[MAXN<<2],laz[MAXN<<2],lc[MAXN<<2],rc[MAXN<<2];
void inline pushup(int &rt){
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];if(rc[rt<<1]==lc[rt<<1|1]) sum[rt]--;
    lc[rt]=lc[rt<<1],rc[rt]=rc[rt<<1|1];
}
void inline pushdown(int &rt){
    if(laz[rt]){
        lc[rt<<1]=lc[rt<<1|1]=rc[rt<<1]=rc[rt<<1|1]=laz[rt<<1]=laz[rt<<1|1]=laz[rt],laz[rt]=0;
        sum[rt<<1]=sum[rt<<1|1]=1;
    }
}
void build(int l,int r,int rt){
    if(l==r){
        lc[rt]=rc[rt]=data[fp[l]],sum[rt]=1;
        return;
    }
    int mid=l+r>>1;
    build(lson);build(rson);
    pushup(rt);
}
void clr(int c,int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R){
        laz[rt]=lc[rt]=rc[rt]=c,sum[rt]=1;
        return;
    }
    pushdown(rt);
    int mid=l+r>>1;
    if(L<=mid) clr(c,L,R,lson);
    if(R>mid) clr(c,L,R,rson);
    pushup(rt);
}
void Clr(int x,int y,int c){
    int tx=top[x],ty=top[y];
    while(tx!=ty){
        if(dep[tx]>dep[ty]) clr(c,pos[tx],pos[x],1,n,1),x=fa[tx],tx=top[x];
        else clr(c,pos[ty],pos[y],1,n,1),y=fa[ty],ty=top[y];
    }
    if(dep[x]<dep[y]) swp(x,y);clr(c,pos[y],pos[x],1,n,1);
}
int qryclr(int p,int l,int r,int rt){
    if(l==r) return lc[rt];
    pushdown(rt);
    int mid=l+r>>1;
    if(p<=mid) return qryclr(p,lson);
    else return qryclr(p,rson);
}
int qry(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R) return sum[rt];
    pushdown(rt);
    int mid=l+r>>1,sm=0;
    if(L<=mid) sm+=qry(L,R,lson);
    if(R>mid) sm+=qry(L,R,rson);
    if(L<=mid&&R>mid&&rc[rt<<1]==lc[rt<<1|1]) return sm-1;
    return sm;
}
void Qry(int x,int y){
    int tx=top[x],ty=top[y],ans=0;
    while(tx!=ty){
        if(dep[tx]>dep[ty]) ans+=qry(pos[tx],pos[x],1,n,1),ans-=qryclr(pos[tx],1,n,1)==qryclr(pos[fa[tx]],1,n,1),x=fa[tx],tx=top[x];
        else ans+=qry(pos[ty],pos[y],1,n,1),ans-=qryclr(pos[ty],1,n,1)==qryclr(pos[fa[ty]],1,n,1),y=fa[ty],ty=top[y];
    }
    if(dep[x]<dep[y]) swp(x,y);ans+=qry(pos[y],pos[x],1,n,1);
    outint(ans),putchar('\n');
}
int main(){
    memset(laz,0,sizeof(laz));
    memset(fir,-1,sizeof(fir));
    memset(ne,-1,sizeof(ne));
    n=readint(),m=readint();
    for(int i=1;i<=n;i++) data[i]=readint();
    for(int i=1;i<n;i++) add(readint(),readint());
    siz[0]=fa[1]=dep[1]=0;dfs1(1);
    top[1]=1;dfs2(1);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        char opt[5];scanf("%s",opt);
        int a=readint(),b=readint();
        switch(opt[0]){
            case 'C':Clr(a,b,readint());break;
            case 'Q':Qry(a,b);break;
        }
    }
}
