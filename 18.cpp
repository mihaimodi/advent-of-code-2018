#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
char sir[60];
struct viz
{
    int nr;
    int poz;
}v[1000000];
int Mat[60][60],Aux[60][60];
bool ok=1;
int dx[]={0,-1,-1,-1,0,0,1,1,1},dy[]={0, -1,0,1,-1,1,-1,0,1};
int n,l,copaciT,cabaneT;
int main()
{
    while(fin.getline(sir,55))
    {
        for(int i=0;i<=49;i++)
            if(sir[i]=='#')
                Mat[n][i]=2;
            else if(sir[i]=='|')
                Mat[n][i]=1;
        n++;
    }

    for(int m=1;m<=1000;m++)
    {
        memset(Aux,0,sizeof(Aux));
        for(int i=0;i<=49;i++)
            for(int j=0;j<=49;j++)
            {
                int copaci=0;
                int cabane=0;
                for(int dir=1;dir<=8;dir++)
                    if(i+dx[dir]>=0&&i+dx[dir]<=49&&j+dy[dir]>=0&&j+dy[dir]<=49)
                    {
                        if(Mat[i+dx[dir]][j+dy[dir]]==1)
                            copaci++;
                        else if(Mat[i+dx[dir]][j+dy[dir]]==2)
                            cabane++;
                    }
                if(Mat[i][j]==0&&copaci>=3)
                        Aux[i][j]=1;
                else if(Mat[i][j]==1)
                {
                    if(cabane>=3)
                        Aux[i][j]=2;
                    else
                        Aux[i][j]=1;
                }
                else if(Mat[i][j]==2&&cabane>=1&&copaci>=1)
                    Aux[i][j]=2;
            }
        for(int i=0;i<=49;i++)
            for(int j=0;j<=49;j++)
                Mat[i][j]=Aux[i][j];
        cabaneT=0;
        copaciT=0;
        for(int i=0;i<=49;i++)
            for(int j=0;j<=49;j++)
            {
                if(Mat[i][j]==2)
                    cabaneT++;
                if(Mat[i][j]==1)
                    copaciT++;
            }

        //partea 1
        if(m==10)
            fout<<"Part 1: "<<cabaneT*copaciT<<'\n';
        //partea 2
        if(v[cabaneT*copaciT].poz==0)
        {
            ok=0;
            v[cabaneT*copaciT].poz=m;
            v[m].nr=cabaneT*copaciT;
        }
        else if(ok==1)
        {
            fout<<"Part 2: "<<v[(1000000000-m)%(m-v[cabaneT*copaciT].nr)].nr;
            return 0;
        }
        else
            ok=1;
          fout<<cabaneT*copaciT<<'\n';
    }

    return 0;
}
