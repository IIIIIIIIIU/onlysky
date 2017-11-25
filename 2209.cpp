#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e5+5;

class SplayTreeType
{
	private:
		struct SplayTreeNodeType
		{
			int l,r,tagR,size,Base;
			
			int l_,r_;
			
			int l2,r2,l2_,r2_;
			
			bool tagI,tagS;
			
			SplayTreeNodeType *ch[2],*f;
			
			SplayTreeNodeType()
			{
				l=0;
				r=0;
				l_=0;
				r_=0;
				l2=0;
				r2=0;
				l2_=0;
				r2_=0;
				size=1;
				tagR=0;
				f=NULL;
				Base=0;
				tagI=false;
				tagS=false;
				ch[0]=NULL;
				ch[1]=NULL;
			}
			
			void updata()
			{
				size=1;
				l=0;
				r=0;
				l_=0;
				r_=0;
				l2=0;
				r2=0;
				l2_=0;
				r2_=0;
				if(Base==1)
				{
					l=1;
					r_=1;
					l2=1;
					r2_=1;
				}
				else
				{
					r=1;
					l_=1;
					r2=1;
					l2_=1;
				}
				if(ch[0]!=NULL)
				{
					size+=ch[0]->size;
					if(ch[0]->r<=l)
						l+=ch[0]->l-ch[0]->r;
					else
					{
						r+=ch[0]->r-l;
						l=ch[0]->l;
					}
					if(ch[0]->r_<=l_)
						l_+=ch[0]->l_-ch[0]->r_;
					else
					{
						r_+=ch[0]->r_-l_;
						l_=ch[0]->l_;
					}
					if(ch[0]->l2>=r2)
					{
						l2+=ch[0]->l2-r2;
						r2=ch[0]->r2;
					}
					else
						r2+=ch[0]->r2-ch[0]->l2;
					if(ch[0]->l2_>=r2_)
					{
						l2_+=ch[0]->l2_-r2_;
						r2_=ch[0]->r2_;
					}
					else
						r2_+=ch[0]->r2_-ch[0]->l2_;
				}
				if(ch[1]!=NULL)
				{
					size+=ch[1]->size;
					if(ch[1]->l>=r)
					{
						l+=ch[1]->l-r;
						r=ch[1]->r;
					}
					else
						r+=ch[1]->r-ch[1]->l;
					if(ch[1]->l_>=r_)
					{
						l_+=ch[1]->l_-r_;
						r_=ch[1]->r_;
					}
					else
						r_+=ch[1]->r_-ch[1]->l_;
					if(ch[1]->r2<=l2)
						l2+=ch[1]->l2-ch[1]->r2;
					else
					{
						r2+=ch[1]->r2-l2;
						l2=ch[1]->l2;
					}
					if(ch[1]->r2_<=l2_)
						l2_+=ch[1]->l2_-ch[1]->r2_;
					else
					{
						r2_+=ch[1]->r2_-l2_;
						l2_=ch[1]->l2_;
					}
				}
			}
			
			void hitR(int x)
			{
				tagR=x;
				Base=x;
				if(x==1)
				{
					l=size;
					r=0;
					r_=size;
					l_=0;
					l2=size;
					r2=0;
					r2_=size;
					l2_=0;
				}
				else
				{
					r=size;
					l=0;
					l_=size;
					r_=0;
					r2=size;
					l2=0;
					l2_=size;
					r2_=0;
				}
				tagS=0;
				tagI=0;
			}
			
			void hitI()
			{
				std::swap(l_,l);
				std::swap(r_,r);
				std::swap(l2_,l2);
				std::swap(r2_,r2);
				if(Base==1)
					Base=2;
				else
					Base=1;
				tagI^=1;
			}
			
			void hitS()
			{
				std::swap(l,l2);
				std::swap(r,r2);
				std::swap(l_,l2_);
				std::swap(r_,r2_);
				std::swap(ch[0],ch[1]);
				tagS^=1;
			}
			
