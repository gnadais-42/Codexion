
#include "../codexion.h"

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
		dongles[i].heap = create_heap(get_compare(sch));
		pthread_mutex_init(&(dongles[i].mutex), NULL);
		pthread_cond_init(&(dongles[i].cond), NULL);
		dongles[i].available = 1;
		dongles[i].last_used = 0;
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
		destroy_heap(&dongles[i].heap);
		pthread_mutex_destroy(&(dongles[i].mutex));
		pthread_cond_destroy(&(dongles[i].cond));
		i++;
	}

	free(dongles);
}
