#include "../codexion.h"

static int  compiled_enough(t_coder *coder, int times_to_compile)
{
    int n;

    n = get_n_compilation(coder);
    return (n >= times_to_compile);
}

static int  burnout(t_coder *coder, long time_to_burnout)
{
    long    time;

    time = get_time_ms();
    return (time - get_last_compiled(coder) >= time_to_burnout);
}

static int  loop_through_coders(t_coder *coders, t_sim *sim)
{
    int i;
    int finished;

    i = 0;
    finished = 1;
    while (i < sim->data.n_coders)
    {
        if (burnout(&coders[i], (long) sim->data.t_burnout))
            return (i + 1);
        if (!compiled_enough(&coders[i], sim->data.n_compiles))
            finished = 0;
        i++;
    }
    if (finished)
        return (-1);
    else
        return (0);
}

void    *monitor_routine(void *arg)
{
    t_sim   *sim;
    int     state;

    sim = (t_sim *) arg;
    while (!sim_stopped(sim))
    {
        state = loop_through_coders(sim->coders, sim);
        if (state == -1)
        {
            stop_simulation(sim);
            break ;
        }
        else if (state > 0)
        {
            printf("bababooey kill simulation\n");
            stop_simulation(sim);
            print_message(sim, &sim->coders[state - 1], "burned out");
            break ;
        }
        usleep(500);
    }
    return (NULL);
}