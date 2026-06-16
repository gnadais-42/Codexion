#include "../codexion.h"

static int acquire_dongle(t_dongle *dongle, t_sim *sim, int coder_id);
static int  dongle_off_cooldown(t_dongle *dongle, long cooldown);
static int  coder_can_take(t_dongle *dongle, int coder_id, long cooldown);

static int  coder_can_take(t_dongle *dongle, int coder_id, long cooldown)
{
    if (!dongle_off_cooldown(dongle, cooldown))
        return (0);
    if (heap_peek(&dongle->heap).coder_id != coder_id)
        return (0);
    return (1);
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
    while (!coder_can_take(dongle, coder_id, sim->data.d_cooldown) && !sim_stopped(sim))
    {
        pthread_cond_broadcast(&dongle->cond);
        pthread_cond_wait(&dongle->cond, &dongle->mutex);
    }
    if (sim_stopped(sim))
    {
        pthread_mutex_unlock(&dongle->mutex);
        return (0);
    }
    return (1);
}

int acquire_dongles(t_coder *coder)
{
    t_dongle    *first;
    t_dongle    *second;

    if (coder->left < coder->right)
    {
        first = coder->left;
        second = coder->right;
    }
    else
    {
        first = coder->right;
        second = coder->left;
    }
    if (!acquire_dongle(first, coder->sim, coder->id))
        return (0);
    else if (!acquire_dongle(second, coder->sim, coder->id))
    {
        pthread_mutex_unlock(&first->mutex);
        return (0);
    }
    return (1);
}