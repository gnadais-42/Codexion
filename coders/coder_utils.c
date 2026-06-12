#include "../codexion.h"

long	get_last_compiled(t_coder *coder)
{
	long	last;

	pthread_mutex_lock(&(coder->mutex));
	last = coder->last_compiled;
	pthread_mutex_unlock(&(coder->mutex));

	return (last);
}

void	set_last_compiled(t_coder *coder)
{
	pthread_mutex_lock(&(coder->mutex));
	coder->last_compiled = get_time_ms();
	pthread_mutex_unlock(&(coder->mutex));
}