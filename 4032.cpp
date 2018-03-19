#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e3+5+1e2;

int nA,nB,f[maxn][maxn<<1|1],pre[maxn][26];

char A[maxn],B[maxn];

inline void calc(int &a,int b)
{
	if(b<a)
		a=b;
}

namespace SAM
{
	int ch[maxn<<1|1][26],last=1,tot=1,len[maxn<<1|1],f[maxn<<1|1];
	
	void extend(int c)
	{
		int p,np,q,nq;
		len[np=++tot]=len[last]+1;
		for(p=last;p&&!ch[p][c];ch[p][c]=np,p=f[p]);
		if(!p)
			f[np]=1;
		else
		{
			q=ch[p][c];
			if(len[q]==len[p]+1)
				f[np]=q;
			else
			{
				nq=++tot;
				memcpy(ch[nq],ch[q],sizeof(ch[nq]));
				f[nq]=f[q];
				f[q]=f[np]=nq;
				len[nq]=len[p]+1;
				for(;ch[p][c]==q;ch[p][c]=nq,p=f[p]);
			}
		}
		last=np;
	}
}

namespace SeAM
{
	int ch[maxn][26];
	
	void build(char *p,int len)
	{
		for(int i=0;i<26;i++)
		{
			int P=len+1;
			for(int v=len;v>=0;v--)
			{
				ch[v][i]=P;
				if(p[v]=='a'+i)
					P=v;
			}
		}
	}
}

int main()
{
	freopen("sus.in","r",stdin);
	freopen("sus.out","w",stdout);
	std::cin>>A+1>>B+1;
	nA=strlen(A+1);
	nB=strlen(B+1);
	for(int i=1;i<=nB;i++)
		SAM::extend(B[i]-'a');
	SeAM::build(B,nB);
	int Ans=nA;
	for(int i=1;i<=nA;i++)
	{
		int now=1;
		for(int v=i,lit=std::min(nA,i+Ans-1);v<=lit;v++)
		{
			now=SAM::ch[now][A[v]-'a'];
			if(!now)
			{
				Ans=v-i+1;
				break;
			}
		}
	}
	std::cout<<Ans<<std::endl;
	Ans=nA;
	for(int i=1;i<=nA;i++)
	{
		int now=0;
		for(int v=i,lit=std::min(nA,i+Ans-1);v<=lit;v++)
		{
			now=SeAM::ch[now][A[v]-'a'];
			if(now==nB+1)
			{
				Ans=v-i+1;
				break;
			}
		}
	}
	std::cout<<Ans<<std::endl;
	for(int i=0;i<26;i++)
	{
		int P=nA+1;
		for(int v=nA;v>=0;v--)
		{
			pre[v][i]=P;
			if(A[v]=='a'+i)
				P=v;
		}
	}
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=nA;i++)
		f[i][1]=0;
	Ans=nA;
	for(int i=0;i<=nA;i++)
	{
		for(int v=1;v<=SAM::tot;v++)
			if(f[i][v]<maxn)
			{
				for(int e=0;e<26;e++)
					if(pre[i][e]!=nA+1)
					{
						if(SAM::ch[v][e])
							calc(f[pre[i][e]][SAM::ch[v][e]],f[i][v]+1);
						else
							calc(Ans,f[i][v]+1);
					}
			}
	}
	std::cout<<Ans<<std::endl;
	Ans=nA;
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<=nA;i++)
		for(int v=0;v<=nB;v++)
			if(f[i][v]<maxn)
			{
				for(int e=0;e<26;e++)
					if(pre[i][e]!=nA+1)
					{
						if(SeAM::ch[v][e]!=nB+1)
							calc(f[pre[i][e]][SeAM::ch[v][e]],f[i][v]+1);
						else
							calc(Ans,f[i][v]+1);
					}
			}
	std::cout<<Ans<<std::endl;
	return 0;
}
