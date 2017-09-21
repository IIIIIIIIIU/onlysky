#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF=1e15;
const ll maxn=100005;
struct node
{
    ll id,val;
    bool operator<(const node pos)const
    {
        if(val==pos.val) return id<pos.id;
        return val>pos.val;
    }
    bool operator==(const node pos)const
    {
        return val==pos.val&&id==pos.id;
    }
    node(ll id_,ll val_)
    {
        id=id_,val=val_;
    }
};
ll ai[maxn],f[maxn],n,k,l[maxn],r[maxn],ans,bi[maxn];
priority_queue<node>que1,que2;
inline void in(ll &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(k);
    for(ll i=1;i<=n;i++) in(ai[i]);
    for(int i=1;i<n;i++) bi[i]=ai[i+1]-ai[i],l[i]=i-1,r[i]=i+1;
    for(ll i=1;i<n;i++) que1.push(node(i,bi[i]));
    que1.push(node(0,INF)),que1.push(node(n,INF)),r[0]=1,l[n]=n-1,bi[0]=bi[n]=INF;
    while(k--)
    {
        while(que2.size()&&que1.top()==que2.top())
            que1.pop(),que2.pop();
        node tmp=que1.top();
        ans+=tmp.val,que1.pop();
        int pos=tmp.id;
        if(l[pos]>=0) que2.push(node(l[pos],bi[l[pos]])),tmp.val-=bi[l[pos]],l[pos]=l[l[pos]],r[l[pos]]=pos;
        if(r[pos]<=n) que2.push(node(r[pos],bi[r[pos]])),tmp.val-=bi[r[pos]],r[pos]=r[r[pos]],l[r[pos]]=pos;
        tmp.val=-tmp.val,bi[pos]=tmp.val,que1.push(tmp);
    }
    cout<<ans;
    return 0;
}
