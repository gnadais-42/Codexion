#include "codexion.h"

long    get_time_ms()
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

long    timestamp(t_sim *sim)
{
    return (get_time_ms() - sim->start_time);
}

void    smart_sleep(t_sim * sim, long duration)
{
    long    start_time;

    start_time = get_time_ms();
    while (!sim_stopped(sim))
    {
        if (get_time_ms() - start_time >= duration)
            return ;
        usleep(300);
    }
}