#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e6+5;
const int INF=0x3f3f3f3f;

int n,r[maxn][2],ch[maxn][2],tot,Min[maxn][2],Max[maxn][2];
int root,ans,m,X,Y;

const int BUF=22341235;

char buf[BUF],*Cget=buf;

inline void read(int &now)
{
	now=0;int if_z=1;
	while(*Cget>'9'||*Cget<'0') if(*(Cget++)=='-') if_z=-1;
	while(*Cget>='0'&&*Cget<='9')now=now*10+(*(Cget++))-'0';
	now*=if_z;
}

inline void insert()
{
	if(!root)
	{
		root=++tot;
		r[root][0]=X;
		r[root][1]=Y;
		Min[root][0]=Max[root][0]=X;
		Min[root][1]=Max[root][1]=Y;
		return;
	}
	int val[2]={X,Y},d=0,now=root,fa=0;
	while(true)
	{
		if(val[0]==r[now][0]&&val[1]==r[now][1])
			return;
		if(val[0]<Min[now][0])
			Min[now][0]=val[0];
		if(val[0]>Max[now][0])
			Max[now][0]=val[0];
		if(val[1]<Min[now][1])
			Min[now][1]=val[1];
		if(val[1]>Max[now][1])
			Max[now][1]=val[1];
		fa=now;
		if(val[d]<=r[fa][d])
			now=ch[fa][0];
		else
			now=ch[fa][1];
		if(!now)
		{
			ch[fa][val[d]>r[fa][d]]=++tot;
			r[tot][0]=val[0];
			r[tot][1]=val[1];
			Min[tot][0]=Max[tot][0]=val[0];
			Min[tot][1]=Max[tot][1]=val[1];
			return;
		}
		d^=1;
	}
}

inline int getdis(int id)
{
	int res=0;
	if(X<Min[id][0])
		res+=Min[id][0]-X;
	if(Y<Min[id][1])
		res+=Min[id][1]-Y;
	if(X>Max[id][0])
		res+=X-Max[id][0];
	if(Y>Max[id][1])
		res+=Y-Max[id][1];
	return res;
}

void ask(int now)
{
	int d0=std::abs(r[now][0]-X)+abs(r[now][1]-Y);
	if(d0<ans)
		ans=d0;
	int dl=INF,dr=INF;
	if(ch[now][0])
		dl=getdis(ch[now][0]);
	if(ch[now][1])
		dr=getdis(ch[now][1]);
	if(dl<dr)
	{
		if(dl<ans)
			ask(ch[now][0]);
		if(dr<ans)
			ask(ch[now][1]);
	}
	else
	{
		if(dr<ans)
			ask(ch[now][1]);
		if(dl<ans)
			ask(ch[now][0]);
	}
}

int main()
{
//	freopen("data.txt","r",stdin);
//	freopen("ans1.txt","w",stdout);
	fread(Cget,1,BUF,stdin);
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
	{
		read(X);
		read(Y);
		insert();
	}
	for(int i=1,op;i<=m;i++)
	{
		read(op);
		read(X);
		read(Y);
		if(op==1)
			insert();
		else
		{
			ans=INF;
			ask(root);
			printf("%d\n",ans);
		}
	}
	return 0;
}
