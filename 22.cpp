#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
char sir[20];
int i=7,pericol;
int L,Xt,Yt,st,dr;
struct pestera
{
    short int tip;
    long long e;
}Mat[6000][6000];
struct coada
{
    int l;
    int c;
}q[10000];
struct matrice_coada
{
    int timp;
    int unealta;
    //0=nimic
    //1=torta
    //2=unelte de urcat
}MatQ[6000][6000];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int main()
{
    fin.getline(sir,20);
    while(sir[i]>='0'&&sir[i]<='9')
        L=L*10+sir[i++]-'0';
    fin.getline(sir,20);
    i=8;
    while(sir[i]>='0'&&sir[i]<='9')
        Xt=Xt*10+sir[i++]-'0';
    i++;
    while(sir[i]>='0'&&sir[i]<='9')
        Yt=Yt*10+sir[i++]-'0';
    for(int i=0;i<=Yt;i++)
        Mat[i][0].e=(i*48271ll+L)%20183,Mat[i][0].tip=Mat[i][0].e%3;
    for(int j=0;j<=Xt;j++)
        Mat[0][j].e=(j*16807ll+L)%20183,Mat[0][j].tip=Mat[0][j].e%3;
    for(int i=1;i<=Yt;i++)
        for(int j=1;j<=Xt;j++)
            Mat[i][j].e=(1ll*Mat[i-1][j].e*Mat[i][j-1].e+L)%20183,Mat[i][j].tip=Mat[i][j].e%3;
    //prima parte
    for(int i=0;i<=Yt;i++)
        for(int j=0;j<=Xt;j++)
            pericol+=Mat[i][j].tip;
    fout<<"Part 1: "<<pericol<<'\n';
    //partea 2
    st=dr=1;
    q[st].l=q[st].c=0;
    MatQ[0][0].unealta=1;
    MatQ[0][0].timp=1;
    while(st<=dr)
    {
        int l=q[st].l;
        int c=q[st].c;
        for(int i=0;i<=3;i++)
        {
            int ln=l+dx[i];
            int cn=c+dy[i];
            if(ln<0||ln>Yt||cn<0||cn>Xt)
                continue;
            if(MatQ[l][c].unealta==0&&Mat[ln][cn].tip==0)
            {
                MatQ[ln][cn].unealta=2;
                MatQ[ln][cn].timp=MatQ[l][c].timp+8;
                q[++dr].l=ln;
                q[dr].c=cn;
            }
            else if(MatQ[l][c].unealta==1&&Mat[ln][cn].tip==1)
            {
                MatQ[ln][cn].unealta=0;
                MatQ[ln][cn].timp=MatQ[l][c].timp+8;
                q[++dr].l=ln;
                q[dr].c=cn;
            }
            else if(MatQ[l][c].unealta==2&&Mat[ln][cn].tip==2)
            {
                MatQ[ln][cn].unealta=1;
                MatQ[ln][cn].timp=MatQ[l][c].timp+8;
                q[++dr].l=ln;
                q[dr].c=cn;
            }
            else if((MatQ[ln][cn].timp==0||MatQ[ln][cn].timp>MatQ[l][c].timp+1))
            {
                MatQ[ln][cn].unealta=MatQ[l][c].unealta;
                MatQ[ln][cn].timp=MatQ[l][c].timp+1;
                q[++dr].l=ln;
                q[dr].c=cn;
            }
        }
        st++;
    }

    fout<<"Part 2: "<<MatQ[Yt][Xt].timp-1;
    return 0;
}
