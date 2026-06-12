#include "../codexion.h"

int debug(t_coder *coder)
{
    int time;

    time = coder->sim->data.t_debug;
    if (sim_stopped(coder->sim))
        return (0);
    print_message(coder->sim, coder, "is debugging");
    smart_sleep(coder->sim, time);
    return (1);
}