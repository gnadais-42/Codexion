#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_data
{
	int	n_coders;
	int	t_burnout;
	int	t_compile;
	int	t_debug;
	int	t_refactor;
	int	n_compiles;
	int	d_cooldown;
	char	*schedule;
} t_data;

typedef struct s_coder
{
	int id;
	pthread_mutex_t *l_dongle;
	pthread_mutex_t *r_dongle;
	int n_compiled;
	t_data	*data;
} t_coder;

pthread_mutex_t	*create_dongles(int n);
void		destroy_dongles(pthread_mutex_t *dongles, int n);

t_coder		*create_coders(pthread_mutex_t *dongles, t_data *data, int n);
void		destroy_coders(t_coder *coders);
void		print_coder(t_coder coder);

t_data		*create_data(char *argv[]);
void		destroy_data(t_data *data);
void		print_data(t_data data);

int validator(int argc, char *argv[]);

#endif
