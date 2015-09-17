#include "slice.h"

#define AT(s,i) (s->elem[(i) * s->isize])

// FIXME: some types must be uint64 here

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

Slice _Slice_New(uint isize, void *data, uint start, uint end) {
    Slice s = { .elem = nil };
    if (isize) {
        long int c = end - start;
        if (c >= 1) {
            if (!data) {
                s.elem = make(byte, c);
                if (s.elem) {
                    s.len = 0;
                    s.cap = c;
                }
            }
            else {
                s.elem = data + start;
                s.len = c;
                s.cap = c;
            }
        }
    }
    s.isize = isize;
    return s;
}

void Slice_Free(Slice *s) {
    if (s) {
        free(s->elem);
        s->elem = nil;
    }
}

Slice Slice_Copy(Slice *s) {
    Slice cpy = { .elem = nil };
    if (s && s->elem) {
        cpy = *s;
        uint t = cpy.cap * cpy.isize;
        cpy.elem = make(byte, t);
        if (cpy.elem) {
            memcpy(cpy.elem, s->elem, t);
        }
    }
    return cpy;
}

Error Slice_Append(Slice *s, void *elem, uint count) {
    if (!s || !elem) {
        return E_INVAL;
    }
    if (!s->elem) {
        return E_NOBUF;
    }
    expand(s, count);
    memcpy(AT(s,count), elem, (count * s->isize));
    return nil;
}

Slice Slice_Join(Slice *s, Slice *other) {
    Slice jnd = Slice_Copy(s);
    if (jnd.elem && other) {
        if (other->elem) {
            Slice_Append(&jnd, other->elem, other->len);
        }
    }
    return jnd;
}

void* Slice_At(Slice *s, uint i) {
    void *val = nil;
    if (s) {
        if (i < s->len) {
            val = AT(s, i);
        }
    }
    return val;
}

void* Slice_Array(Slice *s) {
    if (!s) {
        return nil;
    }
    return s->elem;
}
