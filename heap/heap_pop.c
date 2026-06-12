#include "../codexion.h"

static void heapify_down(t_heap_node *node, t_compare cmp);
static t_heap_node  *get_last_node(t_heap *heap);
static void place_last_in_first(t_heap *heap);

static void heapify_down(t_heap_node *node, t_compare cmp)
{
    t_heap_node *child;
    
    while (node->left)
    {
        child = node->left;
        if (node->right && cmp(node->right->request, child->request))
            child = node->right;
        if (cmp(child->request, node->request))
            swap_node_requests(node, child);
        else
            return ;
        node = child;
    }
}

static t_heap_node  *get_last_node(t_heap *heap)
{
    int         mask;
    int         index;
    t_heap_node *curr;

    index = heap->size;
    mask = get_mask(heap->size);
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
    if (heap->size == 2)
        last->left = NULL;
    if (heap->size == 3)
        last->right = NULL;
    if (last->left)
        last->left->parent = last;
    if (last->right)
        last->right->parent = last;

    heap->head = last;
}

t_request   heap_pop(t_heap *heap)
{
    t_request   r;
    t_heap_node *to_free;

    if (!heap->head)
        return ((t_request) {0,0,0});
    if (heap->size == 1)
    {
        r = heap->head->request;
        free(heap->head);
        heap->head = NULL;
        heap->size--;
        return (r);
    }
    
    to_free = heap->head;
    r = to_free->request;
    place_last_in_first(heap);
    heapify_down(heap->head, heap->compare);

    free(to_free);
    heap->size--;
    return (r);
}