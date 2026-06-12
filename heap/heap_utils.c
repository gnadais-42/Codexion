#include "../codexion.h"

void    swap_node_requests(t_heap_node *a, t_heap_node *b)
{
    t_request   tmp;

    tmp = a->request;
    a->request = b->request;
    b->request = tmp;
}

int  get_mask(int index)
{
    int mask;

    mask = 1;
    while (mask <= index)
        mask <<= 1;
    return (mask >> 2);
}


void    print_heap(t_heap *heap)
{
    t_heap_node *curr;
    int i;
    int index;
    int mask;

    i = 0;
    while (i < heap->size)
    {
        index = i + 1;
        mask = 1;
        while (mask <= index)
            mask <<= 1;
        mask >>= 2;
        curr = heap->head;
        while (mask > 0)
        {
            if (mask & index)
                curr = curr->right;
            else
                curr = curr->left;
            mask >>= 1;
        }
        printf("| %d: %ld\n", i, curr->request.deadline);
        i++;
    }
}