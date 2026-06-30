#include "../codexion.h"

void    *coder_routine(void *arg)
{
    t_coder *coder;
    t_sim   *sim;

    coder = (t_coder *) arg;
    sim = coder->sim;
    set_last_compiled(coder);
    while (!sim_stopped(sim))
    {
        if (!compile(coder))
            break ;
        if (!debug(coder))
            break ;
        if (!refactor(coder))
            break ;
    }
    print_message(sim, coder, "has left");
    return (NULL);
}