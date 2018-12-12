#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
bool Gen[201][401];
bool pattern[50][6];
long long s[201],ratie;
char sir[201];
int k;
int main()
{
    fin.getline(sir,200);
    int i=15;
    while(sir[i]=='.'||sir[i]=='#')
    {
        if(sir[i]=='#')
            Gen[0][i]=1;//parsam prima generatie
        i++;
    }


    fin.get();

    while(fin.getline(sir,200))
    {
        k++;
        int i;
        for(i=0;i<=4;i++)
            if(sir[i]=='#')
                pattern[k][i+1]=1;//formam patternurile
        if(sir[9]=='#')
            pattern[k][0]=1;
    }

    for(int i=1;i<=200;i++)
    {
        for(int j=3;j<=400;j++)
        {
            bool aux[6];
            for(int x=j-2;x<=j+2;x++)
                    aux[x-j+3]=Gen[i-1][x];//formam vectorul auxiliar

            for(int ii=1;ii<=k;ii++)//parcurgem matricea de patternuri
            {
                bool ok=1;
                for(int jj=1;jj<=5;jj++)
                    if(pattern[ii][jj]!=aux[jj])//comparam patternurile cu cel actual
                    {
                        ok=0;
                        break;
                    }

                if(ok==1)
                {
                    Gen[i][j]=pattern[ii][0];//atribuim valoarea patternului
                    break;
                }
            }
        }

        for(int j=1;j<=400;j++)//calculam suma generatiei
            if(Gen[i][j])
                s[i]+=j-15;
    }
    fout<<"Part 1: "<<s[20]<<'\n';
    //partea a doua
    //dupa cateva generatii suma incepe sa fie progresie aritmetica
    ratie=s[200]-s[199];
    fout<<"Part 2: "<<s[200]+ratie*(50000000000-200);
    return 0;
}
