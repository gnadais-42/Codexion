#include "codexion.h"

static void heapify_up(t_heap *heap, int i);
static void	remove_request_by_id(t_heap *heap, int coder_id);

static void heapify_up(t_heap *heap, int i)
{
    int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (has_higher_priority(heap,
				heap->arr[parent],
				heap->arr[i]))
			break ;
		swap_request(&heap->arr[parent], &heap->arr[i]);
		i = parent;
	}
}

static void	remove_request_by_id(t_heap *heap, int coder_id)
{
	int	i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->arr[i].coder_id == coder_id)
			break ;
		i++;
	}
	if (i == heap->size)
		return ;
	heap->size--;
	heap->arr[i] = heap->arr[heap->size];
	heapify_up(heap, i);
	heapify_down(heap, i);
}

void    lock_remove_unlock(t_dongle *dongle, int coder_id)
{
    pthread_mutex_lock(&dongle->heap_mutex);
    remove_request_by_id(dongle->waitline, coder_id);
    pthread_mutex_unlock(&dongle->heap_mutex);
}

