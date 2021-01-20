#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "util_comparator.h"
#include "util_display.h"

#define endl puts("")
#define LEFT_CHILD 0
#define RIGHT_CHILD 1

typedef bool which_child;
/*
    STRING_SET initialize_set(STRING_SET,NULL,NULL);
    MODIFIED_STRING_SET initialize_set(STRING_SET,YourComparatorFunction,YourDisplayFunction);
    DEFAULT_SET is INTEGER SET
    DEFAULT_SET initialize_set(DEFAULT_SET,NULL,NULL);
*/
enum
{
    STRING_SET = -100,
    STRING_CASE_INSENSITIVE_SET,
    MODIFIED_STRING_SET,
    DEFAULT_SET,
    CHAR_SET,
    BYTE_SET,
    SHORT_SET,
    INT_SET,
    LONG_SET,
    FLOAT_SET,
    DOUBLE_SET,
    LONG_DOUBLE_SET,
    UNSIGNED_INT_SET,
    UNSIGNED_SHORT_SET,
    UNSIGNED_LONG_SET,
    LONG_LONG_SET,
    UNSIGNED_LONG_LONG_SET
};

enum
{
    SET_UNION = 3,
    SET_INTERSECTION,
    SET_DIFFERENCE
};

// Declaring Set structure;
typedef struct set_node
{
    void *data;
    struct set_node *ll;
    struct set_node *rl;
} set_node;

typedef set_node *Set_Node;


// Set Traversal Section JIT Stands for Just In Time
typedef struct JIT_Set_Stack_Elem
{
	Set_Node node;
	struct JIT_Set_Stack_Elem *next_link;
} JIT_Set_Stack_Elem;

typedef JIT_Set_Stack_Elem *JIT_Set_Iterator_Stack_Top;

typedef struct
{
	Set_Node next_iterator;
	JIT_Set_Iterator_Stack_Top jit_top;
} JIT_Set_Iterator;

typedef void *SetTraversalDataRef;
typedef set_node set_iterator;
// Set Traversal Section


typedef struct set
{
    size_t ESize;
    int ctr;
    long double (*compare)(const void *, const void *);
    void (*display)(const void *);
    Set_Node start;
    SetTraversalDataRef dataRef;
} set;

typedef set *pset;

typedef struct
{
    set (*getSet)(size_t size, long double (*compare)(const void *, const void *), void (*display)(const void *));

    bool (*addInSet)(pset obj, const void *data);

    void (*printSet)(const set obj);

    bool (*searchInSet)(const set obj, const void *data);

    bool (*deleteFromSet)(pset obj, void *key);

    set (*setUnion)(const set seta, const set setb, long *message);
    set (*setIntersection)(const set seta, const set setb, long *message);
    set (*setDifference)(const set seta, const set setb, long *message);

    bool (*getIterator)(pset obj, Set_Node iter);
    bool (*nextIterator)(pset obj, Set_Node iter);

    void (*destroySet)(pset obj, void (*addOnsClean)(const void *));
    void (*clearSet)(pset obj, void (*addOnsClean)(const void *));
} GLOBAL_SET_OBJECT;

// Iterator Implementation is Remaining Please work on it
