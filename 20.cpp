#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
char sir[15000];
int dx[]={0,1,0,-1,0};
int dy[]={0,0,1,0,-1};
int i=1;
int l,x,y,dmax,nr;
bool ok=0;
struct usi
{
    bool sus,jos;
    bool st,dr;
    int d;
    bool viz;
}a[1001][1001];
struct que
{
    int l,c;
}q[500000];

void Rec(int l,int c)
{
    while(sir[i]!='$')
    {
        if(ok==1)
        {
            ok=0;
            Rec(l,c);
        }
        if(sir[i]=='W')
        {
            i++;
            a[l][c].st=1;
            a[l][--c].dr=1;
        }
        else if(sir[i]=='E')
        {
            i++;
            a[l][c].dr=1;
            a[l][++c].st=1;
        }
        else if(sir[i]=='N')
        {
            i++;
            a[l][c].sus=1;
            a[--l][c].jos=1;
        }
        else if(sir[i]=='S')
        {
            i++;
            a[l][c].jos=1;
            a[++l][c].sus=1;
        }
        else if(sir[i]=='(')//daca gasim paranteza deschisa apelam recursiv
        {
            i++;
            Rec(l,c);
        }
        else if(sir[i]==')')
        {
            i++;
            return;
        }
        else if(sir[i]=='|')
        {
            i++;
            ok=1;
            return;
        }
    }
}
void coada()
{
    a[500][500].d=1;
    q[1].l=500;
    q[1].c=500;
    int st=1;
    int dr=1;
    while(st<=dr)
    {
        int l=q[st].l;
        int c=q[st].c;
        if(a[l][c].sus&&!a[l-1][c].viz&&(a[l-1][c].d==0||a[l-1][c].d>a[l][c].d+1))//verificam daca este o usa deschisa la N
        {
            a[l-1][c].d=a[l][c].d+1;
            q[++dr].l=l-1;
            q[dr].c=c;
            a[l-1][c].viz=1;
        }
        if(a[l][c].jos&&!a[l+1][c].viz&&(a[l+1][c].d==0||a[l+1][c].d>a[l][c].d+1))//verificam daca este o usa deschisa la S
        {
            a[l+1][c].d=a[l][c].d+1;
            q[++dr].l=l+1;
            q[dr].c=c;
            a[l+1][c].viz=1;
        }
        if(a[l][c].st&&!a[l][c-1].viz&&(a[l][c-1].d==0||a[l][c-1].d>a[l][c].d+1))//verificam daca este o usa deschisa la V
        {
            a[l][c-1].d=a[l][c].d+1;
            q[++dr].l=l;
            q[dr].c=c-1;
            a[l][c-1].viz=1;
        }
        if(a[l][c].dr&&!a[l][c+1].viz&&(a[l][c+1].d==0||a[l][c+1].d>a[l][c].d+1))//verificam daca este o usa deschisa la E
        {
            a[l][c+1].d=a[l][c].d+1;
            q[++dr].l=l;
            q[dr].c=c+1;
            a[l][c+1].viz=1;
        }
        st++;
    }
}
int main()
{
    fin.getline(sir,15000);
    l=strlen(sir);
    Rec(500,500);//incepem din mijlocul matricei
    coada();
    for(int i=1;i<=1000;i++)
        for(int j=1;j<=1000;j++)
        {
            if(a[i][j].d>dmax)
                dmax=a[i][j].d-1;
            if(a[i][j].d>1000)
                nr++;
        }
    fout<<"Part 1: "<<dmax<<'\n';
    fout<<"Part 2: "<<nr;
    return 0;
}
