#include "codexion.h"

void    *routine(void *c)
{
    t_coder *coder;

    coder = (t_coder *) c;
    while (!sim_stopped(coder->sim_data))
    {
        pthread_mutex_lock(&(coder->state_mutex));
        coder->last_compiled = get_time_ms();
        coder->n_compiled++;
        pthread_mutex_unlock(&(coder->state_mutex));
        print_message(coder->sim_data, coder->id, "is compiling");
        smart_sleep(coder->sim_data, coder->sim_data->data.t_compile);
        print_message(coder->sim_data, coder->id, "is debugging");
        smart_sleep(coder->sim_data, coder->sim_data->data.t_debug);
        print_message(coder->sim_data, coder->id, "is refactoring");
        smart_sleep(coder->sim_data, coder->sim_data->data.t_refactor);
    }

    return (NULL);
}

void    *monitor_routine(void *s)
{
    int     i;
    t_sim   *sim;

    sim = (t_sim *) s;
    while (!sim_stopped(sim))
    {
        i = 0;
        while (i < sim->data.n_coders)
        {
            if (get_time_ms() - last_compile(&(sim->coders[i])) > sim->data.t_burnout)
            {
                print_message(sim, i + 1, "has burned out");
                stop_simulation(sim);
                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}

void    *null_func(void *arg){return (NULL);}
