
#include "../codexion.h"

static void	get_heap(t_heap *, t_schedule sch)
{
	
}

t_dongle	*create_dongles(int n, t_schedule sch)
{
	t_dongle	*dongles;
	int			i;

	dongles = malloc(sizeof(t_dongle) * n);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dongles[i].waitline = create_heap();
		if (!dongles[i].waitline)
		{
			destroy_dongles(dongles, i);
			return (NULL);
		}
		pthread_mutex_init(&(dongles[i].mutex), NULL);
		pthread_cond_init(&(dongles[i].cond), NULL);
		pthread_mutex_init(&(dongles[i].heap_mutex), NULL);
		dongles[i].available_at = 0;
		dongles[i].occupied = 0;
		i++;
	}
	return (dongles);
}

void	destroy_dongles(t_dongle *dongles, int n)
{
	int	i;
	if (!dongles)
		return ;

	i = 0;
	while (i < n)
	{
		destroy_heap(dongles[i].waitline);
		pthread_mutex_destroy(&(dongles[i].mutex));
		pthread_mutex_destroy(&(dongles[i].heap_mutex));
		pthread_cond_destroy(&(dongles[i].cond));
		i++;
	}

	free(dongles);
}

void take_dongle(t_dongle *d, t_coder *c)
{
    pthread_mutex_lock(&d->mutex);

    while (!dongle_available(d, c) && !sim_stopped(c->sim_data))
        pthread_cond_wait(&d->cond, &d->mutex);

    d->occupied = 1;

    pthread_mutex_unlock(&d->mutex);
}

void release_dongle(t_dongle *d, t_sim *s)
{
    pthread_mutex_lock(&d->mutex);

    d->occupied = 0;
    d->available_at = get_time_ms() + s->data.d_cooldown;
	
	pthread_mutex_lock(&d->heap_mutex);
	heap_pop(d->waitline);
	pthread_mutex_unlock(&d->heap_mutex);

    pthread_cond_broadcast(&d->cond);

    pthread_mutex_unlock(&d->mutex);
}
