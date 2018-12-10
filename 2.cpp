#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int fr2,fr3,frL[27];
int i,j,l,k,n,dif;
bool ok2,ok3;
char s[300][100];
int main()
{
    while(fin.getline(s[++n],100))
    {
        for(i=0;s[n][i]!=0;i++)
            frL[s[n][i]-'a'+1]++;
        ok2=ok3=1;
        for(i=1;i<=26;i++)
            if(ok2&&frL[i]==2)//litere care apar de 2 ori
            {
                fr2++;
                ok2=0;
            }
            else if(ok3&&frL[i]==3)//litere care apar de 3 ori
            {
                fr3++;
                ok3=0;
            }
        memset(frL,0,sizeof(frL));//reinitializam numarul de litere

    }
    n--;

    fout<<"Part 1: "<<fr2*fr3<<'\n';
    //partea 2

    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++)
        {
            dif=0;
            for(k=0;s[j][k]!=0;k++)//calculam nr de caractere diferite dintre 2 siruri
            {
                if(s[i][k]!=s[j][k])
                    dif++;
                if(dif==2)
                    break;
            }
            if(dif==1)//am gasit
            {
                fout<<"Part 2: ";
                for(k=0;s[i][k];k++)
                    if(s[i][k]==s[j][k])
                        fout<<s[i][k];
                return 0;
            }
        }
    return 0;
}
