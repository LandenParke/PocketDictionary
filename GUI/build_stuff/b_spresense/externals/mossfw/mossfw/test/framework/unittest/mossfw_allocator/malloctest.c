#undef malloc
#include <stdlib.h>
#include "malloctest.h"

int mallocerr = -1;

void *malloctest(size_t size)
{
    void *ret = mallocerr == 0 ? NULL : malloc(size);
    mallocerr = mallocerr - (mallocerr < 0 ? 0 : 1);
    return ret;
}
