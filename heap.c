#include "codexion.h"

t_heap  *create_heap(int n, char *schedule)
{
    t_request   *requests;
    t_heap      *heap;

    requests = malloc(sizeof(t_request) * n);
    if (!requests)
        return (NULL);
    memset(requests, 0, sizeof(t_request) * n);
    heap = malloc(sizeof(t_heap));
    if (!heap)
    {
        free(requests);
        return (NULL);
    }
    heap->arr = requests;
    heap->capacity = n;
    heap->size = 0;
    heap->schedule = schedule;

    return (heap);
}

void    destroy_heap(t_heap *heap)
{
    if (!heap)
        return;
    
    free(heap->arr);
    free(heap);
}
