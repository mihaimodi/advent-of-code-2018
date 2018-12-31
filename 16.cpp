#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
char sir[30];
int fr[1001][20];
int Rez[1000][4],Reg[1000][4],Val[1000][4],Aux[1000][4];
int NR=0,OP;
int k;
void operatie()
{
    if(OP==0)//muli
        Aux[k][Val[k][3]]=Aux[k][Val[k][1]]*Val[k][2];
    else if(OP==1)//bani
        Aux[k][Val[k][3]]=Aux[k][Val[k][1]]&Val[k][2];
    else if(OP==2)//addi
        Aux[k][Val[k][3]]=Aux[k][Val[k][1]]+Val[k][2];
    else if(OP==3)//seti
        Aux[k][Val[k][3]]=Val[k][1];
    else if(OP==4)//eqrr
    {
        if(Reg[k][Val[k][1]]==Reg[k][Val[k][2]])
            Aux[k][Val[k][3]]=1;
        else
            Aux[k][Val[k][3]]=0;
    }
    else if(OP==5)//eqir
    {
        if(Val[k][1]==Reg[k][Val[k][2]])
            Aux[k][Val[k][3]]=1;
        else
            Aux[k][Val[k][3]]=0;
    }
    else if(OP==6)
        Aux[k][Val[k][3]]=Aux[k][Val[k][1]];//setr
    else if(OP==7)
        Aux[k][Val[k][3]]=Aux[k][Val[k][1]]|Val[k][2];//bori
    else if(OP==8)//gtri
    {
        if(Aux[k][Val[k][1]]>Val[k][2])
            Aux[k][Val[k][3]]=1;
        else
            Aux[k][Val[k][3]]=0;
    }
    else if(OP==9)//eqri
    {
        if(Reg[k][Val[k][1]]==Val[k][2])
            Aux[k][Val[k][3]]=1;
        else
            Aux[k][Val[k][3]]=0;
    }
    else if(OP==10)//gtir
    {
        if(Val[k][1]>Aux[k][Val[k][2]])
            Aux[k][Val[k][3]]=1;
        else
            Aux[k][Val[k][3]]=0;
    }
    else if(OP==11)//borr
        Aux[k][Val[k][3]]=Aux[k][Val[k][1]]|Aux[k][Val[k][2]];
    else if(OP==12)//addr
        Aux[k][Val[k][3]]=Aux[k][Val[k][1]]+Aux[k][Val[k][2]];
    else if(OP==13)//gtrr
    {
        if(Aux[k][Val[k][1]]>Aux[k][Val[k][2]])
            Aux[k][Val[k][3]]=1;
        else
            Aux[k][Val[k][3]]=0;
    }
    else if(OP==14)//mulr
        Aux[k][Val[k][3]]=Aux[k][Val[k][1]]*Aux[k][Val[k][2]];
    else if(OP==15)//banr
        Aux[k][Val[k][3]]=Aux[k][Val[k][1]]&Aux[k][Val[k][2]];

}
int main()
{
    fin.getline(sir,30);
    while(sir[0]=='B')
    {
        k++;
        Reg[k][0]=sir[9]-'0';
        Reg[k][1]=sir[12]-'0';
        Reg[k][2]=sir[15]-'0';
        Reg[k][3]=sir[18]-'0';
        fin>>OP>>Val[k][1]>>Val[k][2]>>Val[k][3];
        fin.get();fin.getline(sir,30);
        Rez[k][0]=sir[9]-'0';
        Rez[k][1]=sir[12]-'0';
        Rez[k][2]=sir[15]-'0';
        Rez[k][3]=sir[18]-'0';
        for(int j=0;j<=15;j++)
        {
            OP=j;
            for(int K=0;K<=3;K++)//copierea registrului intr-un vector auxiliar pe care vom opera
                Aux[k][K]=Reg[k][K];
            operatie();
            bool ok=1;
            for(int K=0;K<=3;K++)//comparam rezultatul fiecarei instructiuni aplicate cu rezultatul corect
                if(Aux[k][K]!=Rez[k][K])
                {
                    ok=0;
                    break;
                }
            if(ok==1)
                fr[k][++fr[k][0]]=OP;
        }
        if(fr[k][0]>=3)
            NR++;

        fin.get();
        fin.getline(sir,30);
    }
    fout<<"Part 1: "<<NR<<'\n';
    //partea 2
    k=0;
    while(fin>>OP>>Val[0][1]>>Val[0][2]>>Val[0][3])
    {
        for(int K=0;K<=3;K++)
            Aux[0][K]=Reg[0][K];
        operatie();
        for(int K=0;K<=3;K++)
            Reg[0][K]=Aux[0][K];
    }
    fout<<"Part 2: "<<Reg[0][0];
    return 0;
}
