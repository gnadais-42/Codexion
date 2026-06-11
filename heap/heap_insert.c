#include "../codexion.h"

static void heapify_up(t_heap *heap, t_heap_node *node, int (*cmp)(t_request, t_request));
static void place_node(t_heap_node *parent, t_heap_node *node);
static int  insert_at_beginning(t_heap *heap, t_heap_node *node);

static void heapify_up(t_heap *heap, t_heap_node *node, int (*cmp)(t_request, t_request))
{
    t_request tmp;

    while (node->parent && cmp(node->request, node->parent->request))
    {
        swap_node_requests(node->parent, node);
        node = node->parent;
    }
}

static void place_node(t_heap_node *parent, t_heap_node *node)
{
    if (!parent->left)
        parent->left = node;
    else
        parent->right = node;
    
    node->parent = parent;
}

static int  insert_at_beginning(t_heap *heap, t_heap_node *node)
{
    if (heap->size == 0)
    {
        heap->head = node;
        heap->size++;
        return (1);
    }
    return (0);
}

int heap_insert(t_heap *heap, t_request r)
{
    t_heap_node *node;
    t_heap_node *curr;
    int         mask;

    node = new_node(r);
    if (!node)
        return (0);
    if (insert_at_beginning(heap, node))
        return (1);
    curr = heap->head;
    mask = get_mask(heap, heap->size + 1);
    while (mask > 1)
    {
        if (mask & (heap->size + 1))
            curr = curr->right;
        else
            curr = curr->left;
        mask >>= 1;
    }
    place_node(curr, node);
    heapify_up(heap, node, heap->compare);
    heap->size++;
    return (1);
}

/* int main()
{
    t_heap heap = create_heap(compare_edf);
    t_request r1 = {0, 1, 2};
    t_request r2 = {0, 6, 3};
    t_request r3 = {0, 7, 3};

    heap_insert(&heap, r3);
    heap_insert(&heap, r2);
    heap_insert(&heap, r1);
    heap_insert(&heap, (t_request) {0, 10, 4});
    heap_insert(&heap, (t_request) {0, 1, 1});
    heap_insert(&heap, (t_request) {0, 20, 1});
    heap_insert(&heap, (t_request) {0, 5, 1});
    heap_insert(&heap, (t_request) {0, 3, 1});
    heap_insert(&heap, (t_request) {0, 4, 1});
    heap_insert(&heap, (t_request) {0, 9, 1});
    heap_insert(&heap, (t_request) {0, 10, 1});

    print_heap(&heap);
} */