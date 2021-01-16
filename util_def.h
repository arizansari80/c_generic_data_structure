#ifndef UTIL_DEF_H_INCLUDED
#define UTIL_DEF_H_INCLUDED

#define BYTEAT(ptr) (*(byte *)ptr)
#define CHARAT(ptr) (*(char *)ptr)
#define INTAT(ptr)  (*(int *)ptr)
#define SHORTAT(ptr)    (*(short *)ptr)
#define LONGAT(ptr) (*(long *)ptr)
#define FLOATAT(ptr)    (*(float *)ptr)
#define DOUBLEAT(ptr)   (*(double *)ptr)
#define UNSIGNEDSHORTAT(ptr)    (*(unsigned short *)ptr)
#define UNSIGNEDINTAT(ptr)  (*(unsigned int *)ptr)
#define UNSIGNEDLONGAT(ptr) (*(unsigned long *)ptr)
#define LONGDOUBLEAT(ptr)   (*(long double *)ptr)
#define LONGLONGAT(ptr) (*(long long *)ptr)
#define UNSIGNEDLONGLONGAT(ptr) (*(unsigned long long *)ptr)
#define STRINGAT(ptr)   ((char *)ptr)

#define MAX_STR_SIZE 4096
#define SPACE_CHAR 32
#define NULL_CHAR 0

typedef unsigned char byte;

typedef char * string;

#endif // UTIL_DEF_H_INCLUDED
