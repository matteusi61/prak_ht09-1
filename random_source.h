typedef struct RandomSource
{
    unsigned long long current;
    unsigned inc;
    unsigned mod;
    unsigned multi;
    int fd;
    void *ops;
} RandomSource;

typedef struct RandomSourceOperations
{
    RandomSource *(*destroy)(RandomSource *src);
    double (*next)(RandomSource *src);
} RandomSourceOperations;
