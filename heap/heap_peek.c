#include "../codexion.h"

t_request   heap_peek(t_heap *heap)
{
    return (heap->head->request);
}