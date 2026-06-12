#include "../codexion.h"

t_coder	*create_coders(t_dongle *dongles, int n, t_sim *sim)
{
	t_coder	*coders;
	int		i;

	if (!dongles)
		return (NULL);

	coders = malloc(sizeof(t_coder) * n);
	if (!coders)
		return (NULL);

	i = 0;
	while (i < n){
		coders[i].id = i + 1;
		coders[i].left = &dongles[i];
		coders[i].right = &dongles[(i + 1) % n];
		pthread_mutex_init(&(coders[i].mutex), NULL);
		coders[i].sim = sim;
		coders[i].last_compiled = sim->start_time;
		coders[i].times_compiled = 0;
		i++;
	}
	return (coders);
}

void	destroy_coders(t_coder *coders, int n)
{
	int	i;

	if (!coders)
		return ;
	i = 0;
	while (i < n)
		pthread_mutex_destroy(&(coders[i++].mutex));
	free(coders);
}