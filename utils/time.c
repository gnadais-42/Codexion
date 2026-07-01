#include "../codexion.h"

long    get_time_ms()
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long    timestamp(t_sim *sim)
{
    return (get_time_ms() - sim->start_time);
}

void    smart_sleep(t_sim *sim, long duration)
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

void    cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex, long time)
{
    struct  timespec ts;
    long    total_time;

    total_time = get_time_ms() + time;
    ts.tv_sec = total_time / 1000;
    ts.tv_nsec = (total_time % 1000) * 1000000L;
    pthread_cond_timedwait(cond, mutex, &ts);
}