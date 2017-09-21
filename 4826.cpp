#include <bits/stdc++.h>
using namespace std;
#define maxn 200005
#define ll long long
#define maxtree maxn*30
class PTreeType
{
    private:
        int ch[maxtree][2],root[maxn],tot,head[maxn],li[maxn<<1],ri[maxn<<1],E[maxn<<1],cnt,val_[maxn<<1];
        ll val[maxtree],tag[maxtree];
    public:
        void add(int &now,int pre,int l,int r,int tl,int tr,ll x)
        {
            now=++tot,val[now]=val[pre],tag[now]=tag[pre];
            val[now]+=((r<tr?r:tr)-(l>tl?l:tl)+1)*x;
            ch[now][0]=ch[pre][0],ch[now][1]=ch[pre][1];
            if(l>=tl&&r<=tr){tag[now]+=x;return;}int mid=l+r>>1;
            if(tl<=mid) add(ch[now][0],ch[pre][0],l,mid,tl,tr,x);
            if(tr>mid) add(ch[now][1],ch[pre][1],mid+1,r,tl,tr,x);
        }
        ll query(int now,int pre,int l,int r,int tl,int tr)
        {
            if(l>=tl&&r<=tr) return val[now]-val[pre];
            int mid=l+r>>1;ll res=((r<tr?r:tr)-(l>tl?l:tl)+1)*(tag[now]-tag[pre]);
            if(tl<=mid) res+=query(ch[now][0],ch[pre][0],l,mid,tl,tr);
            if(tr>mid) res+=query(ch[now][1],ch[pre][1],mid+1,r,tl,tr);
            return res;
        }
        void add(int l,int r,int size,int x,int to)
        {
            add(root[to],root[to],1,size,l,r,x);
        }
        ll query(int l,int r,int size,int now,int pre)
        {
            return query(root[now],root[pre],1,size,l,r);
        }
        void operation_add(int to,int l,int r,int pi)
        {
            E[++cnt]=head[to],li[cnt]=l,ri[cnt]=r,val_[cnt]=pi,head[to]=cnt;
        }
        void makeit(int size)
        {
            for(int i=1;i<=size;i++)
            {
                root[i]=root[i-1];
                for(int v=head[i];v;v=E[v])
                {
                    add(li[v],ri[v],size,val_[v],i);
                }
            }
        }
};
class PTreeType xtree,ytree;
struct NodeType {
    int l,r;
};
struct NodeType ai[maxn];
int n,m,p1,p2,ki[maxn],sta[maxn];
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
inline void in(ll &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
int main()
{
    in(n),in(m),in(p1),in(p2);int top=0,op,l,r;ll ans;
    for(int i=1;i<=n;i++)
    {
        in(ki[i]);
        while(top&&ki[sta[top]]<ki[i]) ai[sta[top]].r=i,top--;
        ai[i].l=sta[top],sta[++top]=i;
    }
    while(top) ai[sta[top]].r=n+1,top--;
    for(int i=1;i<=n;i++)
    {
        if(ai[i].l>0&&ai[i].r<=n) xtree.operation_add(ai[i].l,ai[i].r,ai[i].r,p1);
        if(i+1<=ai[i].r-1) xtree.operation_add(ai[i].l,i+1,ai[i].r-1,p2);
        if(ai[i].l+1<=i-1) ytree.operation_add(ai[i].r,ai[i].l+1,i-1,p2);
    }
    xtree.makeit(n),ytree.makeit(n);
    while(m--)
    {
        in(l),in(r),ans=0;
        ans+=xtree.query(l,r,n,r,l-1);
        ans+=ytree.query(l,r,n,r,l-1);
        ans+=(ll)p1*(r-l);
        printf("%lld\n",ans);
    }
    return 0;
}
