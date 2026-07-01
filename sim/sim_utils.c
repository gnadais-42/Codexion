#include "../codexion.h"

int sim_stopped(t_sim *sim)
{
    int stopped;

    pthread_mutex_lock(&sim->stop_mutex);
    stopped = sim->stopped;
    pthread_mutex_unlock(&sim->stop_mutex);

    return (stopped);
}

void    stop_simulation(t_sim *sim)
{
    int i;

    pthread_mutex_lock(&sim->stop_mutex);
    sim->stopped = 1;
    pthread_mutex_unlock(&sim->stop_mutex);

    i = 0;
    while (i < sim->data.n_coders)
    {
        pthread_cond_broadcast(&sim->dongles[i].cond);
        i++;
    }
}

void    print_message(t_sim *sim, t_coder *coder, char *message)
{
    long    time;

    time = timestamp(sim);
    pthread_mutex_lock(&sim->print_mutex);
    printf("%ld %d %s\n", time, coder->id, message);
    pthread_mutex_unlock(&sim->print_mutex);
}