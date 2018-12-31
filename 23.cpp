#include <fstream>
#include <climits>
#include <algorithm>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
struct robot
{
    int x,y,z;
    int range;
}v[1100];
int k,rangeMax;
int minx,miny,minz,maxx,maxy,maxz,Dmax,L=1;
char sir[200];
int abs(int x)
{
    if(x<0)
        return -x;
    return x;
}
int manhattan(int x1,int y1,int z1,int x2,int y2,int z2)
{
    return abs(x1-x2)+abs(y1-y2)+abs(z1-z2);
}
int cmp(robot a,robot b)
{
    return a.range>b.range;
}
int main()
{
    while(fin.getline(sir,200))
    {
        short int semn;
        k++;
        int i=5;
        if(sir[i]=='-')
            semn=-1,i++;
        else semn=1;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].x=v[k].x*10+sir[i++]-'0';
        v[k].x=v[k].x*semn;
        i++;
        if(sir[i]=='-')
            semn=-1,i++;
        else semn=1;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].y=v[k].y*10+sir[i++]-'0';
        v[k].y=v[k].y*semn;
        i++;
        if(sir[i]=='-')
            semn=-1,i++;
        else semn=1;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].z=v[k].z*10+sir[i++]-'0';
        v[k].z=v[k].z*semn;
        i+=5;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].range=v[k].range*10+sir[i++]-'0';
    }
    //prima parte
    sort(v+1,v+k+1,cmp);
    for(int i=1;i<=k;i++)
    {
        if(manhattan(v[1].x,v[1].y,v[1].z,v[i].x,v[i].y,v[i].z)<=v[1].range)
            rangeMax++;
        maxx=max(v[i].x,maxx);
        minx=min(v[i].x,minx);
        maxy=max(v[i].y,maxy);
        miny=min(v[i].y,miny);
        maxz=max(v[i].z,maxz);
        minz=min(v[i].z,minz);
    }
    fout<<"Part 1: "<<rangeMax<<'\n';
    //partea 2
    //fout<<minx<<' '<<maxx<<' '<<miny<<' '<<maxy<<' '<<minz<<' '<<maxz;
    Dmax=max(max(maxx-minx,maxy-miny),maxz-minz);
    while(L<Dmax)
        L*=2;//latura cubului pe care il vom imparti

    while(true)
    {
        int botsinrange=0;
        for(int i=1;i<=8;i++)
        {
            int botiC=calc(i,x,y,z);
            if(botiC>botsinrange)
            {
               botsinrange=botiC;
               xC=x;
               yC=y;
               zC=z;
            }
            else if(botiC==botsinrange&&manhattan(x,y,z,0,0,0)<manhattan(xC,yC,zC,0,0,0))
            {
                xC=x;
                yC=y;
                zC=z;
            }
        }
        L/=2;
        if(L==1)
        {
            fout<<"Part 2: "<<botsinrange;
            return 0;
        }

    }
}
