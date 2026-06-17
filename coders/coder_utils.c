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

void	increment_compilation(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->times_compiled++;
	pthread_mutex_unlock(&coder->mutex);
}

int		get_n_compilation(t_coder *coder)
{
	int	n;

	pthread_mutex_lock(&coder->mutex);
	n = coder->times_compiled;
	pthread_mutex_unlock(&coder->mutex);

	return (n);
}

void	print_times_compiled(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
    printf("coder %d: %d\n", coder->id, coder->times_compiled);
	pthread_mutex_unlock(&coder->mutex);
}