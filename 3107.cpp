#include<cstdio>  
#include<iostream>  
int calc(int x){  
    int t=0;
    for(;x;x>>=1)
	    t++;
    return t;   
}  
int getit(int x){  
    int t=0;
    for(;x;x^=x&-x)
	    t++;
    return t;  
}  
using std::max;
using std::swap;
int main(){  
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);  
    int len=max(max(calc(a),calc(b)),calc(c)),ans;  
    a=getit(a);
    b=getit(b);
    c=getit(c);   
    if(a>b)
	    swap(a,b);  
    if(c<=a)
	    ans=(1<<(a+b-c))|((1<<c)-2);  
    else if(c<=b)
	    ans=((1<<b)|((1<<c)-1))^(1<<(c-a));  
    else if(c<=a+b)
	    ans=((1<<(c+1))-1)^(1<<(c+c-a-b));  
    else
    {  
        puts("-1");
	return 0;  
    }  
    printf("%d\n",(calc(ans)<=len)?ans:-1);  
    return 0;  
}  
