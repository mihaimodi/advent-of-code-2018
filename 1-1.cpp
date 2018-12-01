#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int s[1000];
char sir[20];
int i,k,semn;
long long nr;
int main()
{
    fin.getline(sir,20);
    while(strlen(sir))
    {
        if(sir[0]=='+')
            semn=1;
        else
            semn=-1;
        nr=0;
        for(i=1;sir[i]!=0;i++)
            nr=nr*10+sir[i]-'0';
        nr=nr*semn;

        s[++k]=s[k-1]+nr;

        memset(sir,0,sizeof(sir));
        fin.getline(sir,20);
    }
    fout<<s[k];

    return 0;

}
