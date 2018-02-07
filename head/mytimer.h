#ifndef MYTIMER_H
#define MYTIMER_H
#include<QObject>
#include<QTImer>

class Mytimer:public QTimer
{Q_OBJECT
public:
    Mytimer();
void settimes(int n);
void addtimes(int mod_n);
int gettimes();

private:
    int times;
};


#endif // MYTIMER_H
