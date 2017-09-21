#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
struct node
{
    int id,key;
    bool operator<(const node &pos)const
    {
        if(key==pos.key) return id>pos.id;
        return key<pos.key;
    }
    bool operator==(const node &pos)const
    {
        return id==pos.id&&key==pos.key;
    }
    node(int id_,int key_)
    {
        id=id_,key=key_;
    }
};
int n,m,Next[maxn],last[maxn],ai[maxn],bi[maxn],cnt,ans,pre[maxn];
bool vis[maxn];
priority_queue<node>que,que2;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++) in(ai[i]),bi[i]=ai[i];
    sort(bi+1,bi+n+1),cnt=unique(bi+1,bi+n+1)-bi-1;
    for(int i=1;i<=n;i++) ai[i]=lower_bound(bi+1,bi+cnt+1,ai[i])-bi;
    for(int i=1;i<=n;i++)
    {
        if(last[ai[i]]) Next[last[ai[i]]]=i;
        pre[i]=last[ai[i]];
        last[ai[i]]=i;
    }
    for(int i=1;i<=n;i++) if(last[ai[i]]) Next[last[ai[i]]]=n+1;
    for(int i=1;i<=n;i++)
        if(!vis[ai[i]])
        {
            ans++,vis[ai[i]]=true;
            while(que.size()&&que2.size()&&que.top()==que2.top()) que2.pop(),que.pop();
            if(que.size()-que2.size()<m) que.push(node(ai[i],Next[i]));
            else
            {
                node tmp=que.top();
                vis[tmp.id]=false;
                que.pop();
                que.push(node(ai[i],Next[i]));
            }
        }
        else if(pre[i]) que.push(node(ai[i],Next[i])),que2.push(node(ai[i],i));
    cout<<ans;
    return 0;
}