			void pushdown()
			{
				if(tagR)
				{
					if(ch[0]!=NULL)
						ch[0]->hitR(tagR);
					if(ch[1]!=NULL)
						ch[1]->hitR(tagR);
					tagR=0;
				}
				if(tagS)
				{
					if(ch[0]!=NULL)
						ch[0]->hitS();
					if(ch[1]!=NULL)
						ch[1]->hitS();
					tagS=false;
				}
				if(tagI)
				{
					if(ch[0]!=NULL)
						ch[0]->hitI();
					if(ch[1]!=NULL)
						ch[1]->hitI();
					tagI=false;
				}
			}
			
			void rotate()
			{
				SplayTreeNodeType *fa=f,*ffa=fa->f;
				int l=(fa->ch[1]==this),r=(l^1);
				if(ffa!=NULL)
					ffa->ch[ffa->ch[1]==fa]=this;
				f=ffa;
				fa->ch[l]=ch[r];
				ch[r]=fa;
				fa->f=this;
				if(fa->ch[l]!=NULL)
					fa->ch[l]->f=fa;
				fa->updata();
				updata();
			}
		};
		
	public:
		SplayTreeNodeType *root;
		
		SplayTreeType()
		{
			root=NULL;
		}
		
		void build(SplayTreeNodeType *&now,int l,int r,char *arr)
		{
			int mid=l+r>>1;
			now=new SplayTreeNodeType;
			if(arr[mid]==')')
			{
				now->Base=1;
				now->l=1;
				now->r_=1;
				now->l2=1;
				now->r2_=1;
			}
			else
			{
				now->Base=2;
				now->r=1;
				now->l_=1;
				now->r2=1;
				now->l2_=1;
			}
			if(l<mid)
			{
				build(now->ch[0],l,mid-1,arr);
				now->ch[0]->f=now;
			}
			if(r>mid)
			{
				build(now->ch[1],mid+1,r,arr);
				now->ch[1]->f=now;
			}
			now->updata();
		}
		
		void splay(SplayTreeNodeType *now,bool type)
		{
			SplayTreeNodeType *fa,*ffa,*to;
			if(type)
				to=NULL;
			else
				to=root;
			while(now->f!=to)
			{
				fa=now->f;
				ffa=fa->f;
				if(ffa!=to)
				{
					if(fa->ch[1]==now^ffa->ch[1]==fa)
						now->rotate();
					else
						fa->rotate();
				}
				now->rotate();
			}
			now->updata();
			if(type)
				root=now;
		}
		
		void find(int x,bool type)
		{
			SplayTreeNodeType *now=root;
			while(true)
			{
				now->pushdown();
				if(now->ch[0]!=NULL&&now->ch[0]->size>=x)
					now=now->ch[0];
				else
				{
					if(now->ch[0]!=NULL)
						x-=now->ch[0]->size;
					if(x==1)
					{
						splay(now,type);
						return;
					}
					x--;
					now=now->ch[1];
				}
			}
		}
};

class SplayTreeType splay;

int n,m;

char str[maxn];

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

int main()
{
//	freopen("data.txt","r",stdin);
//	freopen("brackets.in","r",stdin);
//	freopen("brackets.out","w",stdout);
//	freopen("ans1.txt","w",stdout);
	read(n);
	read(m);
	scanf("%s",str+2);
	splay.build(splay.root,1,n+2,str);
	int op;
	for(int i=1,x,y;i<=m;i++)
	{
		read(op);
		if(op==1)
		{
			read(x);
			read(y);
			splay.find(x,true);
			splay.find(y+2,false);
			splay.root->ch[1]->ch[0]->hitI();
			splay.root->ch[1]->updata();
			splay.root->updata();
		}
		else if(op==2)
		{
			read(x);
			read(y);
			splay.find(x,true);
			splay.find(y+2,false);
			splay.root->ch[1]->ch[0]->hitS();
			splay.root->ch[1]->updata();
			splay.root->updata();
		}
		else
		{
			read(x);
			read(y);
			splay.find(x,true);
			splay.find(y+2,false);
			printf("%d\n",(splay.root->ch[1]->ch[0]->l+1)/2+(splay.root->ch[1]->ch[0]->r+1)/2);
		}
	}
	return 0;
}
