#include "tld.h"

#include "particle_struct.h"

#define PARTICLE_ALLOC_IMPORT
#include "particle_alloc.h"

int p_list_alloc(p_list **list, int size)
{
        p_list* l = NULL;

        MMALLOC(l, sizeof(p_list));
        l->n_alloc = size;
        l->n = 0;
        l->particles = NULL;
        MMALLOC(l->particles, sizeof(particle) * l->n_alloc);
        *list = l;
        return OK;
ERROR:
        p_list_free(l);
        return FAIL;
}

void p_list_free(p_list *l)
{
        if(l){
                MFREE(l->particles);
                MFREE(l);
        }
}
