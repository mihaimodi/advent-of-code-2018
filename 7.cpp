#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
vector <int> v[10000];
char s[50],sir[50];
int q[10000];
int vizN[27],viz[27],muncitori[11];
int timp,Max,i,k,st=1,dr,l=-1;
bool ap[27],dep[27];
bool ok;
int cnt(int a, int b)
{
    return a>b;
}
int main()
{
    while(fin.getline(s,50))
    {
        vizN[s[36]-'A'+1]++;//de cate ori e nevoie sa vizitam
        ap[s[36]-'A'+1]=ap[s[5]-'A'+1]=1;//aparitia
        dep[s[36]-'A'+1]=1;//dependenta
        v[s[5]-'A'+1].push_back(s[36]-'A'+1);//adaugare in coada
    }

    for(i=1;i<=26;i++)
    {
        if(ap[i]==1&&dep[i]==0)//verificare dependenta
        {
            dr++;
            q[dr]=i;
        }
        if(v[i].size()>0)
            sort(v[i].begin(),v[i].end(),cnt);//sortare descrescatoare
    }
    //partea 1
    while(st<=dr)
    {
        sort(q+st,q+dr+1);//sortare a cozii
        sir[++l]=q[st]+'A'-1;//adaugare in sir
        for(i=v[q[st]].size()-1;i>=0;i--)//parcurgere a dependentelor
        {
            int x=v[q[st]].back();
            if(viz[x]<vizN[x])//verificare nr dependente
                viz[x]++;
            if(viz[x]==vizN[x])//adaugam in coada
            {
                viz[x]++;
                dr++;
                q[dr]=x;
            }
            v[q[st]].pop_back();//scoatere din vector
        }
        st++;
    }
    fout<<"Part 1: "<<sir<<'\n';
    //partea 2
    return 0;
}
