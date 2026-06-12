#include "../codexion.h"

int refactor(t_coder *coder)
{
    int time;

    time = coder->sim->data.t_refactor;
    if (sim_stopped(coder->sim))
        return (0);
    print_message(coder->sim, coder, "is refactoring");
    smart_sleep(coder->sim, time);
    return (1);
}