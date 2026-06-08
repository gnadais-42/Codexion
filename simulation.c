#include "codexion.h"

static int create_coders_dongles_data(t_sim *sim, char *argv[]);
static int create_threads_and_others(t_sim *sim, char *argv[]);

static int create_coders_dongles_data(t_sim *sim, char *argv[])
{
    t_data  *data;

    data = create_data(argv);
    if (!data)
        return (0);
    sim->data = *data;
    sim->dongles = create_dongles(data->n_coders, data->schedule);
    if (!sim->dongles)
    {
        free(data);
        return (0);
    }
    sim->coders = create_coders(sim->dongles, data->n_coders, sim);
    if (!sim->coders)
    {
        free(data);
        return (0);
    }
    free(data);
    return (1);
}

static int  create_threads_and_others(t_sim *sim, char *argv[])
{
    if (!create_coders_dongles_data(sim, argv))
        return (0);
    sim->threads = create_threads(sim->coders, sim->data.n_coders, routine, sim);
    if (sim->thread_count != sim->data.n_coders)
        return (0);
    
    return (1);
}

t_sim   *create_simulation(char *argv[])
{
    t_sim   *sim;

    sim = malloc(sizeof(t_sim));
    if (!sim)
        return (NULL);
    memset(sim, 0, sizeof(t_sim));
    pthread_mutex_init(&(sim->stop_mutex), NULL);
    pthread_mutex_init(&(sim->print_mutex), NULL);
    sim->start_time = get_time_ms();
    if (!create_threads_and_others(sim, argv))
    {
        destroy_simulation(sim);
        return (NULL);
    }
    if (pthread_create(&(sim->monitor), NULL, monitor_routine, sim) != 0)
    {
        destroy_simulation(sim);
        return (NULL);
    }

    return (sim);
}

void    destroy_simulation(t_sim *sim)
{
    stop_simulation(sim);
    join_threads(sim->threads, sim->thread_count);
    if (sim->monitor_created)
        pthread_join(sim->monitor, NULL);
    destroy_threads(sim->threads);
    destroy_coders(sim->coders, sim->data.n_coders);
    destroy_dongles(sim->dongles, sim->data.n_coders);
    pthread_mutex_destroy(&(sim->stop_mutex));
    pthread_mutex_destroy(&(sim->print_mutex));

    free(sim);
}