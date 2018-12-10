#include <fstream>
#include <cstdlib>
#define SIZE 400
#define DMAX 10000
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
bool viz[100];
struct parcela
{
    int dist,punct;
    long long DM;
}a[SIZE+1][SIZE+1];
struct coada
{
    int l,c;
}q[SIZE*SIZE+1];
struct str
{
    int lin,col;
}v[61];
int dx[]={0,0,1,0,-1},dy[]={0,1,0,-1,0};
int i,j,k,st=1,dr,l,c,ln,cn,x,y,Max,d,X;
char sir[10];
int A[61];
bool verif(int ln,int cn)
{
    return ln>=0&&cn>=0&&ln<=SIZE&&cn<=SIZE;
}
void coada()
{
    while(st<=dr)
    {
        l=q[st].l;
        c=q[st].c;
        for(k=1;k<=4;k++)
        {
            ln=l+dx[k];
            cn=c+dy[k];
            if(a[ln][cn].dist==0&&verif(ln,cn))//punctul nu a mai fost vizitat
            {
                a[ln][cn].dist=a[l][c].dist+1;
                a[ln][cn].punct=a[l][c].punct;
                dr++;
                q[dr].l=ln;
                q[dr].c=cn;
            }
            else if(a[l][c].dist+1<a[ln][cn].dist&&verif(ln,cn))//punctul a mai fost vizitat dar este inlocuit
            {
                a[ln][cn].dist=a[l][c].dist+1;
                a[ln][cn].punct=a[l][c].punct;
                dr++;
                q[dr].l=ln;
                q[dr].c=cn;
            }
            else if(a[l][c].dist+1==a[ln][cn].dist&&verif(ln,cn)&&a[ln][cn].punct!=a[l][c].punct)//puncte de granita
                a[ln][cn].punct=-1;
        }
        st++;
    }

}
int main()
{
    while(fin.getline(sir,10))
    {
        i=0;x=y=0;
        while(sir[i]>='0'&&sir[i]<='9')
        {
            x=x*10+sir[i]-'0';
            i++;
        }
        i+=2;
        while(sir[i]>='0'&&sir[i]<='9')
        {
            y=y*10+sir[i]-'0';
            i++;
        }
        //bagam punctele in coada
        dr++;
        q[dr].l=y;
        q[dr].c=x;
        a[y][x].punct=dr;
        a[y][x].dist=1;

    }
    X=dr;
    coada();
    //partea 1
    for(i=0;i<=SIZE;i++)//salvam ariile infinite
    {
        viz[a[i][0].punct]=viz[a[i][SIZE].punct]=1;
        viz[a[0][i].punct]=viz[a[SIZE][i].punct]=1;
    }

    for(i=0;i<=SIZE;i++)
        for(j=0;j<=SIZE;j++)
            if(viz[a[i][j].punct]==0)//verificam daca aria e infinita
                A[a[i][j].punct]++;//calculam aria

    for(i=1;i<=50;i++)
        if(A[i]!=0)
            Max=max(A[i],Max);

    fout<<"Part 1: "<<Max<<'\n';
    //partea 2
    for(i=1;i<=X;i++)//formarea vectorului de coordonate
    {
        v[i].col=q[i].c;
        v[i].lin=q[i].l;
    }

    for(i=0;i<=SIZE;i++)//parcurgerea matricei
    {
        for(j=0;j<=SIZE;j++)
        {
            d=0;
            for(k=1;k<=X;k++)
            {
                d+=abs(i-v[k].lin);
                d+=abs(j-v[k].col);
                if(d>=10000)
                    break;
            }
            if(d<10000)//se indeplineste conditia
                A[0]++;
        }
    }
    fout<<"Part 2: "<<A[0]<<'\n';

    return 0;
}
