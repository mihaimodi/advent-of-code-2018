#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int Reg[6],Ult;
bool Viz[20000000];
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
    else if(v[nrOp].nr==3)//bani
        Reg[C]=(Reg[A]&B);
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
    else if(v[nrOp].nr==9)//eqri
        Reg[C]=(Reg[A]==B);
    else if(v[nrOp].nr==10)//bori
        Reg[C]=(Reg[A]|B);
    else if(v[nrOp].nr==11)//gtir
        Reg[C]=(A>Reg[B]);
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
        else if(strcmp(op,"bani")==0)
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
        else if(strcmp(op,"eqri")==0)
            v[nrOp].nr=9;
        else if(strcmp(op,"bori")==0)
            v[nrOp].nr=10;
        else if(strcmp(op,"gtir")==0)
            v[nrOp].nr=11;
    }
    //partea 1
    while(Reg[ip]<=nrOp)
    {
        operatie(Reg[ip],v[Reg[ip]].A,v[Reg[ip]].B,v[Reg[ip]].C);
        Reg[ip]++;
        if(Reg[ip]==28)//observam ca la randul 28 se gaseste raspunsul in registrul 4
            break;
    }
    fout<<"Part 1: "<<Reg[4]<<'\n';
    //partea 2
    while(Reg[ip]<=nrOp)//executam operatiile pana cand se gaseste un registru care s a mai intalnit
    {
        operatie(Reg[ip],v[Reg[ip]].A,v[Reg[ip]].B,v[Reg[ip]].C);
        Reg[ip]++;
        if(Reg[ip]==28&&!Viz[Reg[4]])
        {
            Viz[Reg[4]]=1;
            Ult=Reg[4];//ultima valoare
        }

        else if(Reg[ip]==28)
        {
            fout<<"Part 2: "<<Ult;//afisam ultima valoare valida inainte sa se repete
            return 0;
        }
    }
}

