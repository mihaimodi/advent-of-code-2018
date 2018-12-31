#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int Reg[6];
struct operatii
{
    int A,B,C;
    int nr;

}v[50];
void operatie(int nrOp, int A, int B, int C)
{
    if(v[nrOp].nr==1)//addi
        Reg[C]=Reg[A]+B;
    else if(v[nrOp].nr==2)//seti
        Reg[C]=A;
    else if(v[nrOp].nr==3)//mulr
        Reg[C]=Reg[A]*Reg[B];
    else if(v[nrOp].nr==4)//eqrr
        Reg[C]=(Reg[A]==Reg[B]);
    else if(v[nrOp].nr==5)//addr
        Reg[C]=Reg[A]+Reg[B];
    else if(v[nrOp].nr==6)//gtrr
        Reg[C]=(Reg[A]>Reg[B]);
    else if(v[nrOp].nr==7)//setr
        Reg[C]=Reg[A];
    else if(v[nrOp].nr==8)//muli
        Reg[C]=Reg[A]*B;
}
char junk[5];
char op[4];
int A,B,C;
int nrOp=-1,ip;
int main()
{
    fin>>junk>>ip;
    while(fin>>op>>A>>B>>C)
    {
        nrOp++;
        v[nrOp].A=A;
        v[nrOp].B=B;
        v[nrOp].C=C;
        if(strcmp(op,"addi")==0)
            v[nrOp].nr=1;
        else if(strcmp(op,"seti")==0)
            v[nrOp].nr=2;
        else if(strcmp(op,"mulr")==0)
            v[nrOp].nr=3;
        else if(strcmp(op,"eqrr")==0)
            v[nrOp].nr=4;
        else if(strcmp(op,"addr")==0)
            v[nrOp].nr=5;
        else if(strcmp(op,"gtrr")==0)
            v[nrOp].nr=6;
        else if(strcmp(op,"setr")==0)
            v[nrOp].nr=7;
        else if(strcmp(op,"muli")==0)
            v[nrOp].nr=8;
    }
    //partea 1
    while(Reg[ip]<=nrOp)
    {
        operatie(Reg[ip],v[Reg[ip]].A,v[Reg[ip]].B,v[Reg[ip]].C);
        Reg[ip]++;
    }
    fout<<"Part 1: "<<Reg[0]<<'\n';
    //partea 2
    memset(Reg,0,sizeof(Reg));
    Reg[0]=1;
    while(Reg[ip]<nrOp)
    {
        operatie(Reg[ip],v[Reg[ip]].A,v[Reg[ip]].B,v[Reg[ip]].C);
        Reg[ip]++;
    }
    //codul folosit de elfi e prea incet asa ca il vom transforma in C++ :)
    for(int i=1;i*i<Reg[5];i++)//calculam suma factorilor primi a nr din registrul 5
        if(Reg[5]%i==0)
            Reg[0]+=i+Reg[5]/i;
    if(sqrt(Reg[5])*sqrt(Reg[5])==Reg[5])
        Reg[0]+=sqrt(Reg[5]);
    fout<<"Part 2: "<<Reg[0];
    return 0;
}

