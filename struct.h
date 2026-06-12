#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>

typedef struct s_sim t_sim;
typedef struct s_request t_request;
typedef int (*t_compare)(t_request, t_request);

typedef enum s_schedule
{
    FIFO,
    EDF
} t_schedule;

typedef struct s_request
{
    int     coder_id;
    long    deadline;
    long    time_of_creation;
} t_request;

typedef struct s_heap_node
{
    t_request           request;
    struct s_heap_node  *left;
    struct s_heap_node  *right;
    struct s_heap_node     *parent;
} t_heap_node;

typedef struct s_heap
{
    t_heap_node *head;
    int         size;
    t_compare   compare;
} t_heap;

typedef struct s_data
{
	int 		n_coders;
	int 		t_burnout;
	int 		t_compile;
	int 		t_debug;
	int		    t_refactor;
	int		    n_compiles;
	int		    d_cooldown;
	t_schedule  schedule;
} t_data;

typedef struct s_dongle
{
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    int             available;
    long            last_used;
    t_heap          heap;
} t_dongle;

typedef struct s_coder
{
    int             id;
    t_dongle        *left;
    t_dongle        *right;
    pthread_mutex_t mutex;
    pthread_t       thread;
    int             times_compiled;
    long            last_compiled;
    t_sim           *sim;
} t_coder;

typedef struct s_sim
{
    t_coder         *coders;
    t_dongle        *dongles;
    t_data          data;
    pthread_mutex_t print_mutex;
    pthread_mutex_t stop_mutex;
    pthread_t       monitor;

    int             stopped;
    long            start_time;
    int             thread_count;
    int             monitor_created;
} t_sim;

#endif