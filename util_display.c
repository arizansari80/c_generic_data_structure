#include "util_display.h"
#include "util_comparator.h"

void char_display(const void *ch1)
{
    printf("%c",CHARAT(ch1));
}

void int_display(const void *ch1)
{
    printf("%d",INTAT(ch1));
}

void long_display(const void *ch1)
{
    printf("%ld",LONGAT(ch1));
}

void float_display(const void *ch1)
{
    printf("%f",FLOATAT(ch1));
}

void double_display(const void *ch1)
{
    printf("%f",DOUBLEAT(ch1));
}

void long_double_display(const void *ch1)
{
    printf("%f",LONGDOUBLEAT(ch1));
}

void unsigned_int_display(const void *ch1)
{
    printf("%u",UNSIGNEDINTAT(ch1));
}

void unsigned_long_display(const void *ch1)
{
    printf("%lu",UNSIGNEDLONGAT(ch1));
}

void string_display(const void *ch1)
{
    printf("%s",(char *)ch1);
}

void long_long_display(const void *ch1)
{
    printf("%lld",LONGLONGAT(ch1));
}

void unsigned_long_long_display(const void *ch1)
{
    printf("%llu",UNSIGNEDLONGLONGAT(ch1));
}
