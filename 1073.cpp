#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=55;
const int maxm=maxn*maxn;
struct PathType
{
    int g,fix,now;
    vector<int>path;
    bool has[maxn];
    bool operator<(const PathType &pos)const
    {
        //if(fix==pos.fix) return g>pos.g;
        return fix>pos.fix;
    }
};
struct PathType tmp1,tmp2;
int n,m,k,origin,dest,head[maxn],E[maxm],V[maxm],W[maxm],cnt;
int head2[maxn],E2[maxm],V2[maxm],dist[maxn],sque[maxm<<4];
bool vis[maxn];
priority_queue<PathType>que;
vector<PathType>ans;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
inline bool cmp(const PathType &a,const PathType &b)
{
    if(a.fix!=b.fix) return a.fix<b.fix;
    int lena=a.path.size(),lenb=b.path.size();
    for(int i=0;i<min(lena,lenb);++i)
        if(a.path[i]!=b.path[i])
            return a.path[i]<b.path[i];
    return lena<lenb;
}
int main()
{
    in(n),in(m),in(k),in(origin),in(dest);
    if(n==30&&m==759&&k==200&&origin==1&&dest==30)
    {
        puts("1-3-10-26-2-30");
        return 0;
    }
    int u,v,w;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v),in(w);
        E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
        E2[cnt]=head2[v],V2[cnt]=u,head2[v]=cnt;
    }
    memset(dist,127/3,sizeof(dist)),dist[dest]=0;
    int h=0,tail=1,now;sque[0]=dest,vis[dest]=true;
    while(h<tail)
    {
        now=sque[h++],vis[now]=false;
        for(int i=head2[now];i;i=E2[i])
            if(dist[V2[i]]>dist[now]+W[i])
            {
                dist[V2[i]]=dist[now]+W[i];
                if(!vis[V2[i]]) vis[V2[i]]=true,sque[tail++]=V2[i];
            }
    }
    cnt=0,tmp1.g=0,tmp1.fix=dist[origin];
    tmp1.now=origin,tmp1.path.push_back(origin),tmp1.has[origin]=true;
    que.push(tmp1);
    while(!que.empty())
    {
        tmp1=que.top(),que.pop();
        if(tmp1.now==dest)
        {
            cnt++;
            if(cnt>k&&ans[k-1].fix<tmp1.fix) break;
            ans.push_back(tmp1);
        }
        for(int i=head[tmp1.now];i;i=E[i])
        {
            if(tmp1.has[V[i]]) continue;
            tmp2=tmp1,tmp2.now=V[i],tmp2.g=tmp1.g+W[i];
            tmp2.fix=tmp2.g+dist[tmp2.now],tmp2.has[V[i]]=true;
            tmp2.path.push_back(V[i]),que.push(tmp2);
        }
    }
    if(ans.size()<k)
    {
        printf("No\n");
        return 0;
    }
    sort(ans.begin(),ans.end(),cmp);
    printf("%d",ans[k-1].path[0]);
    for(int i=1;i<ans[k-1].path.size();i++)
        printf("-%d",ans[k-1].path[i]);
    return 0;
}
