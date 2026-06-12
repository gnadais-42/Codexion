#include "../codexion.h"

static void free_node(t_heap_node *node);

t_heap  create_heap(t_compare cmp)
{
    t_heap  heap;

    heap.head = NULL;
    heap.size = 0;
    heap.compare = cmp;

    return (heap);
}

t_heap_node *new_node(t_request r)
{
    t_heap_node *node;

    node = malloc(sizeof(t_heap_node));
    if (!node)
        return (NULL);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->request = r;

    return (node);
}

static void free_node(t_heap_node *node)
{
    if (!node)
        return ;
    free_node(node->left);
    free_node(node->right);
    free(node);
}

void    destroy_heap(t_heap *heap)
{
    free_node(heap->head);

    heap->head = NULL;
    heap->size = 0;
}