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

t_heap      create_heap(int (*cmp)(t_request, t_request));
void        destroy_heap(t_heap *heap);
t_heap_node *new_node(t_request r);
void        print_heap(t_heap *heap);
void        swap_node_requests(t_heap_node *parent, t_heap_node *child);
int         get_mask(t_heap *heap, int index);
t_request   heap_peek(t_heap *heap);
int         heap_insert(t_heap *heap, t_request r);




int compare_fifo(t_request a, t_request b);
int compare_edf(t_request a, t_request b);


#endif