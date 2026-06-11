#include "../codexion.h"

static void heapify_down(t_heap_node *node, int (*cmp)(t_request, t_request))
{
    t_heap_node *child; // AQUI FALTA TER A CERTEZA QUE ESCOLHE O CHILD CORRETO
    while (node->left || node->right) // NÃO É SÓ QUALQUER UM MENOR, TEM QUE SER O MENOR DOS DOIS
    {
        if (node->left && cmp(node->left->request, node->request))
            child = node->left;
        else if (node->right && cmp(node->right->request, node->request))
            child = node->right;
        else
            return ;
        swap_node_requests(node, child);
        node = child;
    }
}

static t_heap_node  *get_last_node(t_heap *heap)
{
    int         mask;
    int         index;
    t_heap_node *curr;

    index = heap->size;
    mask = get_mask(heap, heap->size);
    curr = heap->head;
    while (mask > 0)
    {
        if (mask & index)
            curr = curr->right;
        else
            curr = curr->left;
        mask >>= 1;
    }
    return (curr);
}

static void place_last_in_first(t_heap *heap)
{
    t_heap_node *last;

    last = get_last_node(heap);
    if (last->parent->left == last)
        last->parent->left = NULL;
    else
        last->parent->right = NULL;
    
    last->parent = NULL;
    last->left = heap->head->left;
    last->right = heap->head->right;
    last->left->parent = last;
    last->right->parent = last;

    heap->head = last;
}

t_request   heap_pop(t_heap *heap)
{
    t_request   r;
    t_heap_node *to_free;
    t_heap_node *last;

    if (!heap->head)
        return ((t_request) {0,0,0});
    if (heap->size == 1) // FALTA DAR HANDLE DOS CASOS QUANDO SIZE É 2 OU 3 SENÃO CRIAS LOOPS
    {
        r = heap->head->request;
        free(heap->head);
        heap->head = NULL;
        heap->size++;
        return (r);
    }
    
    to_free = heap->head;
    r = to_free->request;
    place_last_in_first(heap);
    heapify_down(heap->head, heap->compare);

    free(to_free);
    heap->size++;
    return (r);
}