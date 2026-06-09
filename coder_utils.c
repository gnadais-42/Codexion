#include "codexion.h"

void    increment_compilation(t_coder *coder)
{
    pthread_mutex_lock(&coder->compilation);
    coder->n_compiled++;
    pthread_mutex_unlock(&coder->compilation);
}

int	get_n_compiled(t_coder *coder)
{
	int	n;

	pthread_mutex_lock(&coder->compilation);
    n = coder->n_compiled;
    pthread_mutex_unlock(&coder->compilation);

	return (n);
}