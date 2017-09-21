#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 100005
 
struct TreeNodeType {
    int lc,rc,dis;
};
struct TreeNodeType tree[maxn*21];
 
int n,ch[maxn][26],ff[maxn],fail[maxn],tot;
int bel[maxn],bel_[maxn],pn,pla[maxn],head[maxn];
int E[maxn<<1],V[maxn<<1],cnt,id[maxn],end[maxn];
int root[maxn],tot_,m,times[maxn],sta[maxn],top;
 
char str[maxn];
 
queue<int>que;
 
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
 
void dfs1(int now,int fa)
{
    id[now]=++cnt;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now);
    }
    end[now]=cnt;
}
 
void tree_build(int &now,int l,int r)
{
    now=++tot_;
    if(l==r) return ;
    int mid=l+r>>1;
    tree_build(tree[now].lc,l,mid);
    tree_build(tree[now].rc,mid+1,r);
}
 
void tree_add(int pre,int &now,int l,int r,int to)
{
    now=++tot_;
    tree[now].dis=tree[pre].dis+1;
    if(l==r) return ;
    int mid=l+r>>1;
    if(to<=mid) tree_add(tree[pre].lc,tree[now].lc,l,mid,to),tree[now].rc=tree[pre].rc;
    else tree_add(tree[pre].rc,tree[now].rc,mid+1,r,to),tree[now].lc=tree[pre].lc;
}
 
int tree_query(int now,int l,int r,int ll,int rr)
{
    if(l==ll&&rr==r) return tree[now].dis;
    int mid=l+r>>1;
    if(ll>mid) return tree_query(tree[now].rc,mid+1,r,ll,rr);
    else if(rr<=mid) return tree_query(tree[now].lc,l,mid,ll,rr);
    else return tree_query(tree[now].lc,l,mid,ll,mid)+tree_query(tree[now].rc,mid+1,r,mid+1,rr);
}
 
int main()
{
    scanf("%s",str),ff[1]=0,tot=1;
    int len=strlen(str),now=1,pos,temp;n=len;
    for(int i=0;i<len;i++)
    {
        if(str[i]=='P')
        {
            bel[i]=now,pla[++pn]=now;
            continue;
        }
        if(str[i]=='B')
        {
            now=ff[now];
            bel[i]=now;
            continue;
        }
        pos=str[i]-'a',bel_[i]=now;
        if(!ch[now][pos]) ch[now][pos]=++tot,ff[ch[now][pos]]=now;
        now=ch[now][pos],bel[i]=now;
    }
    que.push(1);int u,v;
    while(!que.empty())
    {
        now=que.front(),que.pop();
        for(int i=0;i<26;i++)
        {
            if(!ch[now][i]) continue;
            que.push(ch[now][i]);
            if(now==1) fail[ch[now][i]]=1;
            else
            {
                temp=fail[now];
                while(temp)
                {
                    if(ch[temp][i])
                    {
                        fail[ch[now][i]]=ch[temp][i];
                        break;
                    }
                    temp=fail[temp];
                }
                if(!temp) fail[ch[now][i]]=1;
            }
            u=ch[now][i],v=fail[ch[now][i]];
            E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
            E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
        }
    }
    cnt=0,dfs1(1,0),tree_build(root[0],1,n),now=0,pn=0;
    for(int i=0;i<len;i++)
    {
        if(str[i]=='B') top--;
        else if(str[i]=='P') times[++pn]=sta[top];
        else
        {
            tree_add(root[sta[top]],root[i+1],1,n,id[bel[i]]);
            sta[++top]=i+1;
        }
    }
    in(m);
    for(int i=1;i<=m;i++)
    {
        in(u),in(v);
        printf("%d\n",tree_query(root[times[v]],1,n,id[pla[u]],end[pla[u]]));
    }
    return 0;
}
