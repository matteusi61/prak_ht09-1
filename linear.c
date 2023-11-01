#include "random_source.h"
#include <stdlib.h>
#include <stdio.h>

RandomSource *
destroy_linear(RandomSource *src)
{
    free(src->ops);
    free(src);
    return NULL;
}

double
next_linear(RandomSource *src)
{
    src->current = (src->current * src->multi + src->inc) % src->mod;
    return ((double) (src->current) / src->mod);
}

RandomSource *
random_linear_factory(const char *params)
{
    unsigned long long seed = strtoull(params, NULL, 10);
    RandomSource *container = calloc(1, sizeof(*container));
    RandomSourceOperations *operations = calloc(1, sizeof(*operations));
    operations->destroy = destroy_linear;
    operations->next = next_linear;
    container->current = seed & (~(1u << 31));
    container->inc = 12345;
    container->multi = 1103515245;
    container->mod = 1 << 31;
    container->ops = (RandomSourceOperations *) operations;
    return container;
}
