#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
int k,nrc,LN,CN,ture,L,DMG;
int dx[]={0,-1,0,0,1};
int dy[]={0,0,-1,1,0};
int MatQ[75][75];
int a[75][75],MatAux[75][75];
char Mat[75][75];
bool ok=1,OK=1;
int abs(int x)
{
    if(x<0)
        return -x;
    return x;
}
struct que
{
    int l;
    int c;
}q[500];
struct creaturi
{
    int goblin;
    int elf;
    int hp;
    int l,c;
    int damage;
}v[100];
struct auxiliara
{
    int goblin;
    int elf;
    int hp;
    int l,c;
    int damage;
}aux[100];
int cmp(creaturi a,creaturi b)
{
    return a.l<b.l||(a.l==b.l&&a.c<b.c);
}
void lupta(int k)
{
    int HPmin=500;
    int Tinta;
    int l=v[k].l;
    int c=v[k].c;
    for(int i=1;i<=4;i++)
    {
        int ln=l+dx[i];
        int cn=c+dy[i];
        for(int j=1;j<=nrc;j++)
            if(v[k].elf==1-v[j].elf&&v[k].goblin==1-v[j].goblin&&ln==v[j].l&&cn==v[j].c)
                if(HPmin>v[j].hp)//daca sunt mai multe tinte se ia cea cu HP-ul mic
                {
                    HPmin=v[j].hp;
                    Tinta=j;
                }
    }
    v[Tinta].hp-=v[k].damage;//se ataca tinta
}
int coada(int k)
{
    memset(MatQ,0,sizeof(MatQ));//matricea de distante
    memset(&q,0,sizeof(&q));//vectorul coada
    int dmin=1000;
    int st=1;
    int dr=1;
    int lmin=100,cmin=100;
    q[st].l=v[k].l;
    q[st].c=v[k].c;
    while(st<=dr)
    {
        int l=q[st].l;
        int c=q[st].c;
        if(MatQ[l][c]+1>dmin)//facem coada pana intalnim distanta minima pana la inamic
            break;
        for(int i=1;i<=4;i++)
        {
            int ln=l+dx[i];
            int cn=c+dy[i];
            if(MatQ[ln][cn]==0&&a[ln][cn]==0)
            {
                dr++;
                q[dr].l=ln;
                q[dr].c=cn;
                MatQ[ln][cn]=MatQ[l][c]+1;
            }
            else if((v[k].goblin==1&&a[ln][cn]==2)||(v[k].elf==1&&a[ln][cn]==1))
            {
                MatQ[ln][cn]=MatQ[l][c]+1;
                if(dmin>MatQ[ln][cn])//gasim inamicul la distanta mica
                {
                    dmin=MatQ[ln][cn];
                    lmin=l;
                    cmin=c;
                }
                else if(dmin==MatQ[ln][cn])//gasim un alt inamic la distanta minima
                {
                    if(l<lmin)//este inlocuita destinatia in cazul in care noul inamic este citit inainte
                    {
                        dmin=MatQ[ln][cn];
                        lmin=l;
                        cmin=c;
                    }
                    else if(l==lmin&&c<cmin)
                    {
                        dmin=MatQ[ln][cn];
                        lmin=l;
                        cmin=c;
                    }
                }
            }
        }
        st++;
    }
    if(lmin!=100&&cmin!=100)
    {
        while(MatQ[lmin][cmin]>1)
            for(int j=1;j<=4;j++)
                if(MatQ[lmin+dx[j]][cmin+dy[j]]<MatQ[lmin][cmin]&&MatQ[lmin+dx[j]][cmin+dy[j]]>0)//parcurgem invers matricea de distante pana la primul pas
                {
                    lmin+=dx[j];
                    cmin+=dy[j];
                    break;
                }
        LN=lmin;
        CN=cmin;
        return dmin;
    }
    return -1;//daca nu se gaseste niciun inamic
}
bool verif(int k)
{
    int tip;
    if(v[k].goblin==1)
        tip=1;
    else tip=2;
    for(int i=0;i<=L;i++)//se cauta daca este macar un inamic pe harta
    {
        int l=strlen(Mat[i]);
        for(int j=0;j<=l;j++)
            if(a[i][j]!=0 && a[i][j]!=-1 && a[i][j]!=tip)
                return 1;
    }
    return 0;
}
void pas(int k)
{
    ok=verif(k);
    if(ok==0)//daca ok este 0 s-a terminat lupta
        return;
    int dist=coada(k);
    if(dist>1)//se face un pas
    {
        a[v[k].l][v[k].c]=0;
        v[k].l=LN;
        v[k].c=CN;
        if(v[k].goblin==1)
            a[v[k].l][v[k].c]=1;
        else if(v[k].elf==1)
            a[v[k].l][v[k].c]=2;
        dist--;
    }
    if(dist==1)//se lupta
    {
        lupta(k);
        for(int i=1;i<=nrc;i++)
            if(v[i].hp<=0)
            {
                a[v[i].l][v[i].c]=0;
                v[i].l=100;
                v[i].c=100;
                v[i].damage=0;
            }
    }
}
int main()
{
    while(fin.getline(Mat[k],50))
        k++;
    k--;
    L=k;
    for(int i=0;i<=k;i++)
    {
        int l=strlen(Mat[i]);
        for(int j=0;j<=l;j++)
        {
            if(Mat[i][j]=='#')
                MatAux[i][j]=-1;
            else if(Mat[i][j]=='G')
            {
                MatAux[i][j]=1;
                aux[++nrc].l=i;
                aux[nrc].c=j;
                aux[nrc].hp=200;
                aux[nrc].goblin=true;
                aux[nrc].damage=3;
            }

            else if(Mat[i][j]=='E')
            {
                MatAux[i][j]=2;
                aux[++nrc].l=i;
                aux[nrc].c=j;
                aux[nrc].hp=200;
                aux[nrc].elf=true;
                aux[nrc].damage=3;
            }
        }
    }
    //prima parte
    for(int i=1;i<=nrc;i++)//initializare
    {
        v[i].elf=aux[i].elf;
        v[i].goblin=aux[i].goblin;
        v[i].l=aux[i].l;
        v[i].c=aux[i].c;
        v[i].damage=aux[i].damage;
        v[i].hp=aux[i].hp;
    }
    for(int i=0;i<=L;i++)
    {
        int l=strlen(Mat[i]);
        for(int j=0;j<=l;j++)
            a[i][j]=MatAux[i][j];
    }
    while(true)
    {
        sort(v+1,v+nrc+1,cmp);//mutarile se fac in oridinea coordonatelor
        for(int i=1;i<=nrc;i++)
        {
            if(v[i].hp>0)
                pas(i);
            if(ok==0)
            {
                int HP=0;
                for(int i=1;i<=nrc;i++)
                    if(v[i].hp>0)
                        HP+=v[i].hp;
                fout<<"Part 1: "<<HP*ture<<'\n';
                OK=0;
                break;
            }
        }
        if(OK==0)
            break;
        ture++;
    }
    //partea a 2-a

    while(true)
    {
        DMG++;//cresc daunele produse de elf la fiecare simulare noua
        for(int i=1;i<=nrc;i++)//reinitializare
        {
            v[i].elf=aux[i].elf;
            v[i].goblin=aux[i].goblin;
            v[i].l=aux[i].l;
            v[i].c=aux[i].c;
            v[i].damage=aux[i].damage;
            v[i].hp=aux[i].hp;
            if(v[i].elf==1)
                v[i].damage+=DMG;
        }
        for(int i=0;i<=L;i++)
        {
            int l=strlen(Mat[i]);
            for(int j=0;j<=l;j++)
                a[i][j]=MatAux[i][j];
        }
        ture=0;ok=1;
        OK=1;
        while(true)
        {
            sort(v+1,v+nrc+1,cmp);
            for(int i=1;i<=nrc;i++)
            {
                if(v[i].hp>0)
                    pas(i);
                for(int j=1;j<=nrc;j++)
                    if(v[j].elf==1&&v[j].hp<=0)
                    {
                        OK=0;
                        break;
                    }
                if(OK==0)//un elf a murit
                    break;
                if(ok==0)
                {
                    int HP=0;
                    for(int i=1;i<=nrc;i++)
                        if(v[i].hp>0)
                            HP+=v[i].hp;
                    fout<<"Part 2: "<<HP*ture<<' '<<3+DMG<<'\n';
                    return 0;
                }
            }
            if(OK==0)
                break;
            ture++;
        }
    }

}
