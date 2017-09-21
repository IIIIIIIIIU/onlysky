#include <bits/stdc++.h>
using namespace std;
#define maxn 500005
#define INF 0x3f3f3f3f
const double pi=acos(-1);
struct Complex
{
    double r,i;
    Complex(double r,double i=0):r(r),i(i){}
    Complex(){}
};
Complex operator+(Complex a,Complex b)
{
    return Complex(a.r+b.r,a.i+b.i);
}
Complex operator-(Complex a,Complex b)
{
    return Complex(a.r-b.r,a.i-b.i);
}
Complex operator*(Complex a,Complex b)
{
    return Complex(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);
}
int n,m,data1[maxn],data2[maxn],rev[maxn],ans=INF;
Complex ai[maxn],bi[maxn],ai2[maxn],bi2[maxn];
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void fft(Complex *res,int l,int p)
{
    for(int i=0;i<l;i++) if(i<rev[i]) swap(res[i],res[rev[i]]);
    for(int i=1;i<l;i<<=1)
    {
        Complex wd=Complex(cos(pi/i),sin(pi/i)*p);
        for(int v=0;v<l;v+=(i<<1))
        {
            Complex w=Complex(1,0);
            for(int k=0;k<i;k++)
            {
                Complex tmp=res[v+k],tmp_=w*res[v+k+i];
                res[v+k]=tmp+tmp_,res[v+k+i]=tmp-tmp_;
                w=w*wd;
            }
        }
    }
    if(p==-1) for(int i=0;i<l;i++) res[i].r/=l,res[i].i/=l;
}
int main()
{
    in(n),in(m);
    int mxn,lg=0,s=0;
    for(mxn=1;mxn<=n*2;mxn*=2,lg++);
    for(int i=0;i<mxn;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
    for(int i=1;i<=n;i++) in(data1[i]),ai[i]=data1[i],ai2[n-i+1]=data1[i];
    for(int i=1;i<=n;i++) in(data2[i]),bi[n-i+1]=data2[i],bi2[i]=data2[i],s+=data2[i];
    fft(bi,mxn,1),fft(bi2,mxn,1),fft(ai,mxn,1),fft(ai2,mxn,1);
    for(int i=0;i<mxn;i++) ai[i]=ai[i]*bi[i],ai2[i]=ai2[i]*bi2[i];
    fft(ai,mxn,-1),fft(ai2,mxn,-1);
    for(int l=-m+1;l<m;l++)
    {
        int w=0;
        for(int i=1;i<=n;i++) w+=(data1[i]+l)*(data1[i]+l)+data2[i]*data2[i];
        for(int i=1;i<=n;i++)
        {
            int v=(int)(ai[i].r+0.1)+(int)(ai2[n-i+2].r+0.1)+s*l;
            ans=min(ans,w-2*v);
        }
    }
    printf("%d\n",ans);
    return 0;
}
