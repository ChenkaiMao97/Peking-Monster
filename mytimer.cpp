#include"mytimer.h"
#include<QDebug>
Mytimer::Mytimer()
{
   times=0;
}

void Mytimer::settimes(int n)
{
    times=n;
}

void Mytimer::addtimes(int mod_n)
{
    times=(times+1)%mod_n;

}

int Mytimer::gettimes()
{
    return times;
}

//void Mytimer::singlestart(int milisec)
//{
//    setSingleShot(true);
//    start(milisec);
//}
