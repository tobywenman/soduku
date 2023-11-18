#include <inttypes.h>
#include <stddef.h>

struct grid
{
    uint8_t data[9][9];
};

struct solveStack
{
    struct grid *data;
    size_t size;
};
