#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int mn=1e6+13,mnt=mn<<2|1;
const int INF=(1<<30)-1;
int n,m,L[mnt],R[mnt],md[mnt],st[mnt];
int vi[mnt],tag[mnt],o;
inline int in(){
	char c;
	int x=0,z=1;
	while(!isdigit(c=getchar()))
		if(c=='-')
			z=-1;
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*z;
}
void B(int x,int l,int r){
	L[x]=l;
	R[x]=r;
	st[x]=1;
	if(l==r)
		return;
	md[x]=l+r>>1;
	B(x<<1,l,md[x]);
	B(x<<1|1,md[x]+1,r);
}
inline void P(const int &x){
	st[x<<1]=st[x<<1|1]=tag[x<<1]=tag[x<<1|1]=tag[x];
	vi[x<<1]=vi[x<<1|1]=(tag[x]==1?0:INF);
	tag[x]=0;
}
inline void U(const int &x,const int &p,const int &y){
	if(L[x]==R[x]){
		vi[x]=y;
		if(!y)
			st[x]=1;
		else if(y==INF)
			st[x]=2;
		else
			st[x]=0;
		return;
	}
	if(tag[x])
		P(x);
	if(p<=md[x])
		U(x<<1,p,y);
	else
		U(x<<1|1,p,y);
	if(st[x<<1]==st[x<<1|1])
		st[x]=st[x<<1];
	else
		st[x]=0;
}
inline void U(const int &x,const int &l,const int &r,const int &y){
	if(L[x]>=l&&R[x]<=r){
		if(y==1){
			st[x]=tag[x]=1;
			vi[x]=0;
		}
		else{
			st[x]=tag[x]=2;
			vi[x]=INF;
		}
		return;
	}
	if(tag[x])
		P(x);
	if(l<=md[x])
		U(x<<1,l,r,y);
	if(r>md[x])
		U(x<<1|1,l,r,y);
	if(st[x<<1]==st[x<<1|1])
		st[x]=st[x<<1];
	else
		st[x]=0;
}
inline int get(int x,const int &s){
	while(L[x]!=R[x]){
		if(tag[x])
			P(x);
		if(st[x<<1]==s)
			x=x<<1|1;
		else
			x=x<<1;
	}
	o=vi[x];
	return L[x];
}
inline int Q(int x,const int &p){
	while(L[x]!=R[x]){
		if(tag[x])
			P(x);
		if(p<=md[x])
			x<<=1;
		else
			x=x<<1|1;
	}
	return vi[x];
}
inline int find(const int &y,const int &s){
	int x=1;
	while(L[x]!=R[x]){
		if(tag[x])
			P(x);
		if(y<=md[x])
			x=x<<1;
		else
			x=x<<1|1;
	}
	int last=x;
	x>>=1;
	while(true){
		if((x<<1|1)!=last&&st[x<<1|1]!=s)
			return get(x<<1|1,s);
		last=x;
		x>>=1;
	}
}
inline void add(int x){
	int k=x/30,b=x%30,t=Q(1,k);
	for(register short i=b;i<30;i++){
		if(!(1<<i&t)){
			t|=1<<i;
			U(1,k,t);
			return;
		}
		t-=1<<i;
	}
	U(1,k,t);
	b=find(k,2);
	if(b-1>k)
		U(1,k+1,b-1,1);
	for(register short i=0;i<=29;i++){
		if(!(1<<i&o)){
			o|=1<<i;
			U(1,b,o);
			return;
		}
		o-=1<<i;
	}
}
inline void mis(int x){
	int k=x/30,b=x%30,t=Q(1,k);
	for(short i=b;i<30;i++){
		if(1<<i&t){
			t-=1<<i;
			U(1,k,t);
			return;
		}
		t|=1<<i;
	}
	U(1,k,t);
	b=find(k,1);
	if(b-1>k)
		U(1,k+1,b-1,2);
	for(short i=0;i<=29;i++){
		if(1<<i&o){
			o-=1<<i;
			U(1,b,o);
			return;
		}
		o|=1<<i;
	}
}
void A(int a,int b){
	for(short i=0;i<=30;i++)
		if(1<<i&a)
			add(i+b);
}
void M(int a,int b){
	for(short i=0;i<=30;i++)
		if(1<<i&a)
			mis(i+b);
}
int main(){
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	n=in()+5;
	in(),in(),in();
	B(1,0,n);
	for(int i=1,op,k,a,b;i<=n-5;i++){
		op=in();
		if(op==1){
			a=in();
			b=in();
			if(a<0)
				M(-a,b);
			else if(a>0)
				A(a,b);
		}
		else{
			k=in();
			b=k/30;
			k=k%30;
			if(Q(1,b)&(1<<k))
				puts("1");
			else
				puts("0");
		}
	}
	return 0;
}
