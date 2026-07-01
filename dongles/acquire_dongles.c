#include "../codexion.h"

static void get_dongle_order(t_coder *coder, t_dongle **first, t_dongle **second);
static int  acquire_dongle(t_dongle *dongle, t_sim *sim, int coder_id);
static int  dongle_off_cooldown(t_dongle *dongle, long cooldown);
static int  is_first_in_heap(t_dongle *dongle, int coder_id);

static int  is_first_in_heap(t_dongle *dongle, int coder_id)
{
    return (heap_peek(&dongle->heap).coder_id == coder_id);
}

static int  dongle_off_cooldown(t_dongle *dongle, long cooldown)
{
    long    curr;

    if (dongle->last_used == 0)
        return (1);
    curr = get_time_ms();
    return (curr - dongle->last_used >= cooldown);
}

static int acquire_dongle(t_dongle *dongle, t_sim *sim, int coder_id)
{
    pthread_mutex_lock(&dongle->mutex);
    while (!sim_stopped(sim))
    {
        if (!is_first_in_heap(dongle, coder_id))
            cond_wait(&dongle->cond, &dongle->mutex, sim->data.t_compile);
        else if (!dongle_off_cooldown(dongle, sim->data.d_cooldown))
            cond_wait(&dongle->cond, &dongle->mutex, sim->data.d_cooldown - (get_time_ms() - dongle->last_used));
        else
            break ;
    }
    if (sim_stopped(sim))
    {
        pthread_mutex_unlock(&dongle->mutex);
        return (0);
    }
    return (1);
}

static void get_dongle_order(t_coder *coder, t_dongle **first, t_dongle **second)
{
    if (coder->left < coder->right)
    {
        *first = coder->left;
        *second = coder->right;
    }
    else
    {
        *first = coder->right;
        *second = coder->left;
    }
}

int acquire_dongles(t_coder *coder)
{
    t_dongle    *first;
    t_dongle    *second;

    get_dongle_order(coder, &first, &second);
    if (!acquire_dongle(first, coder->sim, coder->id))
        return (0);
    if (!acquire_dongle(second, coder->sim, coder->id))
    {
        pthread_mutex_unlock(&first->mutex);
        return (0);
    }
    return (1);
}