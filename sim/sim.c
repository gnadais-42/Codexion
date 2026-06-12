#include "../codexion.h"

t_sim   *create_simulation(char *argv[])
{
    t_sim   *sim;

    sim = malloc(sizeof(t_sim));
    if (!sim)
        return (NULL);
    memset(sim, 0, sizeof(t_sim));
    pthread_mutex_init(&(sim->stop_mutex), NULL);
    pthread_mutex_init(&(sim->print_mutex), NULL);
    sim->stopped = 1;
    sim->data = create_data(argv);
    sim->dongles = create_dongles(sim->data.n_coders, sim->data.schedule);
    if (!sim->dongles)
        destroy_simulation(sim);
    sim->coders = create_coders(sim->dongles, sim->data.n_coders, sim);
    if (!sim->coders)
        destroy_simulation(sim);
    
    return (sim);
}

void    destroy_simulation(t_sim *sim)
{
    int i;

    i = 0;
    while (i < sim->thread_count)
        pthread_join(sim->coders[i++].thread, NULL);
    if (sim->monitor_created)
        pthread_join(sim->monitor, NULL); // Talvez seja melhor trocar a ordem destes joins
    destroy_dongles(sim->dongles, sim->data.n_coders);
    destroy_coders(sim->coders, sim->data.n_coders);

    pthread_mutex_destroy(&sim->print_mutex);
    pthread_mutex_destroy(&sim->stop_mutex);

    free(sim);
}

int start_simulation(t_sim *sim)
{
    int i;

    i = 0;
    sim->start_time = get_time_ms();
    sim->stopped = 0;
    while (i < sim->data.n_coders)
    {
        if (pthread_create(&sim->coders[i].thread, NULL, coder_routine, &sim->coders[i]) != 0)
            return (0);
        sim->thread_count++;
        i++;
    }
    if (pthread_create(&sim->monitor, NULL, monitor_routine, sim) != 0)
        return (0);
    sim->monitor_created = 1;
    return (1);
}