#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
int n,m,S,Q,top,f[maxn],maxa[maxn],maxb[maxn],ans[maxn],opcnt,siz[maxn];
struct data
{
    int x,y,a,b,id;
};
struct data e[maxn],q[maxn],stk[maxn];
struct oper
{
    int x,y,f,maxa,maxb,siz;
};
struct oper op[maxn];
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
bool operator<(const data &x,const data &y)
{
    return x.a==y.a?x.b<y.b:x.a<y.a;
}
bool cmp(const data &x,const data &y)
{
    return x.b==y.b?x.a<y.a:x.b<y.b;
}
int find(int x)
{
    return f[x]==x?x:find(f[x]);
}
void merge(int x,int y,int a,int b)
{
    x=find(x),y=find(y);
    if(siz[x]>siz[y]) swap(x,y);
    op[++opcnt]=(oper){x,y,f[x],maxa[y],maxb[y],siz[y]};
    if(x==y)
    {
        maxa[y]=max(maxa[y],a),maxb[y]=max(maxb[y],b);
        return;
    }
    f[x]=y,siz[y]+=siz[x];
    maxa[y]=max(maxa[x],max(maxa[y],a));
    maxb[y]=max(maxb[x],max(maxb[y],b));
}
void goback()
{
    for(int i=opcnt;i;i--)
    {
        int x=op[i].x,y=op[i].y;
        f[x]=op[i].f,maxa[y]=op[i].maxa,maxb[y]=op[i].maxb,siz[y]=op[i].siz;
    }
    opcnt=0;
}
int main()
{
    in(n),in(m),S=(int)sqrt(m);
    for(int i=1;i<=m;i++) in(e[i].x),in(e[i].y),in(e[i].a),in(e[i].b),e[i].id=i;
    sort(e+1,e+m+1),in(Q);
    for(int i=1;i<=Q;i++) in(q[i].x),in(q[i].y),in(q[i].a),in(q[i].b),q[i].id=i;
    sort(q+1,q+Q+1,cmp);
    for(int i=1;i<=m;i+=S)
    {
        top=0;
        for(int v=1;v<=Q;v++)
            if(q[v].a>=e[i].a&&(i+S>m||q[v].a<e[i+S].a)) stk[++top]=q[v];
        sort(e+1,e+i+1,cmp);
        for(int v=1;v<=n;v++) f[v]=v,maxa[v]=maxb[v]=-1,siz[v]=1;
        for(int v=1,k=1;v<=top;v++)
        {
            for(;k<i&&e[k].b<=stk[v].b;k++)
                merge(e[k].x,e[k].y,e[k].a,e[k].b);
            opcnt=0;
            for(int l=i;l<i+S&&l<=m;l++)
                if(e[l].a<=stk[v].a&&e[l].b<=stk[v].b)
                    merge(e[l].x,e[l].y,e[l].a,e[l].b);
            int x=find(stk[v].x),y=find(stk[v].y);
            ans[stk[v].id]=(x==y&&maxa[x]==stk[v].a&&maxb[x]==stk[v].b);
            goback();
        }
    }
    for(int i=1;i<=Q;i++) puts(ans[i]?"Yes":"No");
    return 0;
}
