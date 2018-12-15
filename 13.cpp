#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int I,J,k,nrt,nrR;
struct cfr
{
    int i,j;
    int x,y;
    int IntViz;
    bool accidentat;
}v[201];
char Mat[201][201];
bool viz[201][201];
bool ok=0;
short int a[201][201];
int cmp(cfr a,cfr b)
{
    return a.i<b.i;
}
void ParcOriz(int i,int j)
{
        viz[i][j]=1;
        if(Mat[i][j]=='>')
        {
            a[i][j]=1;
            v[++nrt].i=i;
            v[nrt].j=j;
            v[nrt].y=0;
            v[nrt].x=1;
        }
        else if(Mat[i][j]=='<')
        {
            a[i][j]=1;
            v[++nrt].i=i;
            v[nrt].j=j;
            v[nrt].y=0;
            v[nrt].x=-1;
        }
}
void ParcVert(int i,int j)
{
        viz[i][j]=1;
        if(Mat[i][j]=='^')
        {
            a[i][j]=1;
            v[++nrt].i=i;
            v[nrt].j=j;
            v[nrt].y=-1;
            v[nrt].x=0;
        }
        else if(Mat[i][j]=='v')
        {
            a[i][j]=1;
            v[++nrt].i=i;
            v[nrt].j=j;
            v[nrt].y=1;
            v[nrt].x=0;
        }
}
void Parcurgere(int i,int j)
{
    while(Mat[i][j]!='\\')
        ParcOriz(i,j++);
    while(Mat[i][j]!='/')
        ParcVert(i++,j);
    while(Mat[i][j]!='\\')
        ParcOriz(i,j--);
    while(Mat[i][j]!='/')
        ParcVert(i--,j);
}
void pas(int k)
{
    if(Mat[v[k].i][v[k].j]=='\\')//intalnim curba
        swap(v[k].x,v[k].y);
    else if(Mat[v[k].i][v[k].j]=='/')//intalnim curba
    {
        swap(v[k].x,v[k].y);
        v[k].x=-v[k].x;
        v[k].y=-v[k].y;
    }
    else if(Mat[v[k].i][v[k].j]=='+')//intram in intersectie
    {
        v[k].IntViz++;
        if(v[k].IntViz%3==1)//directia se schimba in stanga
        {
            if(v[k].x==0)
                swap(v[k].x,v[k].y);
            else
            {
                swap(v[k].x,v[k].y);
                v[k].x=-v[k].x;
                v[k].y=-v[k].y;
            }
        }
        //daca restul este 2 inseamna ca isi continua drumul
        else if(v[k].IntViz%3==0)//directia se schimba in dreapta
        {
            if(v[k].x==0)
            {
                swap(v[k].x,v[k].y);
                v[k].x=-v[k].x;
                v[k].y=-v[k].y;
            }
            else
                swap(v[k].x,v[k].y);
        }
    }
    a[v[k].i][v[k].j]--;//stergem pozitia anterioara de pe matrice
    v[k].i+=v[k].y;//actualizam pozitia pe axa x
    v[k].j+=v[k].x;//actualizam pozitia pe axa y
    a[v[k].i][v[k].j]++;//actualizam pozitia pe matrice
    I=v[k].i;
    J=v[k].j;
}
int main()
{
    while(fin.getline(Mat[k],200))
        k++;
    k--;
    for(int i=0;i<=k;i++)
    {
        int l=strlen(Mat[i]);
        for(int j=0;j<=l;j++)
            if(Mat[i][j]=='/'&&viz[i][j]==0)//este gasita o cale ferata noua
                Parcurgere(i,j);//parcurgem calea ferata in sensul acelor de ceasornic
    }
    nrR=nrt;//numarul de trenuri ramase
    while(true)
    {
        sort(v+1,v+nrt+1,cmp);//ordonam prioritatea trenurilor dupa linia pe care se afla
        for(int x=1;x<=nrt;x++)
            if(v[x].accidentat==0)
            {
                pas(x);
                if(a[I][J]==2)
                {
                    if(ok==0)
                    {
                        fout<<"Part 1: "<<J<<','<<I<<'\n';
                        ok=1;
                    }
                    //cele 2 trenuri accidentate sunt scoase de pe linie
                    for(int t=1;t<=nrt;t++)
                        if(v[t].i==I&&v[t].j==J)
                            v[t].accidentat=1;
                    nrR-=2;
                    a[I][J]=0;
                }
                if(nrR==1)//ultimului tren ii este afisata pozitia cu un pas inainte
                {
                    for(int t=1;t<=nrt;t++)
                        if(v[t].accidentat==0)
                            fout<<"Part 2: "<<v[t].j-v[t].x<<','<<v[t].i-v[t].y<<'\n';
                    return 0;
                }
            }
    }
}
