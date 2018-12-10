#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
char sir[50005],sir1[50005],aux[50005];
bool viz[200];
int Min=100000,lc;
int main()
{
    fin.getline(sir,50005);
    strcpy(sir1,sir);
    //partea 1
    for(int i=1;sir[i]!=0;i++)
    {
        if(viz[sir[i-1]]==0)//marcam literele prezente
            viz[sir[i-1]]=1;
        if(sir[i-1]==sir[i]+'A'-'a'||sir[i-1]==sir[i]-'A'+'a')//eliminam substantele care reactioneaza
        {
            strcpy(sir+i-1,sir+i+1);
            i=i-2;
        }
    }
    fout<<"Part 1: "<<strlen(sir)<<'\n';
    //partea 2
    for(int i='a';i<='z';i++)
        if(viz[i]||viz[i+'A'-'a'])
        {
            strcpy(aux,sir1);//reinitializarea sirului
            for(int j=0;aux[j]!=0;j++)
                if(aux[j]==i||aux[j]==i+'A'-'a')//elminam literele de acelasi fel
                {
                    strcpy(aux+j,aux+j+1);
                    j--;
                }

            for(int j=1;aux[j]!=0;j++)
                if(aux[j-1]==aux[j]+'A'-'a'||aux[j-1]==aux[j]-'A'+'a')//eliminam substantele care reactioneaza in noul sir
                {
                    strcpy(aux+j-1,aux+j+1);
                    j=j-2;
                }
            lc=strlen(aux);
            Min=min(lc,Min);//calculam lungimea minima
        }
    fout<<"Part 2: "<<Min;

    return 0;
}
