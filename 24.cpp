#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
struct sist
{
    int units;
    int hp;
    short int slash,blud,cold,rad,fire;
    //-1 immune
    //1 weak
    int init;
    int DMG,TypeDMG;
    //1-slash
    //2-blud
    //3-cold
    //4-rad
    //5-fire
    int inf;//e infectat sau nu
    int tinta;
    int DMG1;//damage dat in runda respectiva
}v[40];
int k,GrAct;
bool tintit[30];
char sir[200];
int cmptinta(sist a, sist b)
{
    return a.DMG*a.units>b.DMG*b.units||(a.DMG*a.units==b.DMG*b.units&&a.init>b.init);
}
int cmpatac(sist a,sist b)
{
    return a.init<b.init;
}
void tinta(int k)
{
    v[k].tinta=0;
    v[k].DMG1=0;
    for(int i=1;i<=GrAct;i++)
    {
        int dmgdat=0;
        if(tintit[i]==1)
            continue;
        if((v[k].TypeDMG==1&&v[i].slash==1)||(v[k].TypeDMG==2&&v[i].blud==1)||(v[k].TypeDMG==3&&v[i].cold==1)||(v[k].TypeDMG==4&&v[i].rad==1)||(v[k].TypeDMG==5&&v[i].fire==1))
            dmgdat=2*v[k].DMG*v[k].units;
        else if((v[k].TypeDMG==1&&v[i].slash==-1)||(v[k].TypeDMG==2&&v[i].blud==-1)||(v[k].TypeDMG==3&&v[i].cold==-1)||(v[k].TypeDMG==4&&v[i].rad==-1)||(v[k].TypeDMG==5&&v[i].fire==-1))
            dmgdat=0;
        else
            dmgdat=v[k].DMG*v[k].units;
        if(dmgdat>v[k].DMG1)
        {
            v[k].tinta=i;
            v[k].DMG1=dmgdat;
        }
        else if(v[k].DMG1&&v[i].DMG*v[i].units>v[v[k].tinta].DMG*v[v[k].tinta].units)
            v[k].tinta=i;
        else if(v[k].DMG1&&v[i].DMG*v[i].units==v[v[k].tinta].DMG*v[v[k].tinta].units&&v[i].init>v[v[k].tinta].init)
            v[k].tinta=i;
    }
    tintit[v[k].tinta=1];
}
void atac(int k)
{
    if(v[k].tinta==0)
        return;
    v[v[k].tinta].units-=v[k].DMG1/v[v[k].tinta].hp;
    if(v[v[k].tinta].units<=0)
    {
        v[v[k].tinta].DMG1=0;
        v[v[k].tinta].DMG=0;
        v[v[k].tinta].hp=0;
        v[v[k].tinta].inf=0;
        v[v[k].tinta].init=0;
        v[v[k].tinta].units=0;
        GrAct--;
    }
}
bool ok()
{
    bool oki=0;//gasit infectat
    bool okn=0;//gasit neinfectat
    for(int i=1;i<=k;i++)
        if(v[i].units)
        {
            if(v[i].inf==1)
                oki=1;
            else
                okn=1;
            if(oki&&okn)
                return 1;
        }
    return 0;
}
int main()
{
    fin.getline(sir,200);
    fin.getline(sir,200);
    while(sir[0]!='I')
    {
        if(sir[0]==0)
        {
            fin.getline(sir,200);
            continue;
        }
        k++;
        int i=0;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].units=v[k].units*10+sir[i++]-'0';
        i+=17;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].hp=v[k].hp*10+sir[i++]-'0';
        i+=12;
        if(sir[i]=='(')
        {
            i++;
            if(sir[i]=='w')
            {
                i+=8;
                while(sir[i]!=')'&&sir[i]!=';')
                {
                     if(sir[i]=='s')
                        v[k].slash=1;
                    else if(sir[i]=='b')
                        v[k].blud=1;
                    else if (sir[i]=='c')
                        v[k].cold=1;
                    else if(sir[i]=='r')
                        v[k].rad=1;
                    else if(sir[i]=='f')
                        v[k].fire=1;
                    while(sir[i]!=')'&&sir[i]!=';'&&sir[i]!=',')
                        i++;
                    if(sir[i]!=')'&&sir[i]!=';')
                        i+=2;
                }
            }
            if(sir[i]==';')
                i+=2;
            if(sir[i]=='i')
            {
                i+=10;
                while(sir[i]!=')'&&sir[i]!=';')
                {
                     if(sir[i]=='s')
                        v[k].slash=-1;
                    else if(sir[i]=='b')
                        v[k].blud=-1;
                    else if (sir[i]=='c')
                        v[k].cold=-1;
                    else if(sir[i]=='r')
                        v[k].rad=-1;
                    else if(sir[i]=='f')
                        v[k].fire=-1;
                    while(sir[i]!=')'&&sir[i]!=';'&&sir[i]!=',')
                        i++;
                    if(sir[i]!=')'&&sir[i]!=';')
                        i+=2;
                }
            }
            i+=2;
        }
        i+=25;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].DMG=v[k].DMG*10+sir[i++]-'0';
        i++;
        if(sir[i]=='s')
            v[k].TypeDMG=1;
        else if(sir[i]=='b')
            v[k].TypeDMG=2;
        else if (sir[i]=='c')
            v[k].TypeDMG=3;
        else if(sir[i]=='r')
            v[k].TypeDMG=4;
        else if(sir[i]=='f')
            v[k].TypeDMG=5;
        while(sir[i]<'0'||sir[i]>'9')
            i++;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].init=v[k].init*10+sir[i++]-'0';
        fin.getline(sir,200);
    }
    while(fin.getline(sir,200))
    {
        k++;
        int i=0;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].units=v[k].units*10+sir[i++]-'0';
        i+=17;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].hp=v[k].hp*10+sir[i++]-'0';
        i+=12;
        if(sir[i]=='(')
        {
            i++;
            if(sir[i]=='i')
            {
                i+=10;
                while(sir[i]!=')'&&sir[i]!=';')
                {
                     if(sir[i]=='s')
                        v[k].slash=-1;
                    else if(sir[i]=='b')
                        v[k].blud=-1;
                    else if (sir[i]=='c')
                        v[k].cold=-1;
                    else if(sir[i]=='r')
                        v[k].rad=-1;
                    else if(sir[i]=='f')
                        v[k].fire=-1;
                    while(sir[i]!=')'&&sir[i]!=';'&&sir[i]!=',')
                        i++;
                    if(sir[i]!=')'&&sir[i]!=';')
                        i+=2;
                }
            }
            if(sir[i]==';')
                i+=2;
            if(sir[i]=='w')
            {
                i+=8;
                while(sir[i]!=')'&&sir[i]!=';')
                {
                     if(sir[i]=='s')
                        v[k].slash=1;
                    else if(sir[i]=='b')
                        v[k].blud=1;
                    else if (sir[i]=='c')
                        v[k].cold=1;
                    else if(sir[i]=='r')
                        v[k].rad=1;
                    else if(sir[i]=='f')
                        v[k].fire=1;
                    while(sir[i]!=')'&&sir[i]!=';'&&sir[i]!=',')
                        i++;
                    if(sir[i]!=')'&&sir[i]!=';')
                        i+=2;
                }

            }
            if(sir[i]==';')
                i+=2;
            if(sir[i]=='i')
            {
                i+=10;
                while(sir[i]!=')'&&sir[i]!=';')
                {
                     if(sir[i]=='s')
                        v[k].slash=-1;
                    else if(sir[i]=='b')
                        v[k].blud=-1;
                    else if (sir[i]=='c')
                        v[k].cold=-1;
                    else if(sir[i]=='r')
                        v[k].rad=-1;
                    else if(sir[i]=='f')
                        v[k].fire=-1;
                    while(sir[i]!=')'&&sir[i]!=';'&&sir[i]!=',')
                        i++;
                    if(sir[i]!=')'&&sir[i]!=';')
                        i+=2;
                }
            }
            i+=2;
        }
        i+=25;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].DMG=v[k].DMG*10+sir[i++]-'0';
        i++;
        if(sir[i]=='s')
            v[k].TypeDMG=1;
        else if(sir[i]=='b')
            v[k].TypeDMG=2;
        else if (sir[i]=='c')
            v[k].TypeDMG=3;
        else if(sir[i]=='r')
            v[k].TypeDMG=4;
        else if(sir[i]=='f')
            v[k].TypeDMG=5;
        while(sir[i]<'0'||sir[i]>'9')
            i++;
        while(sir[i]>='0'&&sir[i]<='9')
            v[k].init=v[k].init*10+sir[i++]-'0';
        v[k].inf=1;
    }

    GrAct=k;
    while(ok())
    {
        if(!ok())
        {
            int oO;
            oO=1;
        }
        sort(v+1,v+k+1,cmptinta);
        memset(tintit,0,sizeof(tintit));
        for(int i=1;i<=GrAct;i++)
            tinta(i);

        //sort(v+1,v+k+1,cmpatac);
        for(int i=1;i<=GrAct;i++)
            atac(i);
    }
    int s=0;
    for(int i=1;i<=k;i++)
        s+=v[i].units;
    fout<<s;






    return 0;
}
