#include "../codexion.h"

int compile(t_coder *coder)
{
    long    time;

    if (create_requests(coder) == 0)
        return (0);
    
    return (1);
}

/*
Faz as funções de acquire dongle
Figure out como se vais fazer o coder fazer stop_simulation quando
o create_requests falha ou se fazes o monitor fazer isso.
*/