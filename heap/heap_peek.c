#include "../codexion.h"

t_request   heap_peek(t_heap *heap)
{
    if (heap->head)
        return (heap->head->request);
    else
        return ((t_request) {0,0,0});
}