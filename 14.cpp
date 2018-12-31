#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int e1=1,e2=2,n,k=2,nrRet,nrCif;
char sir[100000000]="037";
char sirNr[10];
bool Part1,Part2;
int calccif(int x)
{
    int nr=0;
    while(x)
    {
        nr++;
        x/=10;
    }
    return nr;
}
void transfchar(int x)
{
    int cifra=0;
    while(x)
    {
        cifra++;
        sirNr[nrCif-cifra]=x%10+'0';
        x/=10;
    }
}
int main()
{
    fin>>n;
    nrCif=calccif(n);
    transfchar(n);
    while(true)
    {
        int s=sir[e1]+sir[e2]-2*'0';
        if(s>9)
            sir[++k]='1';
        if(!Part2&&strcmp(sir+k-nrCif+1,sirNr)==0)
        {
            fout<<"Part 2: "<<k-nrCif<<'\n';
            Part2=1;
        }
        sir[++k]=s%10+'0';
        if(!Part2&&strcmp(sir+k-nrCif+1,sirNr)==0)
        {
            fout<<"Part 2: "<<k-nrCif<<'\n';
            Part2=1;
        }
        e1+=sir[e1]-'0'+1;
        e2+=sir[e2]-'0'+1;
        if(e1!=k)
            e1%=k;
        if(e2!=k)
            e2%=k;
        if(k==n+10)
        {
            fout<<"Part 1: "<<sir+1+n<<'\n';
            Part1=1;
        }

        if(Part1&&Part2)
            return 0;
    }
}

