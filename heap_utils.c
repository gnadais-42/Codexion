#include "codexion.h"

static int has_higher_priority(t_heap *heap, t_request a, t_request b);
static void swap_request(t_request *a, t_request *b);

static int has_higher_priority(t_heap *heap, t_request a, t_request b)
{
    if (strcmp(heap->schedule, "fifo") == 0) 
        return (a.request_time < b.request_time); // FIFO, priority given to who asks for it first

    if (a.deadline != b.deadline)
        return (a.deadline < b.deadline); // EDF, priority is by deadline

    return (a.request_time < b.request_time); // Tie-breaker in case two coders have the same deadline
}

static void swap_request(t_request *a, t_request *b)
{
    t_request tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void heap_push(t_heap *heap, t_request r)
{
    int i;
    int parent;

    if (!heap || heap->size >= heap->capacity)
        return;
    i = heap->size;
    heap->arr[i] = r;
    heap->size++;
    while (i > 0)
    {
        parent = (i - 1) / 2;
        if (has_higher_priority(heap,
                heap->arr[parent],
                heap->arr[i]))
            break;
        swap_request(&heap->arr[parent], &heap->arr[i]);
        i = parent;
    }
}

t_request   heap_peek(t_heap *heap)
{
    return heap->arr[0];
}

int is_first(t_heap *h, int id)
{
    if (h->size == 0)
        return (0);
    return (h->arr[0].coder_id == id);
}