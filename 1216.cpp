#include <bits/stdc++.h>
using namespace std;
struct node
{
    int id,s,c,val;
    bool operator<(const node &pos)const
    {
        if(val==pos.val) return s>pos.s;
        return val<pos.val;
    }
    node(int id_=0,int s_=0,int c_=0,int val_=0)
    {
        id=id_,s=s_,c=c_,val=val_;
    }
};
priority_queue<node>que;
int main()
{
    int id,s,c,val,now=0,pos,pos2;node tmp,tmp2;
    while(scanf("%d%d%d%d",&id,&s,&c,&val)!=EOF)
    {
        pos=s-now,pos2=0;
        while(que.size())
        {
            tmp=que.top();
            if(tmp.c>pos)
            {
                tmp2=tmp;
                tmp2.c-=pos;
                que.pop();
                que.push(tmp2);
                break;
            }
            else
            {
                pos-=tmp.c,pos2+=tmp.c;
                printf("%d %d\n",tmp.id,now+pos2);
                que.pop();
            }
        }
        que.push(node(id,s,c,val));
        now=s;
    }
    pos=0;
    while(que.size())
    {
        tmp=que.top(),que.pop(),pos+=tmp.c;
        printf("%d %d\n",tmp.id,now+pos);
    }
    return 0;
}
