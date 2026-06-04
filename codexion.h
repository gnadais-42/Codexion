#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_sim;

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

typedef struct s_dongle
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    long available_at;
} t_dongle;

typedef struct s_coder
{
	int id;
	t_dongle *l_dongle;
	t_dongle *r_dongle;
	int		n_compiled;
	long	last_compiled;

	t_sim	*sim_data;
} t_coder;

typedef struct s_sim
{
    t_data          data;

    t_coder         *coders;
    pthread_t       *threads;
    pthread_t       monitor;

    t_dongle        *dongles;

    long            start_time;

    int             stopped;

    pthread_mutex_t stop_mutex;
    pthread_mutex_t print_mutex;

} t_sim;

t_dongle	*create_dongles(int n);
void		destroy_dongles(t_dongle *dongles, int n);

t_coder		*create_coders(t_dongle *dongles, int n);
void		destroy_coders(t_coder *coders);
void		print_coder(t_coder coder);

t_data		*create_data(char *argv[]);
void		destroy_data(t_data *data);
void		print_data(t_data data);

pthread_t	*create_threads(t_coder *coders, int n, void *(*routine)(void *));
void		join_threads(pthread_t *threads, int n);
void		destroy_threads(pthread_t *threads);

int validator(int argc, char *argv[]);

#endif
