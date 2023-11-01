#include "random_source.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    void *handle = dlopen(NULL, RTLD_LAZY);

    long n = strtol(argv[2], NULL, 10);
    if (n < 0 || n > 100000) {
        fprintf(stderr, "main: Wrong argument\n");
        return 1;
    }

    RandomSource *random;
    RandomSource *(*random_factory)(const char *params);

    if (!strcmp(argv[1], "linear")) {
        random_factory = dlsym(handle, "random_linear_factory");
    } else if (!strcmp(argv[1], "random")) {
        random_factory = dlsym(handle, "random_random_factory");
    } else {
        fprintf(stderr, "main: Wrong argument\n");
        return 1;
    }

    random = random_factory(argv[3]);

    for (int i = 0; i < n; ++i) {
        printf("%.10g\n", ((RandomSourceOperations *) random->ops)->next(random));
    }

    random = ((RandomSourceOperations *) random->ops)->destroy(random);

    return 0;
}
