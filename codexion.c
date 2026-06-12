#include "codexion.h"

int main(int argc, char *argv[])
{
    t_sim   *sim;

    if (!validator(argc, argv))
        return (1);

    sim = create_simulation(argv);
    if (!sim)
        return (2);
    start_simulation(sim);
    destroy_simulation(sim);
    
    return (0);
}