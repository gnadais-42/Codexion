#include "../codexion.h"

static void release_dongle(t_dongle *dongle);

static void release_dongle(t_dongle *dongle)
{
    heap_pop(&dongle->heap);
    set_last_used(dongle);
    pthread_cond_broadcast(&dongle->cond);
    pthread_mutex_unlock(&dongle->mutex);
}

void    release_dongles(t_coder *coder)
{
    release_dongle(coder->left);
    release_dongle(coder->right);
}