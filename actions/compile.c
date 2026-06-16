#include "../codexion.h"

int compile(t_coder *coder)
{
    long    time;

    time = coder->sim->data.t_compile;
    if (create_requests(coder) == 0)
        return (0); //ainda é preciso mandar um sinal a todas as threads para acordarem e pararem
    if (acquire_dongles(coder) == 0)
        return (0);
    if (sim_stopped(coder->sim))
        return (0);
    print_message(coder->sim, coder, "is debugging");
    smart_sleep(coder->sim, time);
    release_dongles(coder);

    return (1);
}

