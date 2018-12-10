#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
char sir[20];
int sum,i,k,semn,nr,aux;
int v[1000];
bool vizPOZ[200000],vizNEG[200000];
bool ok=1;
int main()
{
    //partea 1+citire
    while(fin.getline(sir,20))
    {
        k++;
        semn=1;
        if(sir[0]=='-')//aflam semnul
            semn=-1;

        nr=0;
        for(i=1;sir[i]!=0;i++)
            nr=nr*10+sir[i]-'0';
        v[k]=nr*semn;
        sum+=v[k];//calculam suma
        memset(sir,0,sizeof(sir));
    }
    //partea 2
    i=1;
    while(ok)//cautam o frecventa gasita deja
    {
        aux+=v[i];
        if(aux>=0)//numarul este pozitiv
        {
            if(!vizPOZ[aux])
                vizPOZ[aux]=1;
            else
                break;
        }
        else//numarul este strict negativ
        {
            if(!vizNEG[-aux])
                vizNEG[-aux]=1;
            else
                break;
        }
        if(i==k)//reparcurgem sirul
            i=1;
        else
            i++;
    }
    fout<<"Part 2: "<<aux<<'\n';
    fout<<"Part 1: "<<sum<<'\n';
    return 0;

}
