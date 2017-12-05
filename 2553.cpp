#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long double lreal;

const int maxn=416;

struct MatrixType
{
	int n,m;
	
	lreal data[maxn][maxn];
	
	MatrixType operator*(const MatrixType &tmp)const
	{
		MatrixType res;
		res.n=n;
		res.m=tmp.m;
		for(register short i=1,v,e;i<=res.n;++i)
			for(v=1;v<=res.m;++v)
			{
				res.data[i][v]=0;
				for(e=1;e<=m;++e)
					res.data[i][v]+=data[i][e]*tmp.data[e][v];
			}
		return res;
	}
	
	void debug()
	{
		printf("\n%d %d\n",n,m);
		for(int i=1;i<=n;i++,printf("\n"))
			for(int v=1;v<=m;v++)
				printf("%.2lf ",(double)data[i][v]);
	}
};

struct MatrixType Base,C;

int ch[maxn][26],tot=1,root=1,len,n,m,val[maxn];
int que[maxn*maxn],fail[maxn],get[maxn][26];

bool vis[maxn];

char str[maxn];

lreal alp;

inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

MatrixType powww(MatrixType base,MatrixType c,int e)
{
	while(e)
	{
		if(e&1)
			base=base*c;
		c=c*c;
//		c.debug();
		e>>=1;
	}
	return base;
}

int main()
{
	freopen("data.txt","r",stdin);
	scanf("%d%d%d",&n,&len,&m);
	alp=1.0/(lreal)m;
	for(int i=1,tmp;i<=n;i++)
	{
		scanf("%s",str+1);
		tmp=strlen(str+1);
		int now=root;
		for(int v=1;v<=tmp;v++)
		{
			if(!ch[now][str[v]-'a'])
				ch[now][str[v]-'a']=++tot;
			now=ch[now][str[v]-'a'];
		}
		val[now]++;
	}
	int h=0,tail=1,now;
	que[0]=root;
	for(int i=0;i<m;i++)
		ch[0][i]=1;
	while(h<tail)
	{
		int now=que[h++];
		for(int i=0;i<m;i++)
			if(ch[now][i])
			{
				int to=fail[now];
				while(!ch[to][i])
					to=fail[to];
				to=ch[to][i];
				fail[ch[now][i]]=to;
				que[tail++]=ch[now][i];
			}
	}
	for(int i=1;i<=tot;i++)
		for(int v=0;v<m;v++)
		{
			int now=i;
			while(!ch[now][v])
				now=fail[now];
			get[i][v]=ch[now][v];
		}
	h=0;
	tail=1;
	que[0]=root;
	vis[root]=true;
	while(h<tail)
	{
		int i=que[h++];
		for(int v=0;v<m;v++)
		{
			if(!vis[get[i][v]])
			{
				vis[get[i][v]]=true;
				que[tail++]=get[i][v];
			}
			if(val[get[i][v]])
			{
				C.data[i][1]+=alp;
				C.data[i][tot+1]+=alp;
			}
			else
				C.data[i][get[i][v]]+=alp;
		}
	}
	C.data[tot+1][tot+1]=alp;
	C.n=tot+1;
	C.m=tot+1;
	Base.n=1;
	Base.m=tot+1;
	Base.data[1][1]=1;
	for(int i=1;i<=tot+1;i++)
		Base.data[i][i]=1;
	C.data[tot+1][tot+1]=1;
//	C.debug();
//	Base.debug();
	printf("%.7lf\n",(double)powww(Base,C,len).data[1][tot+1]);
//	for(int i=1;i<=len;i++)
//	{
//		Base=Base*C;
//		Base.debug();
//	}
	return 0;
}
