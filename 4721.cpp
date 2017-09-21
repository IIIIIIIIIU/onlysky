#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define ll long long
int n,m,que[maxn],u,v,t,ans[8000005],h=1,Q;
ll q;
queue<int>qmax,qmin,qall;
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
bool cmp(int a,int b)
{
    return a>b;
}
ll get(int now)
{
    int resa=-(0x7fffffff-1),resb=0;
    if(h<=n)
    {
        if(que[h]>resa) resa=que[h],resb=1;
    }
    if(!qmax.empty())
    {
        if(qmax.front()>resa) resa=qmax.front(),resb=2;
    }
    if(!qmin.empty())
    {
        if(qmin.front()>resa) resa=qmin.front(),resb=3;
    }
    if(resb==1) h++;
    else if(resb==2) qmax.pop();
    else qmin.pop();
    return resa+now*q;
}
int main()
{
    in(n),in(m),in(Q),in(u),in(v),in(t),q=Q;double pos;ll tmp1,tmp2;
    for(int i=1;i<=n;i++) in(que[i]);sort(que+1,que+n+1,cmp);
    for(int i=1;i<=m;i++)
    {
        pos=get(i-1);
        if(i%t==0)
        {
            if(i==t) printf("%lld",(ll)pos);
            else printf(" %lld",(ll)pos);
        }
        tmp1=pos*u/v,tmp2=pos-tmp1;
        if(tmp2>tmp1) swap(tmp1,tmp2);
        qmax.push(tmp1-q*i),qmin.push(tmp2-q*i);
    }
    putchar('\n');
    for(int i=1;i<=n+m;i++) ans[i]=get(0);
    if(t<=n+m) printf("%lld",ans[t]+m*q);
    for(int i=t*2;i<=n+m;i+=t) printf(" %lld",ans[i]+m*q);
    return 0;
}
