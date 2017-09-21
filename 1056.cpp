#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int hpos=27;
const int maxn=500005;
#define updata(x) (size[x]=size[ch[x][0]]+size[ch[x][1]]+1)
struct NodeType
{
    int score,Time;
    char name[11];
    bool operator<(const NodeType pos)const
    {
        if(score==pos.score) return Time<pos.Time;
        return score>pos.score;
    }
};
struct NodeType key[maxn];
int ch[maxn][2],size[maxn],f[maxn],tot,root,ktmp;
char str[1005];
map<ull,int>Map;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
inline void rotate(int now)
{
    register int fa=f[now],ffa=f[fa],l=(ch[fa][1]==now),r=l^1;
    if(ffa) ch[ffa][ch[ffa][1]==fa]=now;
    ch[fa][l]=ch[now][r],ch[now][r]=fa,f[fa]=now,f[now]=ffa;
    if(ch[fa][l]) f[ch[fa][l]]=fa;updata(fa);
}
inline void splay(int now)
{
    int fa,ffa;
    while(f[now])
    {
        fa=f[now],ffa=f[fa];
        if(ffa)
        {
            if(ch[fa][1]==now^ch[ffa][1]==fa) rotate(fa);
            else rotate(now);
        }
        rotate(now);
    }
    updata(now),root=now;
}
void insert(NodeType x)
{
    if(!root)
    {
        root=++tot,size[tot]=1,key[tot]=x;
        return;
    }
    register int now=root,fa=0;
    while(1)
    {
        fa=now;
        if(x<key[now]) now=ch[now][0];
        else now=ch[now][1];
        if(!now)
        {
            now=++tot,f[tot]=fa,ch[fa][!(x<key[fa])]=tot;
            size[tot]=1,key[now]=x,splay(now);return;
        }
    }
}
void del()
{
    int now=root;
    if(!ch[now][1]&&!ch[now][0])
    {
        root=0;return;
    }
    if(ch[now][1]&&ch[now][0])
    {
        int tmp=ch[root][1];
        root=ch[now][0],f[root]=0;
        int to=root;
        while(ch[to][1]) to=ch[to][1];
        splay(to),ch[to][1]=tmp,f[tmp]=to;
        updata(now);
    }
    else if(ch[now][1]) root=ch[now][1],f[root]=0;
    else root=ch[now][0],f[root]=0;
}
inline void find(int x)
{
    register int now=root;
    while(1)
    {
        if(size[ch[now][0]]>=x) now=ch[now][0];
        else
        {
            x-=size[ch[now][0]];
            if(x==1)
            {
                splay(now);return;
            }
            x--,now=ch[now][1];
        }
    }
}
inline void work(int now)
{
    if(!now) return;
    if(ch[now][0]) work(ch[now][0]);
    if(ktmp<10)
    {
        ktmp++;
        printf(" %s",key[now].name);
        if(ktmp==10) splay(now);
    }
    if(ktmp<10) work(ch[now][1]);
}
int Main()
{
    int n;
    scanf("%d",&n);
    int pos,len,pos2;
    NodeType tmp;
    ull Hash;int cur_now=0;
    for(int e=1,i;e<=n;e++)
    {
        scanf("%s",str);
        if(e%100==0) find(rand()%cur_now+1);
        if(str[0]=='+')
        {
            cur_now++;
            len=strlen(str),tmp.Time=e,Hash=0;
            memset(tmp.name,0,sizeof(tmp.name));
            for(i=1;i<len;i++) Hash=Hash*hpos+str[i]-'A'+1,tmp.name[i-1]=str[i];
            in(tmp.score),pos2=Map[Hash];
            if(pos2) splay(pos2),del(),cur_now--;
            insert(tmp),Map[Hash]=root;
        }
        else if(str[1]>='0'&&str[1]<='9')
        {
            len=strlen(str);ktmp=1;
            pos=0;
            for(i=1;i<len;i++) pos=pos*10+str[i]-'0';
            find(pos);
            printf("%s",key[root].name);
            work(ch[root][1]),putchar('\n');
        }
        else
        {
            len=strlen(str),Hash=0;
            for(i=1;i<len;i++) Hash=Hash*hpos+str[i]-'A'+1;
            splay(Map[Hash]),printf("%d\n",size[ch[root][0]]+1);
        }
    }
    return 0;
}
int S=Main();
int main()
{
    ;
}
