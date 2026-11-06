#include <cmdline.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    const char* const key;
    const mma_t       algo;
} _cmdline_algo_entry_t;

static const _cmdline_algo_entry_t _CMDLINE_ALGO_MAP[NUM_MMAS] = {
    { "naive-ijk", MMA_NAIVE_IJK, },
    { "naive-ikj", MMA_NAIVE_IKJ, },
    { "naive-jik", MMA_NAIVE_JIK, },
    { "naive-jki", MMA_NAIVE_JKI, },
    { "naive-kij", MMA_NAIVE_KIJ, },
    { "naive-kji", MMA_NAIVE_KJI, },
};

static mma_t _get_algo_by_key(const char* const key)
{
    for (int i = 0; i < NUM_MMAS; i++) {
        if (strcmp(_CMDLINE_ALGO_MAP[i].key, key) == 0) {
            return _CMDLINE_ALGO_MAP[i].algo;
        }
    }

    return MMA_INVALID;
}

char* cmdline_get_args(
    const int argc,
    const char* const argv[],
    cmdline_args_t* const args
)
{
    // TODO: Add more specific error/help messages
    // TODO: Add default arguments
    if (argc != 5)
        return "Invalid argument count.";

    // get algorithm
    const mma_t algo = _get_algo_by_key(argv[1]);

    if (algo == MMA_INVALID)
        return "Invalid algorithm.";

    // get matrix size
    mat_size_t size;
    if (sscanf(argv[2], "%hu", &size) != 1 || size == 0)
        return "Invalid size.";

    // get number of threads
    unsigned short num_multiplications;
    if (
        sscanf(argv[3], "%hu", &num_multiplications) != 1
        || num_multiplications == 0
    )
        return "Invalid number of operations.";
    
    // get number of threads
    unsigned short num_threads;
    if (sscanf(argv[3], "%hu", &num_threads) != 1 || num_threads == 0)
        return "Invalid number of threads.";

    // return args
    args->mat_size            = size;
    args->mult_algo           = algo;
    args->num_multiplications = num_multiplications;
    args->num_threads         = num_threads;
    return NULL;
}
