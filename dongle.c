
#include "codexion.h"

t_dongle	*create_dongles(int n, char *schedule)
{
	t_dongle	*dongles;
	int			i;

	dongles = malloc(sizeof(t_dongle) * n);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dongles[i].waitline = create_heap(n, schedule);
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
