#include <inttypes.h>
#include <stddef.h>

struct grid
{
    uint8_t data[9][9];
    uint8_t x,y,nextTest;
};

struct solveStack
{
    struct grid *data;
    size_t size;
    size_t top;
};
