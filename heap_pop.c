#include "codexion.h"

static int get_best_child(t_heap *heap, int i);

void swap_request(t_request *a, t_request *b)
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

void heapify_down(t_heap *heap, int i)
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