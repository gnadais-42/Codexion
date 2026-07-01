#ifndef CODEXION_H
# define CODEXION_H

# include "struct.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

int validator(int argc, char *argv[]);

t_data	create_data(char *argv[]);
void print_data(t_data data);

t_heap      create_heap(t_compare cmp);
void        destroy_heap(t_heap *heap);
t_heap_node *new_node(t_request r);
void        print_heap(t_heap *heap);
void        swap_node_requests(t_heap_node *parent, t_heap_node *child);
int         get_mask(int index);
t_request   heap_peek(t_heap *heap);
int         heap_insert(t_heap *heap, t_request r);
t_request   heap_pop(t_heap *heap);
t_compare   get_compare(t_schedule sch);

t_dongle	*create_dongles(int n, t_schedule sch);
void	    destroy_dongles(t_dongle *dongles, int n);
int         create_requests(t_coder *coder);
int         acquire_dongles(t_coder *coder);
void        release_dongles(t_coder *coder);
void        set_last_used(t_dongle *dongle);


t_coder	*create_coders(t_dongle *dongles, int n, t_sim *sim);
void	destroy_coders(t_coder *coders, int n);
long	get_last_compiled(t_coder *coder);
void	set_last_compiled(t_coder *coder);
void	increment_compilation(t_coder *coder);
int		get_n_compilation(t_coder *coder);
void	print_times_compiled(t_coder *coder);


t_sim   *create_simulation(char *argv[]);
void    destroy_simulation(t_sim *sim);
int     start_simulation(t_sim *sim);
void    stop_simulation(t_sim *sim);
int     sim_stopped(t_sim *sim);
void    print_message(t_sim *sim, t_coder *coder, char *message);

int compare_fifo(t_request a, t_request b);
int compare_edf(t_request a, t_request b);

void    *coder_routine(void *coder);
void    *monitor_routine(void *sim);

long    get_time_ms();
long    timestamp(t_sim *sim);
void    smart_sleep(t_sim * sim, long duration);
void    cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex, long time);

int compile(t_coder *coder);
int debug(t_coder *coder);
int refactor(t_coder *coder);

#endif