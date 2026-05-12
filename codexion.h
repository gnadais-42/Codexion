#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_coder
{
	int id;
	pthread_mutex_t *l_dongle;
	pthread_mutex_t *r_dongle;
} t_coder;

#endif
