#include "codexion.h"

static int has_higher_priority(t_heap *heap, t_request a, t_request b);
static void swap_request(t_request *a, t_request *b);
static int get_best_child(t_heap *heap, int i);
static void heapify_down(t_heap *heap, int i);

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

static int get_best_child(t_heap *heap, int i)
{
    int left;
    int right;
    int best;

    left = 2 * i + 1;
    right = 2 * i + 2;
    best = i;

    if (left < heap->size
        && !has_higher_priority(heap,
            heap->arr[best],
            heap->arr[left]))
        best = left;

    if (right < heap->size
        && !has_higher_priority(heap,
            heap->arr[best],
            heap->arr[right]))
        best = right;

    return (best);
}

static void heapify_down(t_heap *heap, int i)
{
    int best;

    while (1)
    {
        best = get_best_child(heap, i);

        if (best == i)
            break ;

        swap_request(&heap->arr[i], &heap->arr[best]);
        i = best;
    }
}

t_request heap_pop(t_heap *heap)
{
    t_request root;

    root = heap->arr[0];
    heap->size--;
    heap->arr[0] = heap->arr[heap->size];
    heapify_down(heap, 0);

    return (root);
}