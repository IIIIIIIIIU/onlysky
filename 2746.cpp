#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 1000005
#define mod 1000000007LL
 
struct TreeNodeType {
    int id;
     
    long long dis;
     
    TreeNodeType *next[26],*fail;
     
    TreeNodeType()
    {
        id=0,dis=0,fail=NULL;
        for(int i=0;i<26;i++) next[i]=NULL;
    }
};
struct TreeNodeType *map[maxn<<1],*que[maxn<<1],*root;
 
int n,m,deep[maxn<<1],f[maxn<<1],top[maxn<<1],head[maxn<<1];
int E[maxn<<2],V[maxn<<2],tot,cnt,len,size[maxn<<1];
 
char ch[maxn<<1];
 
vector<int>vec[maxn<<1];
 
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
    f[now]=fa,deep[now]=deep[fa]+1,size[now]=1;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dfs1(V[i],now),size[now]+=size[V[i]];
    }
}
 
void dfs2(int now,int chain)
{
    top[now]=chain;int pos=0;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==f[now]) continue;
        if(size[V[i]]>size[pos]) pos=V[i];
    }
    if(pos) dfs2(pos,chain);else return ;
    for(int i=head[now];i;i=E[i])
    {
        if(V[i]==pos||V[i]==f[now]) continue;
        dfs2(V[i],V[i]);
    }
}
 
inline int lca(int x,int y)
{
    for(;top[x]!=top[y];)
    {
        if(deep[top[x]]<deep[top[y]]) swap(x,y);
        x=f[top[x]];
    }
    if(deep[x]>deep[y]) swap(x,y);
    return x;
}
 
int main()
{
    in(n);root=new TreeNodeType;
    root->id=++tot,map[root->id]=root;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch),len=strlen(ch);
        TreeNodeType *now=root;int pos;
        for(int j=0;j<len;j++)
        {
            pos=ch[j]-'a';
            if(now->next[pos]==NULL)
            {
                now->next[pos]=new TreeNodeType,now->next[pos]->id=++tot;
                map[tot]=now->next[pos],now->next[pos]->dis=(now->dis*26LL+pos)%mod;
            }
            vec[i].push_back(now->next[pos]->id),now=now->next[pos];
        }
    }
    int h=0,tail=1,u,v;que[0]=root;
    while(h<tail)
    {
        TreeNodeType *now=que[h++],*temp=NULL;
        for(int i=0;i<26;i++)
        {
            if(now->next[i]==NULL) continue;
            if(now==root) now->next[i]->fail=root;
            else
            {
                temp=now->fail;
                while(temp!=NULL)
                {
                    if(temp->next[i]!=NULL)
                    {
                        now->next[i]->fail=temp->next[i];
                        break;
                    }
                    temp=temp->fail;
                }
                if(temp==NULL) now->next[i]->fail=root;
            }
            que[tail++]=now->next[i];
            u=now->next[i]->id,v=now->next[i]->fail->id;
            E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
            E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
        }
    }
    dfs1(1,0),dfs2(1,1);
    in(m);int a,a1,b,b1;
    for(;m--;)
    {
        in(a),in(a1),in(b),in(b1);
        printf("%lld\n",map[lca(vec[a][a1-1],vec[b][b1-1])]->dis);
    }
    return 0;
}
