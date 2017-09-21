#include <cstdio>
#include <iostream>
 
using namespace std;
 
class node {
    public:
         
        int l,r,mid;
         
        long long int dis;
         
        void mid_()
        {
            mid=(l+r)>>1;
        }
};
class node tree[800001];
 
int m,d,num_q=0,q_l[200100],q_r[200100];
int num_a,a_[200010],cnt=0;
 
long long int t;
 
inline void tree_up(int now)
{
    if(tree[now<<1].dis>tree[now<<1|1].dis)
    {
        tree[now].dis=tree[now<<1].dis;
    }
    else tree[now].dis=tree[now<<1|1].dis;
}
 
void tree_build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r;
    if(l==r)
    {
        tree[now].dis=a_[++cnt];
        return ;
    }
    tree[now].mid_();
    tree_build(now<<1,l,tree[now].mid);
    tree_build(now<<1|1,tree[now].mid+1,r);
    tree_up(now);
}
 
void tree_change(int now,int to)
{
    if(tree[now].l==tree[now].r&&tree[now].l==to)
    {
        tree[now].dis=(tree[now].dis+t)%d;
        return ;
    }
    if(to>tree[now].mid) tree_change(now<<1|1,to);
    else tree_change(now<<1,to);
    tree_up(now);
}
 
long long int tree_query(int now,int l,int r)
{
    if(tree[now].l==l&&tree[now].r==r)
    {
        return tree[now].dis;
    }
    if(l>tree[now].mid) return tree_query(now<<1|1,l,r);
    else if(r<=tree[now].mid) return tree_query(now<<1,l,r);
    else return max(tree_query(now<<1,l,tree[now].mid),tree_query(now<<1|1,tree[now].mid+1,r));
}
 
int main()
{
    char ch;
    int now_;
    scanf("%d%d",&m,&d);
    for(int i=1;i<=m;i++)
    {
        cin>>ch>>now_;
        if(ch=='Q')
        {
            num_q++;
            q_l[num_q]=num_a-now_+1;
            q_r[num_q]=num_a;
        }
        else
        {
            num_a++;
            a_[num_a]=now_;
        }
    }
    tree_build(1,1,num_a);
    cnt=0;
    for(int i=1;i<=num_q;i++)
    {
        while(cnt<q_r[i])
        {
            tree_change(1,++cnt);
        }
        t=tree_query(1,q_l[i],q_r[i]);
        printf("%d\n",t);
    }
    return 0;
}
