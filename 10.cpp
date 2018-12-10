#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
struct directii
{
    int l,c;
}dir[300];
struct coordonate
{
    int l,c;
}coord[300];
char sir[60];
int i,k,semn,cnt;
int kcmin,kcmax,klmin,klmax,cmax,cmin=1000,lmax,lmin=1000;
bool Mat[1000][1000];
void minmax()//functie pt calcularea extremele
{
    if(coord[k].l<coord[klmin].l)
        klmin=k;
    if(coord[k].l>coord[klmax].l)
        klmax=k;
    if(coord[k].c<coord[kcmin].c)
        kcmin=k;
    if(coord[k].c>coord[kcmax].c)
        kcmax=k;
}
void calcsemn()
{
    if(sir[i++]=='-')
        semn=-1;
    else
        semn=1;
}
void citire()
{
    i=10;k++;
    calcsemn();
    while(sir[i]>='0'&&sir[i]<='9')
        coord[k].c=coord[k].c*10+sir[i++]-'0';
    coord[k].c*=semn;
    i+=2;
    calcsemn();
    while(sir[i]>='0'&&sir[i]<='9')
        coord[k].l=coord[k].l*10+sir[i++]-'0';
    coord[k].l*=semn;
    i+=12;
    calcsemn();
    while(sir[i]>='0'&&sir[i]<='9')
        dir[k].c=dir[k].c*10+sir[i++]-'0';
    dir[k].c*=semn;
    i+=2;
    calcsemn();
    while(sir[i]>='0'&&sir[i]<='9')
        dir[k].l=dir[k].l*10+sir[i++]-'0';
    dir[k].l*=semn;
    minmax();
}
int main()
{
    while(fin.getline(sir,60))
        citire();

    while(coord[kcmax].c>coord[kcmin].c&&coord[klmax].l>coord[klmin].l)//miscam punctele pana cand sunt apropiate
    {
        for(int i=1;i<=k;i++)
        {
            coord[i].l+=dir[i].l;
            coord[i].c+=dir[i].c;
        }
        cnt++;//nr de operatii facute creste
    }

    for(int i=1;i<=k;i++)//inversam ultima operatie
    {
        coord[i].l-=dir[i].l;
        coord[i].c-=dir[i].c;
    }
    cnt--;

    for(int i=1;i<=k;i++)
    {
        Mat[coord[i].l][coord[i].c]=1;//marcam punctele
        //aflam laturile dreptunghiului in care se afla literele
        cmax=max(cmax,coord[i].c);
        cmin=min(cmin,coord[i].c);
        lmax=max(lmax,coord[i].l);
        lmin=min(lmin,coord[i].l);
    }
    fout<<"Part 1:\n";
    for(int i=lmin;i<=lmax;i++)
    {
        for(int j=cmin;j<=cmax;j++)
            if(Mat[i][j])
                fout<<"#";
            else
                fout<<" ";
        fout<<'\n';
    }
    fout<<"Part 2:"<<cnt;
    return 0;
}
