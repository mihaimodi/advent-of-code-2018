#include <bits/stdc++.h>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");

char sir[1200][50];
bool timp[301][61];
int dormit[3501],fr[3501][61],MFM[3501];
int k,i,j,x,m,Max,gMax,M,Msomn,frMax,MinfrMax;
int id[301];
int main()
{
    fin.getline(sir[++k],50);
    while(strlen(sir[k]))
        fin.getline(sir[++k],50);//citire
    k--;
    for(i=1;i<k;i++)
        for(j=i+1;j<=k;j++)
            if(strcmp(sir[i],sir[j])>0)//sortare
            {
                strcpy(sir[0],sir[i]);
                strcpy(sir[i],sir[j]);
                strcpy(sir[j],sir[0]);
            }

    for(i=1;i<=k;i++)
    {
        M=0;//reinitializare
        j=12;//parcurgerea incepe de la ora si minut

        M=(sir[i][15]-'0')*10+sir[i][16]-'0';

        if(sir[i][19]=='G')//gardian nou incepe tura
        {
            x++;//trecem la noaptea urmatoare
            j=26;//incepem parcurgerea de la prima cifra a id-ului
            while(sir[i][j]<='9'&&sir[i][j]>='0')//calculam id-ul curent
            {
                id[x]=id[x]*10+sir[i][j]-'0';
                j++;
            }
        }
        else if(sir[i][19]=='f')//gardianul se culca
            Msomn=M;
        else if(sir[i][19]=='w')//gardianul se trezeste-salvam minutele in care a dormit
        {
            for(m=Msomn;m<M;m++)
                timp[x][m]=1;
            dormit[id[x]]+=M-Msomn;
        }
    }

    for(i=1;i<=3500;i++)//aflam gardianul care a dormit cel mai mult
        if(dormit[i]>dormit[Max])
            Max=i;

    for(i=1;i<=300;i++)
        for(j=1;j<=60;j++)
            if(timp[i][j])
                fr[id[i]][j]++;//calculam in ce minute a dormit fiecare gardian in fiecare noapte

    for(i=1;i<=3500;i++)
        if(dormit[i])
        {
            frMax=0,MinfrMax=0;
            for(j=1;j<=60;j++)
                if(fr[i][j]>fr[i][MinfrMax])
                {
                    MinfrMax=j;
                    frMax=fr[i][MinfrMax];
                }

            fr[i][0]=frMax;//frecventa maxima
            MFM[i]=MinfrMax;//minutul cu frecventa maxima pt fiecare gardian
        }

    for(i=1;i<=3500;i++)
        if(fr[i][0]>fr[gMax][0])
            gMax=i;//gardianul cu minutul cu frecventa maxima

    fout<<"Part 1: "<<MFM[Max]*Max<<'\n';
    fout<<"Part 2: "<<MFM[gMax]*gMax<<'\n';

    return 0;
}
