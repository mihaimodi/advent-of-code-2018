#include <climits>
#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int s[305][305],a[305][305];
int cod,Ymax,Xmax,Lmax;
int smax=INT_MIN;
int main()
{
    fin>>cod;
    for(int i=1;i<=300;i++)//parcurgem y
        for(int j=1;j<=300;j++)//parcurgem x
        {
            int id=j+10;
            int aux=(id*i+cod)*id;
            a[i][j]=(aux/100)%10-5;
            s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];//vector de sume partiale
        }

    for(int i=1;i<=298;i++)//parcurgem y
        for(int j=1;j<=298;j++)//parcurgem x
            if(s[i+2][j+2]-s[i+2][j-1]-s[i-1][j+2]+s[i-1][j-1]>smax)
            {
                smax=s[i+2][j+2]-s[i+2][j-1]-s[i-1][j+2]+s[i-1][j-1];
                Ymax=i;
                Xmax=j;
            }
    fout<<"Part 1: "<<Xmax<<','<<Ymax<<'\n';
    //partea 2
    smax=INT_MIN;
    for(int i=1;i<=300;i++)
        for(int j=1;j<=300;j++)
        {
            int lim=300-max(i,j);//limita matricei
            for(int n=0;n<=lim;n++)
                if(s[i+n-1][j+n-1]-s[i+n-1][j-1]-s[i-1][j+n-1]+s[i-1][j-1]>smax)
                {
                    smax=s[i+n-1][j+n-1]-s[i+n-1][j-1]-s[i-1][j+n-1]+s[i-1][j-1];
                    Ymax=i;
                    Xmax=j;
                    Lmax=n;
                }
        }
    fout<<"Part 2: "<<Xmax<<','<<Ymax<<','<<Lmax;
}
