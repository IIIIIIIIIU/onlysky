#include <bits/stdc++.h>
using namespace std;
#define maxn 400005
#define INF 0x3f3f3f3f
int n,val[maxn],sum[maxn],Max[maxn],Min[maxn],ch[maxn][2];
int rev[maxn],flag[maxn],f[maxn],top,st[maxn],m,cur[maxn],id;
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
void updata(int now)
{
    int l=ch[now][0],r=ch[now][1];
    Max[now]=max(Max[l],Max[r]);
    Min[now]=min(Min[l],Min[r]);
    if(now>n) Max[now]=max(Max[now],val[now]);
    if(now>n) Min[now]=min(Min[now],val[now]);
    sum[now]=sum[l]+sum[r]+val[now];
}
void rever(int now)
{
    sum[now]=-sum[now];
    val[now]=-val[now];
    swap(Max[now],Min[now]);
    Min[now]=-Min[now];
    Max[now]=-Max[now];
    flag[now]^=1;
}
void pushdown(int now)
{
    int l=ch[now][0],r=ch[now][1];
    if(flag[now])
    {
        flag[now]=0;
        if(l) rever(l);
        if(r) rever(r);
    }
    if(rev[now])
    {
        rev[now]^=1,rev[l]^=1,rev[r]^=1;
        swap(ch[now][0],ch[now][1]);
    }
}
bool isroot(int now)
{
    return (ch[f[now]][0]!=now)&&(ch[f[now]][1]!=now);
}
void rotate(int &now)
{
    int fa=f[now],ffa=f[fa],l,r;
    if(ch[fa][0]==now) l=0;else l=1;r=l^1;
    if(!isroot(fa))
    {
        if(ch[ffa][0]==fa) ch[ffa][0]=now;
        else ch[ffa][1]=now;
    }
    f[now]=ffa,f[fa]=now,f[ch[now][r]]=fa;
    ch[fa][l]=ch[now][r],ch[now][r]=fa;
    updata(fa),updata(now);
}
void splay(int now)
{
    top=0;st[++top]=now;
    for(int i=now;!isroot(i);i=f[i]) st[++top]=f[i];
    while(top) pushdown(st[top--]);
    while(!isroot(now))
    {
        int fa=f[now],ffa=f[fa];
        if(!isroot(fa))
        {
            if(ch[fa][0]==now^ch[ffa][0]==fa) rotate(now);
            else rotate(fa);
        }
        rotate(now);
    }
}
void access(int now)
{
    for(int t=0;now;t=now,now=f[now]) splay(now),ch[now][1]=t,updata(now);
}
void makeroot(int now)
{
    access(now);
    splay(now);
    rev[now]^=1;
}
void split(int x,int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x,int y)
{
    makeroot(x),f[x]=y;
}
int main()
{
    in(n);
    for(int i=0;i<=n;i++) Max[i]=-INF,Min[i]=INF;
    int u,v,w;id=n;
    for(int i=1;i<n;i++)
    {
        in(u),in(v),in(w),cur[i]=++id;
        link(u+1,id),link(v+1,id);
        val[id]=sum[id]=Max[id]=Min[id]=w;
    }
    in(m);
    char ch[10];
    while(m--)
    {
        scanf("%s",ch),in(u),in(v);
        if(ch[0]=='C') splay(cur[u]),val[cur[u]]=v,updata(cur[u]);
        else if(ch[0]=='N') split(u+1,v+1),rever(v+1);
        else if(ch[0]=='S') split(u+1,v+1),printf("%d\n",sum[v+1]);
        else if(ch[1]=='A') split(u+1,v+1),printf("%d\n",Max[v+1]);
        else split(u+1,v+1),printf("%d\n",Min[v+1]);
    }
    return 0;
}
