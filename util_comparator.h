#ifndef UTIL_COMPARATOR_H_INCLUDED
#define UTIL_COMPARATOR_H_INCLUDED
#include <string.h>

#include "util_def.h"

long double byte_comparator(const void *ch1, const void *ch2);
long double char_comparator(const void *ch1, const void *ch2);
long double int_comparator(const void *ch1, const void *ch2);
long double short_comparator(const void *ch1, const void *ch2);
long double long_comparator(const void *ch1, const void *ch2);
long double float_comparator(const void *ch1, const void *ch2);
long double double_comparator(const void *ch1, const void *ch2);
long double unsigned_short_comparator(const void *ch1, const void *ch2);
long double unsigned_int_comparator(const void *ch1, const void *ch2);
long double unsigned_long_comparator(const void *ch1, const void *ch2);
long double long_double_comparator(const void *ch1, const void *ch2);
long double string_comparator(const void *ch1, const void *ch2);
long double string_case_insensitive_comparator(const void *ch1, const void *ch2);
long double long_long_comparator(const void *ch1, const void *ch2);
long double unsigned_long_long_comparator(const void *ch1, const void *ch2);

#endif // UTIL_COMPARATOR_H_INCLUDED
