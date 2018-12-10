#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int ind,n,m,i,j,x,y,nr;
char sir[50];
int a[1500][1500];
int b[1500][1500];
bool viz[1500];
int main()
{

    while(fin.getline(sir,50))
    {
        n=m=x=y=ind=0;
        i=1;
        while(sir[i]>='0'&&sir[i]<='9')//aflam indicele
        {
            ind=ind*10+sir[i]-'0';
            i++;
        }
        i=i+3;
        while(sir[i]>='0'&&sir[i]<='9')//aflam coloana de inceput
        {
            m=m*10+sir[i]-'0';
            i++;
        }
        i++;
        while(sir[i]>='0'&&sir[i]<='9')//aflam linia de inceput
        {
            n=n*10+sir[i]-'0';
            i++;
        }
        i+=2;
        while(sir[i]>='0'&&sir[i]<='9')//aflam latimea
        {
            x=x*10+sir[i]-'0';
            i++;
        }
        i++;
        while(sir[i]>='0'&&sir[i]<='9')//aflam lungimea
        {
            y=y*10+sir[i]-'0';
            i++;
        }

        for(i=n+1;i<=n+y;i++)
        {
            for(j=m+1;j<=m+x;j++)
            {
                if(a[i][j]>0)
                {
                    viz[b[i][j]]=1;
                    viz[ind]=1;
                }
                b[i][j]=ind;
                a[i][j]++;
            }
        }
    }
    for(i=1;i<=1200;i++)
        for(j=1;j<=1200;j++)
            if(a[i][j]>1)
                nr++;
    fout<<"Part 1: "<<nr<<'\n';
    for(i=1;i<=1499;i++)
        if(!viz[i])
        {
            fout<<"Part 2: "<<i<<'\n';
            return 0;
        }

}
