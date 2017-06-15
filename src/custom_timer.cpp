#include "custom_timer.h"

msTimer::msTimer()
{
    restart();
}

void msTimer::restart()
{
    ftime(&t_start);
}

float msTimer::elapsedMs()
{
    timeb t_now;
    ftime(&t_now);
    return (float)(t_now.time - t_start.time) * 1000.0f +
           (float)(t_now.millitm - t_start.millitm);
}