#include "util_comparator.h"

long double byte_comparator(const void *ch1, const void *ch2)
{
    return BYTEAT(ch1) - BYTEAT(ch2);
}

long double char_comparator(const void *ch1, const void *ch2)
{
    return CHARAT(ch1) - CHARAT(ch2);
}

long double int_comparator(const void *ch1, const void *ch2)
{
    return INTAT(ch1) - INTAT(ch2);
}

long double short_comparator(const void *ch1, const void *ch2)
{
    return SHORTAT(ch1) - SHORTAT(ch2);
}

long double long_comparator(const void *ch1, const void *ch2)
{
    return LONGAT(ch1) - LONGAT(ch2);
}

long double float_comparator(const void *ch1, const void *ch2)
{
    return FLOATAT(ch1) - FLOATAT(ch2);
}

long double double_comparator(const void *ch1, const void *ch2)
{
    return DOUBLEAT(ch1) - DOUBLEAT(ch2);
}

long double unsigned_short_comparator(const void *ch1, const void *ch2)
{
    return UNSIGNEDSHORTAT(ch1) - UNSIGNEDSHORTAT(ch2);
}

long double unsigned_int_comparator(const void *ch1, const void *ch2)
{
    return UNSIGNEDINTAT(ch1) - UNSIGNEDINTAT(ch2);
}

long double unsigned_long_comparator(const void *ch1, const void *ch2)
{
    return UNSIGNEDLONGAT(ch1) - UNSIGNEDLONGAT(ch2);
}

long double long_double_comparator(const void *ch1, const void *ch2)
{
    return LONGDOUBLEAT(ch1) - LONGDOUBLEAT(ch2);
}

long double long_long_comparator(const void *ch1, const void *ch2)
{
    return LONGLONGAT(ch1) - LONGLONGAT(ch2);
}

long double unsigned_long_long_comparator(const void *ch1, const void *ch2)
{
    return UNSIGNEDLONGLONGAT(ch1) - UNSIGNEDLONGLONGAT(ch2);
}

long double string_case_insensitive_comparator(const void *ch1, const void *ch2)
{
    return strcmp(ch1,ch2);
}

long double string_comparator(const void *ch1, const void *ch2)
{
    #ifdef _WIN32
	    return stricmp(ch1,ch2);
	#else
	    return strcasecmp(ch1,ch2);
    #endif
}
