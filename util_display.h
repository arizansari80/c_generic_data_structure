#ifndef UTIL_DISPLAY_H_INCLUDED
#define UTIL_DISPLAY_H_INCLUDED
#include <stdio.h>

#include "util_def.h"

void char_display(const void *ch1);
void int_display(const void *ch1);
void long_display(const void *ch1);
void float_display(const void *ch1);
void double_display(const void *ch1);
void long_double_display(const void *ch1);
void unsigned_int_display(const void *ch1);
void unsigned_long_display(const void *ch1);
void long_long_display(const void *ch1);
void unsigned_long_long_display(const void *ch1);
void string_display(const void *ch1);

#endif // UTIL_DISPLAY_H_INCLUDED
