#include "slice.h"

#define AT(s,i) (s->elem[(i) * s->isize])

static inline void expand(Slice *s, uint need) {
    uint ntotal = s->len + need;
    if (ntotal > s->cap) {
        uint n = s->cap;
        do {
            n <<= 1;
        } while (ntotal > n);
        uint nbytes = n * s->isize;
        byte *nptr = realloc(s->elem, nbytes);
        if (!nptr) {
            panic(E_NOMEM);
        }
        s->elem = nptr;
        s->cap = n;
    }
}
