#include <bits/stdc++.h>
using namespace std;
#define maxn 10005
#define ll long long
int val[maxn];
struct LinkCutTreeType {
        int f[maxn],Max[maxn],ch[maxn][2],rev[maxn],sta[maxn],top,cnt[maxn];
        void updata(int now)
        {
            Max[now]=val[now];
            if(ch[now][1]) Max[now]=max(Max[now],Max[ch[now][1]]);
            if(ch[now][0]) Max[now]=max(Max[now],Max[ch[now][0]]);
        }
        void downdata(int now)
        {
            if(rev[now])
            {
                rev[now]^=1,swap(ch[now][1],ch[now][0]);
                if(ch[now][1]) rev[ch[now][1]]^=1;
                if(ch[now][0]) rev[ch[now][0]]^=1;
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
            if(ch[fa][l]) f[ch[fa][l]]=fa;updata(fa);
        }
        void splay(int now)
        {
            top=1,sta[1]=now;int fa,ffa;
            for(int i=now;!isroot(i);i=f[i]) sta[++top]=f[i];
            while(top) downdata(sta[top--]);
            while(!isroot(now))
            {
                fa=f[now],ffa=f[fa];
                if(!isroot(fa)) rotate(((ch[ffa][1]==fa)^(ch[fa][1]==now))?now:fa);
                rotate(now);
            }
            updata(now);
        }
        void access(int now)
        {
            for(int i=0;now;i=now,now=f[now]) splay(now),ch[now][1]=i;
        }
        void makeroot(int now)
        {
            access(now),splay(now),rev[now]^=1;
        }
        void cut(int x,int y)
        {
            makeroot(x),access(y),splay(y);
            f[x]=0,ch[y][0]=0,cnt[x]--,cnt[y]--;
        }
        void link(int x,int y)
        {
            makeroot(x),f[x]=y,splay(x),cnt[x]++,cnt[y]++;
        }
        bool iscon(int x,int y)
        {
            while(f[x]) x=f[x];
            while(f[y]) y=f[y];
            return x==y;
        }
        int query(int u,int v)
        {
            makeroot(u),access(v),splay(v);
            return Max[v];
        }
};
struct LinkCutTreeType lct[15];
int n,m,c,k;
map<ll,int>Map;
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
ll Mapped(int u,int v)
{
    if(u>v) swap(u,v);
    return (ll)u*n*n+v;
}
int main()
{
    //freopen("data.txt","r",stdin);
    //freopen("networkzj.in","r",stdin);
    //freopen("networkzj.out","w",stdout);
    in(n),in(m),in(c),in(k);int u,v,w,op;ll pos,id;
    for(int i=1;i<=n;i++) in(val[i]);
    while(m--) in(u),in(v),in(w),Map[Mapped(u,v)]=w+1,lct[w].link(u,v);
    while(k--)
    {
        in(op);
        if(op==0)
        {
            in(u),in(val[u]);
            for(int i=0;i<c;i++) lct[i].splay(u);
        }
        if(op==1)
        {
            in(u),in(v),in(w),id=Mapped(u,v),pos=Map[id]-1;
            if(pos<0)
            {
                puts("No such edge.");
                continue;
            }
            if(pos==w)
            {
                puts("Success.");
                continue;
            }
            if(lct[w].cnt[u]>=2||lct[w].cnt[v]>=2)
            {
                puts("Error 1.");
                continue;
            }
            if(lct[w].iscon(u,v))
            {
                puts("Error 2.");
                continue;
            }
            lct[pos].cut(u,v),lct[w].link(u,v),Map[id]=w+1;
            puts("Success.");
        }
        if(op==2)
        {
            in(w),in(u),in(v);
            if(!lct[w].iscon(u,v))
            {
                puts("-1");
                continue;
            }
            printf("%d\n",lct[w].query(u,v));
        }
    }
    return 0;
}
