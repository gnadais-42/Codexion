#include "../codexion.h"

static int create_request(t_dongle *dongle, t_coder *coder);

static int create_request(t_dongle *dongle, t_coder *coder)
{
    t_request   r;
    int         success;

    r.coder_id = coder->id;
    r.deadline = get_last_compiled(coder) + coder->sim->data.t_burnout;
    r.time_of_creation = get_time_ms();
    pthread_mutex_lock(&dongle->mutex);
    success = heap_insert(&dongle->heap, r);
    pthread_mutex_unlock(&dongle->mutex);
    return (success);
}

int create_requests(t_coder *coder)
{
    if (create_request(coder->left, coder) == 0)
        return (0);
    if (create_request(coder->right, coder) == 0)
        return (0);

    return (1);
}

void set_last_used(t_dongle *dongle)
{
    long    time;

    time = get_time_ms();
    dongle->last_used = time;
}
