#include "codexion.h"

t_sim *create_simulation(char *argv[])
{
    t_data      *data;
    t_dongle    *dongles;
    t_coder     *coders;

    data = create_data(argv);
    if (!data)
        return (NULL);
    dongles = create_dongles(data->n_coders);
    if (!dongles)
    {
        destroy_data(data);
        return (NULL);
    }
    coders = create_coders(dongles, data->n_coders);
    if (!coders){
        destroy_dongles(dongles, data->n_coders);
        destroy_data(data);
        return (NULL);
    }
    
}