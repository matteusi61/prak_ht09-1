#include "random_source.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

RandomSource *
destroy_random(RandomSource *src)
{
    free(src->ops);
    close(src->fd);
    free(src);
    return NULL;
}

double
next_random(RandomSource *src)
{
    if (read(src->fd, &(src->current), sizeof(src->current)) != sizeof(src->current)) {
        fprintf(stderr, "next_random: Syscall read error\n");
        exit(1);
    }
    return ((double) (src->current - (src->current == ~0ull)) / ~0ull);
}

RandomSource *
random_random_factory(const char params)
{
    RandomSource *container = calloc(1, sizeof(*container));
    RandomSourceOperations *operations = calloc(1, sizeof(*operations));
    operations->destroy = destroy_random;
    operations->next = next_random;
    container->fd = open("/dev/urandom", O_RDONLY);
    if (!container->fd) {
        fprintf(stderr, "random_random_factory: Syscall open error\n");
        exit(1);
    }
    container->ops = (RandomSourceOperations *) operations;
    return container;
}
