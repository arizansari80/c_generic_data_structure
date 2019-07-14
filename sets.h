#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define endl puts("")

// Declaring Set structure;
typedef struct set_node
{
    void * data;
    struct set_node *ll;
    struct set_node *rl;
} set_node;

typedef set_node * Set_Node;

typedef struct set
{
    size_t ESize;
    int ctr;
    float (*compare)(const void *,const void *);
    void (*display)(const void *);
    Set_Node start;


    // Member Function
    bool (*InsertInSet)(struct set **obj,const void *data);
    void (*PrintSet)(struct set *start);
    bool (*SearchSet)(const struct set *obj,const void *data);
    bool (*DeleteInSet)(struct set **in,void *key);
    void (*SetUnion)(struct set **to,const struct set *from);
    void (*SetIntersection)(struct set **to,const struct set *from);
    void (*SetDifference)(struct set **source,const struct set *from);
} set;

typedef set * Set;



void initialize_set(Set *obj,size_t size,float (*compare)(const void *,const void *),void (*display)(const void *)){
    *obj=(Set)malloc(sizeof(set));
    (*obj)->ESize=size;
    (*obj)->ctr=0;
    (*obj)->compare=compare;
    (*obj)->display=display;
    (*obj)->start=NULL;


    // Initializing Member Function
    (*obj)->InsertInSet = add_in_set;
    (*obj)->PrintSet = print_set;
    (*obj)->SearchSet = search_set;
    (*obj)->DeleteInSet = delete_in_set;
    (*obj)->SetUnion = set_union;
    (*obj)->SetIntersection = set_intersection;
    (*obj)->SetDifference = set_difference;
}


// Adding Unique Element in Set;
bool add_in_set(Set *obj,const void *data);

// Traversing Set Data Structure;
void print_set(Set start);

// Returning Set as an Array

// Search Operation in Set
bool search_set(const Set obj,const void *data);

// Delete In Sets This Operation is Most Complicated One
bool delete_in_set(Set *in,void *key);

// Union Operation
void set_union(Set *to,const Set from);

// Intersection Operation
void set_intersection(Set *to,const Set from);

// Set Difference
void set_difference(Set *source,const Set from);
