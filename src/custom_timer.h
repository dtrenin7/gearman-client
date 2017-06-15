#ifndef CUSTOM_TIMER
#define CUSTOM_TIMER

#include <sys/timeb.h>

class msTimer
{
public:
    msTimer();
    void restart();
    float elapsedMs();
private:
    timeb t_start;
};

#endif