#include <bits/stdc++.h>
using namespace std;
#define maxn 3005
#define ll long long
#define maxm 70002<<2
#define INF 1e13
struct NodeType {
    ll id,dis;
    bool operator<(const NodeType pos)const
    {
        return dis>pos.dis;
    }
};
ll n,m,E1[maxm],V1[maxm],W[maxm],head1[maxn];
ll cnt1,cnt2,E2[maxm],V2[maxm],head2[maxn],dis1[maxn];
ll dis2[maxn],du[maxn];
bool vis[maxn];
priority_queue<NodeType>que;
inline void in(ll &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void edge_add(ll u,ll v,ll w)
{
    E1[++cnt1]=head1[u],V1[cnt1]=v,W[cnt1]=w,head1[u]=cnt1;
}
void edge_add(ll u,ll v)
{
    E2[++cnt2]=head2[u],V2[cnt2]=v,head2[u]=cnt2;
}
NodeType node(ll id_,ll dis_)
{
    NodeType res;
    res.id=id_,res.dis=dis_;
    return res;
}
int main()
{
    in(n),in(m);ll u,v,w;
    while(m--) in(u),in(v),in(w),edge_add(u,v,w);
    for(ll i=1;i<=n;i++)
    {
        in(u),dis1[i]=INF;
        while(u--) in(v),edge_add(v,i),du[i]++;
    }
    dis1[1]=dis2[1]=0,que.push(node(1,0));
    while(!que.empty())
    {
        NodeType now=que.top();que.pop();
        if(vis[now.id]) continue;
        vis[now.id]=true;
        for(ll i=head1[now.id];i;i=E1[i])
        {
            if(dis1[V1[i]]>max(dis1[now.id],dis2[now.id])+W[i])
            {
                dis1[V1[i]]=max(dis1[now.id],dis2[now.id])+W[i];
                if(!du[V1[i]]) que.push(node(V1[i],max(dis1[V1[i]],dis2[V1[i]])));
            }
        }
        for(ll i=head2[now.id];i;i=E2[i])
        {
            dis2[V2[i]]=max(dis2[V2[i]],max(dis1[now.id],dis2[now.id]));
            if(!(--du[V2[i]])) que.push(node(V2[i],max(dis1[V2[i]],dis2[V2[i]])));
        }
    }
    cout<<max(dis1[n],dis2[n]);
    return 0;
}
