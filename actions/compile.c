#include "../codexion.h"

int compile(t_coder *coder)
{
    long    time;

    time = coder->sim->data.t_compile;
    if (create_requests(coder) == 0)
        return (0);
    if (acquire_dongles(coder) == 0)
        return (0);
    if (sim_stopped(coder->sim))
        return (0);
    print_message(coder->sim, coder, "is compiling");
    smart_sleep(coder->sim, time);
    release_dongles(coder);
    increment_compilation(coder);
    print_times_compiled(coder);
    return (1);
}

