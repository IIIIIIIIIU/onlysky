/**************************************************************
    Problem: 3932
    User: onlysky
    Language: C++
    Result: Accepted
    Time:6692 ms
    Memory:202372 kb
****************************************************************/
 
#include <cstdio>
#include <iostream>
#include <algorithm>
  
#define maxn 100001
#define LL long long
  
using namespace std;
  
struct T_do {
    LL time,pi,dis;
};
struct T_do do_[maxn<<2];
  
struct TreeNodeType {
    LL l,r,dis,sum,bel;
      
    TreeNodeType *left,*right;
};
struct TreeNodeType *null,*root[maxn<<1];
  
LL if_z,n,m,num,hash[maxn<<1],size,bef;
  
char Cget;
  
bool if_[maxn<<1];
  
inline void read_LL(LL &now)
{
    if_z=1,now=0,Cget=getchar();
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
  
void tree_build(TreeNodeType *&now,LL l,LL r)
{
    now=new TreeNodeType;
    now->l=l,now->r=r;
    now->dis=0,now->sum=0;
    now->bel=0;
    now->left=null;
    now->right=null;
    if(l==r) return ;
    LL mid=(l+r)>>1;
    tree_build(now->left,l,mid);
    tree_build(now->right,mid+1,r);
}
  
bool cmp(struct T_do a1,struct T_do a2)
{
    return a1.time<a2.time;
}
  
void tree_change(TreeNodeType *&pre,TreeNodeType *&now,LL bel,LL dis,LL sum,LL to)
{
    now=new TreeNodeType;
    now->sum=pre->sum+sum;
    now->l=pre->l,now->r=pre->r;
    now->bel=bel,now->dis=pre->dis+dis;
    now->left=pre->left,now->right=pre->right;
    if(now->l==now->r) return ;
    LL mid=(now->l+now->r)>>1;
    if(to>mid) tree_change(pre->right,now->right,bel,dis,sum,to);
    else tree_change(pre->left,now->left,bel,dis,sum,to);
}
  
void tree_change_(TreeNodeType *&now,LL bel,LL dis,LL sum,LL to)
{
    if(now->bel!=bel)
    {
        TreeNodeType *tmp=new TreeNodeType;
        tmp->l=now->l,tmp->r=now->r;
        tmp->dis=now->dis,tmp->bel=bel;
        tmp->sum=now->sum,tmp->left=now->left;
        tmp->right=now->right;
        now=tmp;
    }
    now->dis+=dis,now->sum+=sum;
    if(now->l==now->r) return ;
    LL mid=(now->l+now->r)>>1;
    if(to>mid) tree_change_(now->right,bel,dis,sum,to);
    else tree_change_(now->left,bel,dis,sum,to);
}
  
LL tree_query(TreeNodeType *now,LL k)
{
    if(now->l==now->r) return now->sum/now->dis*k;
    if(k<=now->left->dis) return tree_query(now->left,k);
    else return tree_query(now->right,k-now->left->dis)+now->left->sum;
}
  
int main()
{
    read_LL(m),read_LL(n);
    LL pi,ai,bi;
    for(LL i=1;i<=m;i++)
    {
        read_LL(ai),read_LL(bi),read_LL(pi);
        num++,do_[num].dis=1,do_[num].pi=pi,do_[num].time=ai;
        num++,do_[num].dis=-1,do_[num].pi=-pi,do_[num].time=bi+1;
        hash[i]=pi;
    }
    sort(hash+1,hash+m+1);
    size=unique(hash+1,hash+m+1)-hash-1;
    null=new TreeNodeType;
    null->l=0,null->r=0;
    null->dis=0,null->sum=0;
    null->bel=0;
    null->left=null;
    null->right=null;
    tree_build(root[0],1,size);
    sort(do_+1,do_+num+1,cmp);
    for(LL i=1;i<=num;i++)
    {
        for(LL j=do_[i-1].time+1;j<do_[i].time;j++)
        {
            root[j]=root[do_[i-1].time];
        }
        LL pi_;
        if(do_[i].pi<0) pi_=lower_bound(hash+1,hash+size+1,-do_[i].pi)-hash;
        else pi_=lower_bound(hash+1,hash+size+1,do_[i].pi)-hash;
        if(!if_[do_[i].time])
        {
            if_[do_[i].time]=true;
            tree_change(root[do_[i-1].time],root[do_[i].time],do_[i].time,do_[i].dis,do_[i].pi,pi_);
        }
        else
        {
            tree_change_(root[do_[i].time],do_[i].time,do_[i].dis,do_[i].pi,pi_);
        }
    }
    LL pre_=1;
    LL xi,ci;
    for(LL i=1;i<=n;i++)
    {
        read_LL(xi),read_LL(ai),read_LL(bi),read_LL(ci);
        pre_=1+((ai*pre_+bi)%ci);
        LL res;
        if(root[xi]->dis>pre_) res=tree_query(root[xi],pre_);
        else res=root[xi]->sum;
        cout<<res;
        putchar('\n');
        pre_=res;
    }
    return 0;
}
