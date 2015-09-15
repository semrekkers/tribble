#ifndef TRIBBLE_H_
#define TRIBBLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;
typedef byte bool;
typedef unsigned int uint;

#define true  (1)
#define false (0)

#define nil ((void*)0)

typedef char *Error;

void _log(const char *f, const uint l, Error err);
void _panic(const char *f, const uint l, Error err);

#ifdef USE_LOG
#define log(e) _log(__FILE__,__LINE__,(e))
#else
#define log(e)
#endif

#ifdef DEBUG
#define check(c) if (!(c)) {_panic(__FILE__,__LINE__,"check failed: "#c);}
#else
#define check(c)
#endif

#define make(t, c) malloc(sizeof(t) * (c))

#endif // TRIBBLE_H_
