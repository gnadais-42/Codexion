#include "codexion.h"

void    request_dongles(t_coder *coder, t_sim *sim)
{
	t_request   request;

    request.coder_id = coder->id;
    request.deadline = coder->last_compiled + sim->data.t_burnout;
    request.request_time = get_time_ms();

    pthread_mutex_lock(&(coder->l_dongle->heap_mutex));
    heap_push(coder->l_dongle->waitline, request);
    pthread_mutex_unlock(&(coder->l_dongle->heap_mutex));

    pthread_mutex_lock(&(coder->r_dongle->heap_mutex));
    heap_push(coder->r_dongle->waitline, request);
    pthread_mutex_unlock(&(coder->r_dongle->heap_mutex));
}

int dongle_available(t_dongle *d, t_coder *coder)
{
    if (d->occupied)
        return (0);
    if (get_time_ms() < d->available_at)
        return (0);
    pthread_mutex_lock(&d->heap_mutex);
    if (d->waitline->arr[0].coder_id != coder->id)
    {
        pthread_mutex_unlock(&d->heap_mutex);
        return (0);
    }
    pthread_mutex_unlock(&d->heap_mutex);
    return (1);
}

void wait_dongle(t_dongle *d)
{
    pthread_cond_wait(&d->cond, &d->mutex);
}

void acquire_both(t_coder *c)
{
    t_dongle *a = c->l_dongle;
    t_dongle *b = c->r_dongle;

    if (a > b)
    {
        t_dongle *tmp = a;
        a = b;
        b = tmp;
    }

    take_dongle(a, c);
    take_dongle(b, c);
}