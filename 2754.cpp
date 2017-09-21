#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 80005
#define maxm 200005
#define maxlen 400005
 
struct TreeNodeType {
    int tag,id;
     
    TreeNodeType *fail;
     
    map<int,TreeNodeType*>next;
 
    TreeNodeType()
    {
        tag=0,id=0,fail=NULL,next.clear();
    }
};
struct TreeNodeType *que[maxlen],*root;
 
int n,m,tot,ans2[maxn],ans1[maxn];
 
map<int,bool>vis;
 
vector<int>name[maxn],times[maxm];
 
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
 
int main()
{
    root=new TreeNodeType,root->id=++tot;
    in(n),in(m);int len,pos;
    for(int i=1;i<=n;i++)
    {
        in(len);
        for(int j=1;j<=len;j++) in(pos),name[i].push_back(pos);
        name[i].push_back(-1),in(len);
        for(int j=1;j<=len;j++) in(pos),name[i].push_back(pos);
        name[i].push_back(-2);
    }
    for(int i=1;i<=m;i++)
    {
        in(len);TreeNodeType *now=root;
        for(int j=1;j<=len;j++)
        {
            in(pos);
            if(now->next[pos]==NULL)
            {
                now->next[pos]=new TreeNodeType;
                now->next[pos]->id=++tot;
            }
            now=now->next[pos];
        }
        now->tag++,times[now->id].push_back(i);
    }
    int h=0,tail=1;que[h]=root;
    while(h<tail)
    {
        TreeNodeType *now=que[h++],*temp=NULL;
        for(map<int,TreeNodeType*>::iterator it=now->next.begin();it!=now->next.end();it++)
        {
            if(now==root) it->second->fail=root;
            else
            {
                temp=now->fail;
                while(temp!=NULL)
                {
                    if(temp->next[it->first])
                    {
                        it->second->fail=temp->next[it->first];
                        break;
                    }
                    temp=temp->fail;
                }
                if(temp==NULL) it->second->fail=root;
            }
            que[tail++]=it->second;
        }
    }
    for(int i=1;i<=n;i++)
    {
        len=name[i].size(),vis.clear();
        TreeNodeType *now=root,*temp;
        for(int j=0;j<len;j++)
        {
            if(!vis[now->id])
            {
                vis[now->id]=true;
                if(now->tag)
                {
                    ans2[i]+=now->tag;
                    for(int v=0;v<times[now->id].size();v++) ans1[times[now->id][v]]++;
                }
                TreeNodeType *temp=now->fail;
                while(temp!=NULL)
                {
                    if(!vis[temp->id])
                    {
                        vis[temp->id]=true;
                        if(temp->tag)
                        {
                            ans2[i]+=temp->tag;
                            for(int v=0;v<times[temp->id].size();v++) ans1[times[temp->id][v]]++;
                        }
                    }
                    temp=temp->fail;
                }
            }
            if(now->next[name[i][j]]) now=now->next[name[i][j]];
            else
            {
                temp=now->fail;
                while(temp!=NULL)
                {
                    if(!vis[temp->id])
                    {
                        vis[temp->id]=true;
                        if(temp->tag)
                        {
                            ans2[i]+=temp->tag;
                            for(int v=0;v<times[temp->id].size();v++) ans1[times[temp->id][v]]++;
                        }
                    }
                    if(temp->next[name[i][j]])
                    {
                        now=temp->next[name[i][j]];
                        TreeNodeType *pos=temp->fail;
                        while(pos!=NULL)
                        {
                            if(!vis[pos->id])
                            {
                                vis[pos->id]=true;
                                if(pos->tag)
                                {
                                    ans2[i]+=pos->tag;
                                    for(int v=0;v<times[pos->id].size();v++) ans1[times[pos->id][v]]++;
                                }
                            }
                            pos=pos->fail;
                        }
                        break;
                    }
                    temp=temp->fail;
                }
                if(temp==NULL) now=root;
            }
        }
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans1[i]);
    for(int i=1;i<=n;i++)
    {
        if(i==1) printf("%d",ans2[i]);
        else printf(" %d",ans2[i]);
    }
    return 0;
}
