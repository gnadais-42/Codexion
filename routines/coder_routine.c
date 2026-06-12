#include "../codexion.h"

void    *coder_routine(void *arg)
{
    t_coder *coder;
    t_sim   *sim;

    coder = (t_coder *) arg;
    sim = coder->sim;
    while (!sim_stopped(sim))
    {
        if (!compile(coder))
            break ;
        if (!debug(coder))
            break ;
        if (!refactor(coder))
            break ;
    }
    return (NULL);
}