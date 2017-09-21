#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxm 510005
int n,ch[maxm][26],tot=1,len,head[maxm],E[maxm],V[maxm],cnt=1;
int val[maxm],cnt2,size[maxm],sta[maxm],top;
long long ans,sum;
char line[maxm];
inline void edge_add(int u,int v)
{
    E[++cnt2]=head[u],V[cnt2]=v,head[u]=cnt2;
}
void dfs1(int now,int last)
{
    if(val[last]) edge_add(now,++cnt),now=cnt;
    for(int i=0;i<26;i++)
    {
        if(ch[last][i]) dfs1(now,ch[last][i]);
    }
}
void dfs2(int now)
{
    size[now]=1;
    for(int i=head[now];i;i=E[i])
    {
        dfs2(V[i]),size[now]+=size[V[i]];
    }
}
bool cmp(int x,int y)
{
    return size[x]<size[y];
}
void dfs3(int now,long long w)
{
    sum++,ans+=sum-w,w=sum;int l=top+1,r=top;
    for(int i=head[now];i;i=E[i]) sta[++r]=V[i];
    sort(sta+l,sta+r+1,cmp),top=r;
    for(int i=l;i<=r;i++) dfs3(sta[i],w);
    top=l-1;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",line),len=strlen(line);
        int now=1,pos;
        for(int v=len-1;v>=0;v--)
        {
            pos=line[v]-'a';
            if(!ch[now][pos]) ch[now][pos]=++tot;
            now=ch[now][pos];
        }
        val[now]=1;
    }
    dfs1(1,1),cnt=0,dfs2(1),dfs3(1,1),printf("%lld\n",ans);
    return 0;
}
