#include "../codexion.h"

t_compare   get_compare(t_schedule sch)
{
    if (sch == FIFO)
        return compare_fifo;
    else
        return compare_edf;
}

int compare_fifo(t_request a, t_request b)
{
    if (a.time_of_creation < b.time_of_creation)
        return (1);
    else
        return (0);
}

int compare_edf(t_request a, t_request b)
{
    if (a.deadline < b.deadline)
        return (1);
    else if (a.deadline > b.deadline)
        return (0);
    else
        return (compare_fifo(a, b));
}