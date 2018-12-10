#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
struct tree
{
    int copii;
    int data;
}a[3000][500];

int v[20000];
int i,l,nrN;
long long s;
void init(int nr)
{
    a[nr][0].copii=v[++i];//nr de copii
    a[nr][0].data=v[++i];//nr de date
    for(int j=1;j<=a[nr][0].copii;j++)
    {
        nrN++;
        a[nr][j].copii=nrN;
        init(nrN);//trecem la copilul urmator
    }
    for(int j=1;j<=a[nr][0].data;j++)
        a[nr][j].data=v[++i];//calculam datele
}
int suma(int nod)
{
    int s=0;
    for(int i=1;i<=a[nod][0].data;i++)//parcurgerea datelor
        s+=a[nod][i].data;
    return s;
}
int calculare(int nod)
{
    int val=0;
    if(a[nod][0].copii==0)//daca nu are copii
        return suma(nod);
    else
        for(int i=1;i<=a[nod][0].data;i++)
            val+=calculare(a[nod][a[nod][i].data].copii);//daca are copii

    return val;
}
int main()
{
    l++;
    while(fin>>v[l])//citire
        l++;
    l--;

    nrN=1;//numarul de noduri
    init(1);//initializarea fiecarui nod
    //partea 1
    for(int i=1;i<=nrN;i++)
        for(int j=1;j<=a[i][0].data;j++)//calcularea sumei
            s+=a[i][j].data;

    fout<<"Part 1: "<<s<<'\n';
    //partea 2
    fout<<"Part 2: "<<calculare(1);

    return 0;
}
