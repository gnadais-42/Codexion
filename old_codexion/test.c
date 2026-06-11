#include "codexion.h"

void    smart_sleep_test(long duration);

void    *test_routine(void *c)
{
    long start;

    start = get_time_ms();

    for(int i = 0; i < 1000; i++)
    {
        printf("%d: %ld\n", 1, get_time_ms() - start);
        smart_sleep_test(500);
    }
    return (NULL);
}

void    smart_sleep_test(long duration)
{
    long    start_time;

    start_time = get_time_ms();
    while (1)
    {
        if (get_time_ms() - start_time >= duration)
            return ;
        usleep(1000);
    }
}

int main()
{
    t_coder *coder = malloc(sizeof(t_coder));
    pthread_t   thr;

    memset(coder, 0, sizeof(t_coder));
    coder->id = 1;
    pthread_create(&(thr), NULL, test_routine, coder);
    pthread_join(thr, NULL);
}