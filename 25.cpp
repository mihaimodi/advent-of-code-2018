#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
struct stea
{
    int x,y,z,t;
}v[1500];
char sir[50];
int k,i,nrC;
int Graf[1500][1500];
short int S;
bool Viz[1500];
void semn()
{
    if(sir[i]=='-')
    {
        S=-1;
        i++;
    }
    else
        S=1;
}
int abs(int x)
{
    if(x<0)
        return -x;
    return x;
}
int manhattan(int a, int b)
{
    return abs(v[a].x-v[b].x)+abs(v[a].y-v[b].y)+abs(v[a].z-v[b].z)+abs(v[a].t-v[b].t);
}
void parcurgere(int k)
{
    Viz[k]=1;
    for(int i=1;i<=Graf[k][0];i++)
        if(Viz[Graf[k][i]]==0)
            parcurgere(Graf[k][i]);
}
int main()
{
    while(fin.getline(sir,50))
    {
        i=0;
        k++;
        semn();
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].x=v[k].x*10+sir[i++]-'0';
        v[k].x*=S;
        i++;
        semn();
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].y=v[k].y*10+sir[i++]-'0';
        v[k].y*=S;
        i++;
        semn();
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].z=v[k].z*10+sir[i++]-'0';
        v[k].z*=S;
        i++;
        semn();
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].t=v[k].t*10+sir[i++]-'0';
        v[k].t*=S;
    }
    for(int i=1;i<k;i++)
        for(int j=i+1;j<=k;j++)
            if(manhattan(i,j)<=3)
            {
                Graf[i][++Graf[i][0]]=j;
                Graf[j][++Graf[j][0]]=i;
            }
    for(int i=1;i<=k;i++)
        if(Viz[i]==0)
        {
            parcurgere(i);
            nrC++;
        }
    fout<<nrC;
    return 0;
}
