#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using std::min;
using std::max;
using std::lower_bound;
const int maxn=20005,maxtree=maxn<<2|1,INF=0x3f3f3f3f;
class TreeType
{
    private:
        struct node
        {
            int l,r,mid,val,tag;
            node *lc,*rc;
            node(int _l=0,int _r=0,int _mid=0,int _val=0)
            {
                l=_l,r=_r,mid=_mid,val=_val,tag=0;
                lc=rc=NULL;
            }
        };
        struct node *root;
        void build(node *&now,int l,int r)
        {
            now=new node(l,r,l+r>>1);
            if(l==r) return;
            build(now->lc,l,now->mid);
            build(now->rc,now->mid+1,r);
        }
        void pushdown(node *now)
        {
            now->lc->val+=now->tag;
            now->rc->val+=now->tag;
            now->lc->tag+=now->tag;
            now->rc->tag+=now->tag;
            now->tag=0;
        }
        void change(node *now,int l,int r,int x)
        {
            if(now->l>=l&&now->r<=r)
            {
                now->val+=x;
                now->tag+=x;
                return;
            }
            if(now->tag) pushdown(now);
            if(l<=now->mid) change(now->lc,l,r,x);
            if(r>now->mid) change(now->rc,l,r,x);
            now->val=min(now->lc->val,now->rc->val);
        }
        int query(node *now,int l,int r)
        {
            if(now->l>=l&&now->r<=r) return now->val;
            if(now->tag) pushdown(now);
            int res=INF;
            if(l<=now->mid) res=min(res,query(now->lc,l,r));
            if(r>now->mid) res=min(res,query(now->rc,l,r));
            return res;
        }
        void setit(node *now,int to,int x)
        {
            if(now->l==now->r)
            {
                now->val=x;
                now->tag=0;
                return;
            }
            if(now->tag) pushdown(now);
            if(to<=now->mid) setit(now->lc,to,x);
            else setit(now->rc,to,x);
            now->val=min(now->lc->val,now->rc->val);
        }
    public:
        inline void Build(int l,int r)
        {
            build(root,l,r);
        }
        inline void UpData(int l,int r,int x)
        {
            change(root,l,r,x);
        }
        inline int Query(int l,int r)
        {
            return query(root,l,r);
        }
        inline void Setit(int to,int x)
        {
            setit(root,to,x);
        }
};
class TreeType tree[2];
int n,m,dist[maxn],cost[maxn],s[maxn],w[maxn],li[maxn],ri[maxn],ans;
int headl[maxn],El[maxn],Vl[maxn],cntl,headr[maxn],Er[maxn],Vr[maxn],cntr;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
//  freopen("base.in","r",stdin);
//  freopen("base.out","w",stdout);
//  freopen("data.txt","r",stdin);
//  freopen("out.txt","w",stdout);
    in(n),in(m);
    for(int i=2;i<=n;i++) in(dist[i]);
    for(int i=1;i<=n;i++) in(cost[i]);
    for(int i=1;i<=n;i++) in(s[i]);
    for(int i=1;i<=n;i++) in(w[i]);
//  n++,dist[n]=cost[n]=c[n]=INF;
    dist[n+1]=INF,w[n+1]=INF,s[n+1]=INF,n++,m++;
    tree[0].Build(1,n),tree[1].Build(1,n);
    for(int i=1;i<=n;i++)
    {
        li[i]=lower_bound(dist+1,dist+n+1,dist[i]-s[i])-dist;
        ri[i]=lower_bound(dist+1,dist+n+1,dist[i]+s[i])-dist;
        if(dist[i]+s[i]<dist[ri[i]]) ri[i]--;
        El[++cntl]=headl[li[i]],Vl[cntl]=i,headl[li[i]]=cntl;
        Er[++cntr]=headr[ri[i]],Vr[cntr]=i,headr[ri[i]]=cntr;
//      printf("%d %d\n",ri[i],i);
    }
    int now,last;
    for(int i=1;i<=m;i++)
    {
        now=i%2,last=now^1;
        if(i==1)
        {
            int tmp=0;
            for(int v=1;v<=n;v++)
            {
                tree[now].UpData(v,v,tmp+cost[v]);
                for(int e=headr[v];e;e=Er[e])
                {
//                  printf("tmp %d\n",tmp);
                    tmp+=w[Vr[e]];
                }
//              printf("%d ",tree[now].Query(v,v));
            }
            ans=max(ans,tree[now].Query(n,n));
//          printf("\n");
            continue;
        }
        if(i==3)
        {
            int efw=0;
        }
        for(int v=1;v<=n;v++)
        {
//          if(v!=1) tree[now].UpData(v,v,tree[last].Query(1,v-1)+cost[v]);
//          else tree[now].UpData(v,v,cost[v]);
            if(v!=1) tree[now].Setit(v,tree[last].Query(1,v-1)+cost[v]);
            else tree[now].Setit(v,cost[v]);
            for(int e=headr[v];e;e=Er[e])
                if(li[Vr[e]]-1>=1)
                    tree[last].UpData(1,li[Vr[e]]-1,w[Vr[e]]);
//          printf("%d ",tree[now].Query(v,v));
        }
        ans=min(ans,tree[now].Query(n,n));
//      printf("\n");
    }
    using std::cout;
    cout<<ans;
    return 0;
}
