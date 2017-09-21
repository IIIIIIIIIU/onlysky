#include <bits/stdc++.h>
using namespace std;
const int maxn=10005;
const int maxm=1000005;
struct node
{
    int id,t,val;
    bool operator<(const node &pos)const
    {
        if(val==pos.val) return t>pos.t;
        return val>pos.val;
    }
    bool operator==(const node &pos)const
    {
        return id==pos.id&&t==pos.t&&val==pos.val;
    }
    node(int id_,int t_,int val_)
    {
        id=id_,t=t_,val=val_;
    }
};
int n,m;
map<int,int>Map,Mapt;
priority_queue<node>que,que2;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(m);int pos,ans=0,cnt=0;
    node tmp(0,0,0);
    for(int i=1;i<=m;i++)
    {
        while(que2.size()&&que2.top()==que.top()) que.pop(),que2.pop();
        in(pos);
        if(Map[pos])
        {
            ans++;
            que2.push(node(pos,Mapt[pos],Map[pos]));
            que.push(node(pos,Mapt[pos],Map[pos]+=1));
        }
        else
        {
            if(cnt<n) que.push(node(pos,Mapt[pos]=i,Map[pos]=1)),cnt++;
            else
            {
                tmp=que.top();que.pop();
                Map[tmp.id]=0,que.push(node(pos,Mapt[pos]=i,Map[pos]=1));
            }
        }
    }
    cout<<ans;
    return 0;
}
