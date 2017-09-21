#include <bits/stdc++.h>
using namespace std;
struct node
{
    int l,r;
    node(int l_=0,int r_=0)
    {
        l=l_,r=r_;
    }
    bool operator<(const node &pos)const
    {
        return l<pos.l;
    }
};
int n,m,ans,ai[100005];
set<node>f[1000005];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++) in(ai[i]);
    for(int i=1;i<=n;i++)
    {
        node tmp;
        tmp.l=i,tmp.r=i;
        while(ai[i]==ai[i+1]&&i+1<=n) tmp.r=++i;
        f[ai[tmp.l]].insert(tmp),ans++;
    }
    int op,x,y;
    node tmp,tmpl,tmpr,pos;
    while(m--)
    {
        in(op);
        if(op==2) printf("%d\n",ans);
        else
        {
            in(x),in(y);
            if(x==y) continue;
            if(!f[x].size()) continue;
            else if(!f[y].size()) swap(f[y],f[x]);
            else if(f[x].size()&&f[y].size())
            {
                if(f[x].size()>f[y].size()) swap(f[x],f[y]);
                for(set<node>::iterator it=f[x].begin(),lit,rit,now;it!=f[x].end();++it)
                {
                    tmp=*it;
                    f[y].insert(tmp);
                    now=lit=rit=f[y].find(tmp);
                    rit++;
                    if(lit==f[y].begin()&&rit==f[y].end()) continue;
                    if(lit==f[y].begin()&&rit!=f[y].end())
                    {
                        tmpr=*rit;
                        pos.l=tmp.l;
                        if(tmpr.l==tmp.r+1)
                        {
                            pos.r=tmpr.r;
                            f[y].erase(rit),f[y].erase(now);
                            f[y].insert(pos),ans--;
                        }
                    }
                    else if(lit!=f[y].begin()&&f[y].end()==rit)
                    {
                        lit--;
                        tmpl=*lit;
                        if(tmpl.r+1==tmp.l)
                        {
                            pos.l=tmpl.l,pos.r=tmp.r;
                            f[y].erase(lit),f[y].erase(now);
                            f[y].insert(pos),ans--;
                        }
                    }
                    else
                    {
                        lit--;
                        tmpl=*lit,tmpr=*rit;
                        if(tmpl.r+1==tmp.l&&tmp.r+1==tmpr.l)
                        {
                            pos.l=tmpl.l,pos.r=tmpr.r;
                            f[y].erase(lit),f[y].erase(rit),f[y].erase(now);
                            f[y].insert(pos),ans-=2;
                        }
                        else if(tmpl.r+1==tmp.l)
                        {
                            pos.l=tmpl.l,pos.r=tmp.r;
                            f[y].erase(lit),f[y].erase(now);
                            f[y].insert(pos),ans--;
                        }
                        else if(tmpr.l-1==tmp.r)
                        {
                            pos.l=tmp.l,pos.r=tmpr.r;
                            f[y].erase(rit),f[y].erase(now);
                            f[y].insert(pos),ans--;
                        }
                    }
                }
                f[x].clear();
            }
        }
    }
    return 0;
}
