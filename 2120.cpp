#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define K 2000001
#define N 10001
#define M 1001
using namespace std;
int n,m,siz,now,tot,tmp;
int col[K],sum[K],original[K];
struct QUERY
{
    int l,r,bl,id,ans;
    int tim;    
}e[N];
struct CNANGE
{
    int before,after,pos;
}ch[M];
bool cmp1(QUERY q,QUERY p)
{
    if(q.bl!=p.bl) return q.bl<p.bl;
    if(q.r!=p.r) return q.r<p.r;
    return q.tim<p.tim;
}
bool cmp2(QUERY q,QUERY p)
{
    return q.id<p.id;
}
void update(int to,int w)
{
    sum[to]+=w;
    if(w==1 && sum[to]==1) tmp++;
    if(w==-1 && !sum[to]) tmp--;
}
int main()
{
    scanf("%d%d",&n,&m);
    siz=sqrt(n);
    for(int i=1;i<=n;i++) scanf("%d",&col[i]),original[i]=col[i];
    char c[2]; int l,r;
    while(m--)
    {
        scanf("%s%d%d",c,&l,&r);
        if(c[0]=='Q')
        {
            ++tot;
            e[tot].l=l; e[tot].r=r; e[tot].id=tot; e[tot].bl=(l-1)/siz+1;
            e[tot].tim=now;
        }
        else ch[++now].after=r,ch[now].pos=l;
    }
    sort(e+1,e+tot+1,cmp1);
    int L=1,R=0; now=0;
    for(int i=1;i<=tot;i++)
    {
        while(now<e[i].tim)
        {
            now++;
            ch[now].before=col[ch[now].pos];
            if(ch[now].pos>=L&&ch[now].pos<=R) update(ch[now].before,-1),update(ch[now].after,1);
            col[ch[now].pos]=ch[now].after;
        }
        while(now>e[i].tim)
        {
            if(ch[now].pos>=L&&ch[now].pos<=R) update(ch[now].after,-1),update(ch[now].before,1);
            col[ch[now].pos]=ch[now].before;
            now--;
        }
        while(L<e[i].l) update(col[L++],-1);
        while(L>e[i].l) update(col[--L],1);
        while(R<e[i].r) update(col[++R],1);
        while(R>e[i].r) update(col[R--],-1); 
        e[i].ans=tmp;
    }
    sort(e+1,e+tot+1,cmp2);
    for(int i=1;i<=tot;i++) printf("%d\n",e[i].ans);
    return 0;
}
