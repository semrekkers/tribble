#ifndef TRIBBLE_SLICE_H_
#define TRIBBLE_SLICE_H_

#include "tribble.h"

typedef struct {
    byte *elem;
    uint isize;
    uint len;
    uint cap;
} Slice;

#define len(s) ((uint)(s)->len)
#define cap(s) ((uint)(s)->cap)

Slice _Slice_New(uint isize, void *data, uint start, uint end);
#define Slice_New(t,d,s,e) _Slice_New(sizeof(t),d,s,e)

void Slice_Free(Slice *s);

Slice Slice_Copy(Slice *s);
Error Slice_Append(Slice *s, void *elem, uint count);
Slice Slice_Join(Slice *s, Slice *other);
void* Slice_At(Slice *s, uint i);
void* Slice_Array(Slice *s);

#endif // TRIBBLE_SLICE_H_
