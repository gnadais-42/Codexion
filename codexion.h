#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_sim t_sim;

typedef struct s_data
{
	int		n_coders;
	int		t_burnout;
	int		t_compile;
	int		t_debug;
	int		t_refactor;
	int		n_compiles;
	int		d_cooldown;
	char	*schedule;
} t_data;

typedef struct s_request
{
    int     coder_id;
	long    request_time;
	long    deadline;
} t_request;

typedef struct s_heap
{
    t_request  *arr;
    int         size;
    int         capacity;

	char		*schedule;
} t_heap;

typedef struct s_dongle
{
    pthread_mutex_t	mutex;
    pthread_cond_t	cond;
    long			available_at;
	int				occupied;

	t_heap			*waitline;
	pthread_mutex_t	heap_mutex;
} t_dongle;

typedef struct s_coder
{
	int 			id;
	t_dongle 		*l_dongle;
	t_dongle 		*r_dongle;
	int				n_compiled;
	pthread_mutex_t	compilation;
	long			last_compiled;
	pthread_mutex_t	state_mutex;

	t_sim			*sim_data;
} t_coder;

typedef struct s_sim
{
    t_data          data;
    t_coder         *coders;
    pthread_t       *threads;
    pthread_t       monitor;
    t_dongle        *dongles;
	int				thread_count;
	int				monitor_created;

    long            start_time;
    int             stopped;

    pthread_mutex_t stop_mutex;
    pthread_mutex_t print_mutex;
} t_sim;

t_heap		*create_heap(int n, char *schedule);
void		destroy_heap(t_heap *heap);
void		heap_push(t_heap *heap, t_request r);
t_request	heap_peek(t_heap *heap);
t_request	heap_pop(t_heap *heap);
int			is_first(t_heap *h, int id);


t_dongle	*create_dongles(int n, char *schedule);
void		destroy_dongles(t_dongle *dongles, int n);
void		request_dongles(t_coder *coder, t_sim *sim);
void		take_dongle(t_dongle *d, t_coder *c);
void 		release_dongle(t_dongle *d, t_sim *s);
int			dongle_available(t_dongle *d, t_coder *coder);
void		wait_dongle(t_dongle *d);
void		acquire_both(t_coder *c);

t_coder		*create_coders(t_dongle *dongles, int n, t_sim *sim);
void		destroy_coders(t_coder *coders, int n);
void		print_coder(t_coder coder);
long		last_compile(t_coder *coder);
void		set_last_compiled(t_coder *coder);
void    	increment_compilation(t_coder *coder);
int			get_n_compiled(t_coder *coder);


t_data		*create_data(char *argv[]);
void		destroy_data(t_data *data);
void		print_data(t_data data);

pthread_t	*create_threads(t_coder *coders, int n, void *(*routine)(void *), t_sim *sim);
void		join_threads(pthread_t *threads, int n);
void		destroy_threads(pthread_t *threads);

t_sim   *create_simulation(char *argv[]);
void	abort_simulation(t_sim *sim);
void	destroy_simulation(t_sim *sim);

int		validator(int argc, char *argv[]);

long	get_time_ms();
long	timestamp(t_sim *sim);
void	smart_sleep(t_sim *sim, long duration);

int		sim_stopped(t_sim *sim);
void    stop_simulation(t_sim *sim);
void	print_message(t_sim *sim, int coder_id, char *message);
void    lock_remove_unlock(t_dongle *dongle, int coder_id);


void    *routine(void *arg);
void    *monitor_routine(void *sim);
void    *null_func(void *arg);

void    compile(t_coder *c, t_sim *s);
void    debug(t_coder *c, t_sim *s);
void    refactor(t_coder *c, t_sim *s);

#endif
