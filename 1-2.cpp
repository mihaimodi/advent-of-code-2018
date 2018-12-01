#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
bool frp[1000000],frm[1000000];
char sir[20];
int v[1000];
int i,k,semn;
long long nr,s;
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

        v[++k]=nr;

        memset(sir,0,sizeof(sir));
        fin.getline(sir,20);

    }
    int cnt=0;
    i=1;s=0;
    while(1)
    {
        s=s+v[i];
        if(s<0)
        {
            if(frm[-s]==0)
                frm[-s]++;
            else
            {
                fout<<s<<'\n'<<cnt;
                return 0;
            }
        }
        else
        {
            if(frp[s]==0)
                frp[s]++;
            else
            {
                fout<<s<<'\n'<<cnt;
                return 0;
            }
        }
        if(i==k)
        {
            cnt++;
            i=1;
        }
        else
            i++;
    }

    return 0;

}
