#include <bits/stdc++.h>
using namespace std;
int n;
char a[55];
bool fix[5];
void out()
{
    for(int i=0;i<n;i++) putchar(a[i]);
    puts("4");
}
int main()
{
    scanf("%s",a),n=strlen(a)-1;
    if(a[n]=='4')
    {
        for(int i=1;i<=3;i++)
        {
            for(int v=0;v<n;v++) putchar(a[v]);
            printf("%d\n",i);
        }
        return 0;
    }
    switch(a[n])
    {
        case '1':fix[1]=fix[3]=true;break;
        case '2':fix[1]=fix[2]=true;break;
        case '3':fix[2]=fix[3]=true;break;
    }
    out();
    while((--n)!=1)
        switch(a[n])
        {
            case'1':
                if(fix[2]) out(),fix[2]=0;
                break;
            case'2':
                if(fix[3]) out(),fix[3]=0;
                break;
            case'3':
                if(fix[1]) out(),fix[1]=0;
                break;
        }
    return 0;
}
