#include <fstream>
#include <vector>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
struct sir
{
    long long val;
    sir *urm;
    sir *ult;
};
int juc,jucc;
long long i,bile,Max;
long long scor[500];
char s[50];
int main()
{
    fin.getline(s,50);
    while(s[i]<='9'&&s[i]>='0')
        juc=juc*10+s[i++]-'0';
    while(s[i]>'9'||s[i]<'0')
        i++;
    while(s[i]<='9'&&s[i]>='0')
        bile=bile*10+s[i++]-'0';

	sir *actuala=new sir;
	actuala->val=0;
	actuala->urm=actuala;
	actuala->ult=actuala;

	for(i=1;i<=bile;i++)
    {
        jucc=i%juc;
        if(jucc==0)
            jucc=juc;
		if (i%23==0)
		{
			actuala=actuala->ult->ult->ult->ult->ult->ult->ult;
			scor[jucc]+=actuala->val+i;
			actuala=actuala->urm;
			actuala->ult = actuala->ult->ult;
			actuala->ult->urm=actuala;
		}
		else
		{
			sir *noua=new sir;
			noua->val=i;
			noua->urm=actuala->urm->urm;
			noua->ult=actuala->urm;
			noua->urm->ult=noua;
			noua->ult->urm=noua;
			actuala=noua;
		}
    }

	for(i=1;i<=juc;i++)
		Max=max(Max,scor[i]);

	fout<<Max;
	return 0;
}
