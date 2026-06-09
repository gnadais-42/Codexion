#include "codexion.h"

void    *routine(void *c)
{
    t_coder *coder;

    coder = (t_coder *) c;
    while (!sim_stopped(coder->sim_data))
    {
        compile(coder, coder->sim_data);
        debug(coder, coder->sim_data);
        refactor(coder, coder->sim_data);
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
