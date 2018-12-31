#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int xmax,ymax,ymin=2000;
int nrApa,nrSt;
short int Mat[2000][2000];
bool viz[2000][2000];
char sir[25];
bool ok=1;
void minmax(char c,int nr1,int nr2,int nr3)
{
    if(c=='x')
    {
        xmax=max(nr1,xmax);
        ymax=max(max(nr2,nr3),ymax);
        ymin=min(min(nr2,nr3),ymin);
    }
    else
    {
        xmax=max(max(nr2,nr3),xmax);
        ymax=max(ymax,nr1);
        ymin=min(ymin,nr1);
    }
}
void Fill(int x, int y);
void FillPahar(int x, int y)
{
    bool okst=1;//are perete stanga
    bool okdr=1;//are perete dreapta
    int st=x-1;
    int dr=x+1;
    while(Mat[y][st]!=-1)//cautam apa pana la stanga
    {
        Mat[y][st]=1;
        if(Mat[y+1][st]==0||Mat[y+1][st]==1)
        {
            okst=0;
            break;
        }
        st--;
    }
    while(Mat[y][dr]!=-1)//cautam apa pana la dreapta
    {
        Mat[y][dr]=1;
        if(Mat[y+1][dr]==0||Mat[y+1][dr]==1)
        {
            okdr=0;
            break;
        }

        dr++;
    }
    if(okst&&okdr)//are pereti in ambele parti
    {
        for(int j=st+1;j<=dr-1;j++)
            Mat[y][j]=2;
        Mat[y-1][x]=1;
        FillPahar(x,y-1);
    }
    else
    {
        if(!okst)//apa curge in stanga
            Fill(st,y);
        if(!okdr)//apa curge in dreapta
            Fill(dr,y);
    }

}
void Fill(int x, int y)
{
    if(y>ymax)
        return;
    Mat[y][x]=1;
    if(Mat[y+1][x]==-1||Mat[y+1][x]==2)//cauta suprafata
        FillPahar(x,y);
    else if(!Mat[y+1][x])//daca nu gaseste suprafata apa coboara
        Fill(x,y+1);
}
int main()
{
    while(fin.getline(sir,25))
    {
        int nr1=0,nr2=0,nr3=0;
        int i=2;
        while(sir[i]>='0'&&sir[i]<='9')
            nr1=nr1*10+sir[i++]-'0';
        i+=4;
        while(sir[i]>='0'&&sir[i]<='9')
            nr2=nr2*10+sir[i++]-'0';
        i+=2;
        while(sir[i]>='0'&&sir[i]<='9')
            nr3=nr3*10+sir[i++]-'0';
        if(sir[0]=='x')
        {
            for(int i=nr2;i<=nr3;i++)
                Mat[i][nr1]=-1;
            minmax('x',nr1,nr2,nr3);
        }
        else
        {
            for(int j=nr2;j<=nr3;j++)
                Mat[nr1][j]=-1;
            minmax('y',nr1,nr2,nr3);
        }
    }
    Fill(500,0);
    for(int i=ymin;i<=ymax;i++)
        for(int j=1;j<=xmax;j++)
            if(Mat[i][j]>0)
            {
                nrApa++;
                if(Mat[i][j]==2)
                    nrSt++;
            }

    fout<<"Part 1: "<<nrApa<<'\n';
    fout<<"Part 2: "<<nrSt;
    return 0;
}

