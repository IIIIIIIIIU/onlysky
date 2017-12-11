#include<iostream>  
#include<cstdio>  
#include<cstring>  
int n;  
bool f[22][20][20][20][20][20];  
using namespace std;  
void out(int i,int j,int k,int l,int a,int b,int c){  
   if (i<10) cout<<i;else cout<<char(i-10+(int)'a');  
   if (j<10) cout<<j;else cout<<char(j-10+(int)'a');  
   if (k<10) cout<<k;else cout<<char(k-10+(int)'a');  
   if (l<10) cout<<l;else cout<<char(l-10+(int)'a');  
   if (a<10) cout<<a;else cout<<char(a-10+(int)'a');  
   if (b<10) cout<<b;else cout<<char(b-10+(int)'a');  
   if (c<10) cout<<c;else cout<<char(c-10+(int)'a');  
}   
int main(){  
  scanf("%d",&n);  
  for (int i=0;i<=15;i++)  
    for (int j=0;j<=15;j++)  
      for (int k=0;k<=15;k++)  
        for (int l=0;l<=15;l++)  
          for (int a=0;a<=15;a++)  
            for (int b=0;b<=15;b++)  
              for (int c=0;c<=15;c++)  
                if (!f[1][k][l][a][b][c]&&!f[2][j][l][a][b][c]&&  
                    !f[3][j][k][a][b][c]&&!f[4][j][k][l][b][c]&&  
                    !f[5][j][k][l][a][c]&&!f[6][j][k][l][a][b]&&  
                    !f[7][i][l][a][b][c]&&!f[8][i][k][a][b][c]&&  
                    !f[9][i][k][l][b][c]&&!f[10][i][k][l][a][c]&&  
                    !f[11][i][k][l][a][b]&&!f[12][i][j][a][b][c]&&  
                    !f[13][i][j][l][b][c]&&!f[14][i][j][l][a][c]&&  
                    !f[15][i][j][l][a][b]&&!f[16][i][j][k][b][c]&&  
                    !f[17][i][j][k][a][c]&&!f[18][i][j][k][a][b]&&  
                    !f[19][i][j][k][l][c]&&!f[20][i][j][k][l][b]&&  
                    !f[21][i][j][k][l][a])  
               {  
                 n--;  
                 if (!n){  
                   out(i,j,k,l,a,b,c);  
                   return 0;  
                 }  
               f[1][k][l][a][b][c]=1;f[2][j][l][a][b][c]=1;  
               f[3][j][k][a][b][c]=1;f[4][j][k][l][b][c]=1;  
               f[5][j][k][l][a][c]=1;f[6][j][k][l][a][b]=1;  
               f[7][i][l][a][b][c]=1;f[8][i][k][a][b][c]=1;  
               f[9][i][k][l][b][c]=1;f[10][i][k][l][a][c]=1;  
               f[11][i][k][l][a][b]=1;f[12][i][j][a][b][c]=1;  
               f[13][i][j][l][b][c]=1;f[14][i][j][l][a][c]=1;  
               f[15][i][j][l][a][b]=1;f[16][i][j][k][b][c]=1;  
               f[17][i][j][k][a][c]=1;f[18][i][j][k][a][b]=1;  
               f[19][i][j][k][l][c]=1;f[20][i][j][k][l][b]=1;  
               f[21][i][j][k][l][a]=1;    
             }
	return 0;          
}
