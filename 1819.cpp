#include <bits/stdc++.h>
using namespace std;
int ch[300505][26],root[30],tot,n,m,len,ans,can,tag[300505],flag;
char str[105];
bool find(int now)
{
    for(int i=1;i<=len;i++)
        if(!ch[now][str[i]-'a']) return false;
        else now=ch[now][str[i]-'a'];
    return true;
}
void dfs1(int now,int deep,bool did)
{
    if((deep==len)||(deep==len-1&&!did))
    {
        if(tag[now]!=flag) ans++,tag[now]=flag;
        return;
    }
    if(!did)
        if(deep+2<=len&&ch[now][str[deep+2]-'a']) dfs1(ch[now][str[deep+2]-'a'],deep+2,true);
    if(ch[now][str[deep+1]-'a']) dfs1(ch[now][str[deep+1]-'a'],deep+1,did);
}
void dfs2(int now,int deep,bool did)
{
    if(deep==len&&did)
    {
        if(tag[now]!=flag&&did) tag[now]=flag,ans++;
        return;
    }
    if(!did)
        for(int i=0;i<26;i++) if(ch[now][i]) dfs2(ch[now][i],deep,true);
    if(ch[now][str[deep+1]-'a']&&deep<len) dfs2(ch[now][str[deep+1]-'a'],deep+1,did);
}
void dfs3(int now,int deep,bool did)
{
    if(deep==len)
    {
        if(tag[now]!=flag) tag[now]=flag,ans++;
        return;
    }
    if(!did)
        for(int i=0;i<26;i++)
            if(ch[now][i]&&i!=str[deep+1]-'a') dfs3(ch[now][i],deep+1,true);
    if(ch[now][str[deep+1]-'a']) dfs3(ch[now][str[deep+1]-'a'],deep+1,did);
}
int main()
{
    scanf("%d%d",&n,&m);
    int now;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1),len=strlen(str+1);
        if(!root[len]) root[len]=++tot;
        now=root[len];
        int to;
        for(int v=1;v<=len;v++)
        {
            to=str[v]-'a';
            if(!ch[now][to]) ch[now][to]=++tot;
            now=ch[now][to];
        }
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%s",str+1),len=strlen(str+1);
        if(root[len]&&find(root[len]))
        {
            printf("-1\n");
            continue;
        }
        ans=0,can=0,flag=i;
        if(len>1&&root[len-1]) dfs1(root[len-1],0,false);
        if(root[len+1]) dfs2(root[len+1],0,false);
        if(root[len]) dfs3(root[len],0,false);
        printf("%d\n",ans);
    }
    return 0;
}
