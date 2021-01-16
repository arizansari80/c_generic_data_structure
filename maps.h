#ifndef MAPS_H_INCLUDED
#define MAPS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "util_comparator.h"

#define endl puts("")
#define LEFT_CHILD 0
#define RIGHT_CHILD 1

typedef bool which_child;

enum
{
    STRING_KEY = -100,
    STRING_CASE_INSENSITIVE_KEY,
    MODIFIED_STRING_KEY,
    DEFAULT_KEY,
    CHAR_KEY,
    BYTE_KEY,
    SHORT_KEY,
    INT_KEY,
    LONG_KEY,
    FLOAT_KEY,
    DOUBLE_KEY,
    LONG_DOUBLE_KEY,
    UNSIGNED_INT_KEY,
    UNSIGNED_SHORT_KEY,
    UNSIGNED_LONG_KEY,
    LONG_LONG_KEY,
    UNSIGNED_LONG_LONG_KEY
};

enum
{
    STRING_VALUE = -100,
    STRING_CASE_INSENSITIVE_VALUE,
    MODIFIED_STRING_VALUE,
    DEFAULT_VALUE,
    CHAR_VALUE,
    BYTE_VALUE,
    SHORT_VALUE,
    INT_VALUE,
    LONG_VALUE,
    FLOAT_VALUE,
    DOUBLE_VALUE,
    LONG_DOUBLE_VALUE,
    UNSIGNED_INT_VALUE,
    UNSIGNED_SHORT_VALUE,
    UNSIGNED_LONG_VALUE,
    LONG_LONG_VALUE,
    UNSIGNED_LONG_LONG_VALUE
};

typedef struct private_map_data_for_library
{
    void *key;
    void *value;
} private_map_data_for_library;

typedef struct map_node
{
    private_map_data_for_library *data;
    struct map_node *ll;
    struct map_node *rl;
} map_node;

typedef map_node *Map_Node;


// Map Traversal Section JIT Stands for Just In Time
typedef struct JIT_Map_Stack_Elem
{
	Map_Node node;
	struct JIT_Map_Stack_Elem *next_link;
} JIT_Map_Stack_Elem;

typedef JIT_Map_Stack_Elem *JIT_Map_Iterator_Stack_Top;

typedef struct
{
	Map_Node next_iterator;
	JIT_Map_Iterator_Stack_Top jit_top;
} JIT_Map_Iterator;

typedef void *MapTraversalDataRef;
typedef map_node map_iterator;
// Map Traversal Section


typedef struct map
{
    size_t key_size;
    size_t value_size;
    int ctr;
    long double (*key_compare)(const void *, const void *);
    long double (*value_compare)(const void *, const void *);
    void (*display)(const void *,const void *);
    Map_Node start;
    MapTraversalDataRef dataRef;
} map;

typedef map *pmap;

typedef struct
{
    map (*getMap)(size_t key_size, size_t value_size, long double (*key_compare)(const void *, const void *), long double (*value_compare)(const void *, const void *), void (*display)(const void *,const void *));

    bool (*addInMap)(pmap obj, const void *data,const void *value);

    void (*printMap)(const map obj);

    void *(*getValue)(const map obj, const void *key);
    bool (*containsValue)(const map obj, const void *value);
    bool (*containsKey)(const map obj, const void *key);
    bool (*containsKeyWithValue)(const map obj, const void *key, const void *value);

    bool (*removeKeyFromMap)(pmap obj, const void *key);
	bool (*removeKeyWithValueFromMap)(pmap obj, const void *key, const void *value);

    bool (*getIterator)(pmap obj, Map_Node iter);
    bool (*nextIterator)(pmap obj, Map_Node iter);

    void (*destroyMap)(pmap obj);
    void (*clearMap)(pmap obj);

    bool (*replaceValueOfKey)(pmap obj, const void *key, const void *value);
    bool (*replaceOldValueOfKeyWithNewValue)(pmap obj, const void *key, const void *old_value, const void *new_value);
} GLOBAL_MAP_OBJECT;

#endif // MAPS_H_INCLUDED
