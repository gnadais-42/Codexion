#include "codexion.h"

void    compile(t_coder *c, t_sim *s)
{
    request_dongles(c, s);

    if (sim_stopped(s))
        return;

    acquire_both(c);
    
    lock_remove_unlock(c->l_dongle, c->id);
    lock_remove_unlock(c->r_dongle, c->id);
    
    set_last_compiled(c);
    print_message(s, c->id, "is compiling");
    smart_sleep(s, s->data.t_compile);
    release_dongle(c->l_dongle, s);
    release_dongle(c->r_dongle, s);
    increment_compilation(c);
}

void    debug(t_coder *c, t_sim *s)
{
    if (sim_stopped(s))
        return ;

    print_message(s, c->id, "is debugging");
    smart_sleep(s, s->data.t_debug);
}

void    refactor(t_coder *c, t_sim *s)
{
    if (sim_stopped(s))
        return ;

    print_message(s, c->id, "is refactoring");
    smart_sleep(s, s->data.t_refactor);
}