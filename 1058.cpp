#pragma GCC optimize("O2")
#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
  
using namespace std;
  
#define maxn 1000005
  
class HeadType {
    private:
        int head[maxn*2],cnt;
          
    public:
        bool size()
        {
            return cnt;
        }
          
        int top()
        {
            if(!cnt) return 0x7fffffff;
            return head[1];
        }
          
        inline void push(int x)
        {
            head[++cnt]=x;
            int now=cnt,tmp;
            while(now>1)
            {
                if(head[now>>1]>head[now]) tmp=head[now],head[now]=head[now>>1],now>>=1,head[now]=tmp;
                else break;
            }
        }
          
        inline void pop()
        {
            head[1]=head[cnt--];
            if(cnt==0) return ;
            int pos,pos_,now=1;
            while(1)
            {
                pos=now,pos_=head[now];
                if((now<<1)<=cnt&&head[now<<1]<head[pos]) pos=now<<1,pos_=head[now<<1];
                if((now<<1|1)<=cnt&&head[now<<1|1]<head[pos]) pos=now<<1|1,pos_=head[now<<1|1];
                if(pos==now) return ;
                head[pos]=head[now],head[now]=pos_,now=pos;
            }
        }
};
class HeadType ai,bi,ci;
  
struct ListType {
    int pre,dis;
};
struct ListType bili[maxn];
  
int n,m,vi[maxn],tot;
  
set<int>so;
  
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
  
int main()
{
    in(n),in(m);bili[0].dis=1e9,bili[n+1].dis=1e9,tot=n+1;
    for(int i=1;i<=n;i++)
    {
        bili[i].pre=i-1,in(bili[i].dis);
        ai.push(abs(bili[i].dis-bili[i-1].dis));
        so.insert(bili[i].dis),vi[i]=bili[i].dis;
    }
    sort(vi+1,vi+n+1),bili[n+1].pre=n,ai.push(abs(bili[n+1].dis-bili[bili[n+1].pre].dis));
    for(int i=2;i<=n;i++) ci.push(abs(vi[i]-vi[i-1]));
    char op[15];int p,x;
    for(;m--;)
    {
        scanf("%s",op);
        if(op[0]=='I')
        {
            in(p),in(x);p++;
            bi.push(abs(bili[p].dis-bili[bili[p].pre].dis));
            ai.push(abs(x-bili[bili[p].pre].dis)),ai.push(abs(bili[p].dis-x));
            bili[++tot].pre=bili[p].pre,bili[tot].dis=x,bili[p].pre=tot;
            set<int>::iterator it=so.lower_bound(x);
            if(it!=so.end()) ci.push(abs(*it-x));
            if(it!=so.begin()) it--,ci.push(abs(*it-x));
            so.insert(x);
        }
        else if(op[4]=='S') printf("%d\n",ci.top());
        else
        {
            while(ai.top()==bi.top()) ai.pop(),bi.pop();
            printf("%d\n",ai.top());
        }
    }
    return 0;
}
