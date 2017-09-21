#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 2000005
 
int ch[maxn][2],key[maxn],f[maxn],root,size[maxn];
int n,m,tot;
 
long long ha[maxn],mi[maxn];
 
char ai[maxn];
 
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
 
inline bool getson(int now)
{
    return ch[f[now]][1]==now;
}
 
inline void updata(int now)
{
    size[now]=1,ha[now]=0;
    if(ch[now][0]) size[now]+=size[ch[now][0]],ha[now]+=ha[ch[now][0]];
    ha[now]+=key[now]*mi[size[now]-1];
    if(ch[now][1]) ha[now]+=ha[ch[now][1]]*mi[size[now]],size[now]+=size[ch[now][1]];
}
 
inline void rotate(int now,int &to)
{
    int fa=f[now],ffa=f[fa];bool pos=getson(now);
    ch[fa][pos]=ch[now][pos^1];
    if(ch[fa][pos]) f[ch[fa][pos]]=fa;
    if(to==fa) to=now;
    else ch[ffa][getson(fa)]=now;
    ch[now][pos^1]=fa,f[fa]=now,f[now]=ffa;
    updata(fa),updata(now);
}
 
void splay(int now,int &to)
{
    while(now!=to)  
    {  
        int fa=f[now],ffa=f[fa];  
        if(fa!=to)
        {  
            if(ch[fa][0]==now^ch[ffa][0]==fa) rotate(now,to);
            else rotate(now,to);  
        }rotate(now,to);  
    }
}
 
void find(int p,bool pos)
{
    int now=root;
    while(1)
    {
        if(size[ch[now][0]]>=p) now=ch[now][0];
        else
        {
            p-=size[ch[now][0]];
            if(p==1)
            {
                if(pos) splay(now,root);
                else splay(now,ch[root][1]);
                return ;
            }
            else p--,now=ch[now][1];
        }
    }
}
 
void insert(int p,int ci)
{
    find(p,true),find(p+1,false);
    ch[ch[root][1]][0]=++tot;
    key[tot]=ci,size[tot]=1,f[tot]=ch[root][1],ha[tot]=ci;
    updata(ch[root][1]),updata(root);
}
 
int tree_build(int l,int r,int fa)
{
    int now=l+r>>1;key[now]=ai[now],f[now]=fa;
    if(now>l) ch[now][0]=tree_build(l,now-1,now);
    if(now<r) ch[now][1]=tree_build(now+1,r,now);
    updata(now);return now;
}
 
long long hash_ci(int p,int len)
{
    find(p,true),find(p+len+1,false);
    return ha[ch[ch[root][1]][0]];
}
 
int main()
{
    mi[0]=1;
    for(int i=1;i<=100003;i++) mi[i]=mi[i-1]*27LL;
    scanf("%s",ai+2),tot=strlen(ai+2)+2;
    for(int i=2;i<=tot-1;i++) ai[i]=ai[i]-'a'+1;
    root=tree_build(1,tot,0);
    in(m);char op[5];int u,v;
    for(;m--;)
    {
        scanf("%s",op);
        if(op[0]=='Q')
        {
            in(u),in(v);
            if(u>v) swap(u,v);
            int l=1,r=tot-v-1,ans=0;
            while(l<=r)
            {
                int mid=l+r>>1;
                if(hash_ci(u,mid)==hash_ci(v,mid)) ans=mid,l=mid+1;
                else r=mid-1;
            }
            printf("%d\n",ans);
        }
        else if(op[0]=='R')
        {
            in(u),scanf("%s",op);
            find(u+1,true),key[root]=op[0]-'a'+1,updata(root);
        }
        else
        {
            in(u),scanf("%s",op);
            insert(u+1,(int)(op[0]-'a'+1));
        }
    }
    return 0;
}
