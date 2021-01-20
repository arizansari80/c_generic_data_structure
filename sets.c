#include "sets.h"
static char *set_operation_message[] = {"Comparator of Set1 and Set2 does not match\n",
										"Display of Set1 and Set2 does not match\n",
										"Display and Comparator of Set1 and Set2 both does not match\n",
										"Set Union Operation is Successful\n",
										"Set Intersection Operation is Successful\n",
										"Set Difference Operation is Successful\n"};

static void modify_compare_display(pset obj, size_t size, long double (*compare)(const void *, const void *), void (*display)(const void *))
{
	switch (size)
	{
    case STRING_SET :
        obj->compare = compare == NULL ? string_comparator : compare;
        obj->display = display == NULL ? string_display : display;
        break;
    case STRING_CASE_INSENSITIVE_SET :
        obj->compare = compare == NULL ? string_case_insensitive_comparator : compare;
        obj->display = display == NULL ? string_display : display;
        break;
    case DEFAULT_SET :
    case INT_SET:
        obj->compare = compare == NULL ? int_comparator : compare;
        obj->display = display == NULL ? int_display : display;
        obj->ESize = sizeof(int);
        break;
    case CHAR_SET :
        obj->compare = compare == NULL ? char_comparator : compare;
        obj->display = display == NULL ? char_display : display;
        obj->ESize = sizeof(char);
        break;
    case BYTE_SET :
        obj->compare = compare == NULL ? byte_comparator : compare;
        obj->display = display == NULL ? int_display : display;
        obj->ESize = sizeof(byte);
        break;
    case SHORT_SET :
        obj->compare = compare == NULL ? short_comparator : compare;
        obj->display = display == NULL ? int_display : display;
        obj->ESize = sizeof(short);
        break;
    case LONG_SET :
        obj->compare = compare == NULL ? long_comparator : compare;
        obj->display = display == NULL ? long_display : display;
        obj->ESize = sizeof(long);
        break;
    case FLOAT_SET :
        obj->compare = compare == NULL ? float_comparator : compare;
        obj->display = display == NULL ? float_display : display;
        obj->ESize = sizeof(float);
        break;
    case DOUBLE_SET :
        obj->compare = compare == NULL ? double_comparator : compare;
        obj->display = display == NULL ? float_display : display;
        obj->ESize = sizeof(double);
        break;
    case LONG_DOUBLE_SET :
        obj->compare = compare == NULL ? long_double_comparator : compare;
        obj->display = display == NULL ? float_display : display;
        obj->ESize = sizeof(long double);
        break;
    case UNSIGNED_INT_SET :
        obj->compare = compare == NULL ? unsigned_int_comparator : compare;
        obj->display = display == NULL ? unsigned_int_display : display;
        obj->ESize = sizeof(unsigned int);
        break;
    case UNSIGNED_SHORT_SET :
        obj->compare = compare == NULL ? unsigned_short_comparator : compare;
        obj->display = display == NULL ? unsigned_int_display : display;
        obj->ESize = sizeof(unsigned short);
        break;
    case UNSIGNED_LONG_SET :
        obj->compare = compare == NULL ? unsigned_long_comparator : compare;
        obj->display = display == NULL ? unsigned_long_display : display;
        obj->ESize = sizeof(unsigned long);
        break;
    case LONG_LONG_SET :
        obj->compare = compare == NULL ? long_long_comparator : compare;
        obj->display = display == NULL ? long_long_display : display;
        obj->ESize = sizeof(long long);
        break;
    case UNSIGNED_LONG_LONG_SET :
        obj->compare = compare == NULL ? unsigned_long_long_comparator : compare;
        obj->display = display == NULL ? unsigned_long_long_display : display;
        obj->ESize = sizeof(unsigned long long);
        break;
    default:
        obj->compare = compare;
        obj->display = display;
	}
}

// Initialize the Set Data Structure
static set initialize_set(size_t size, long double (*compare)(const void *, const void *), void (*display)(const void *))
{
	set obj;
	obj.ctr = 0;
	obj.start = NULL;
	obj.ESize = size;
	modify_compare_display(&obj, size, compare, display);
	obj.dataRef = (JIT_Set_Iterator *)malloc(sizeof(JIT_Set_Iterator));
	((JIT_Set_Iterator *)obj.dataRef)->jit_top = NULL;
	((JIT_Set_Iterator *)obj.dataRef)->next_iterator = NULL;
	return obj;
}

// Adding Unique Element in Set;
static bool add_in_set(pset obj, const void *data)
{
	int l;
	Set_Node temp = (Set_Node)malloc(sizeof(set_node));
	if (obj->ESize == STRING_SET || obj->ESize == MODIFIED_STRING_SET || obj->ESize == STRING_CASE_INSENSITIVE_SET)
		l = strlen(data) + 1;
	else
		l = obj->ESize;
	temp->data = malloc(l);
	memcpy(temp->data, data, l);
	temp->rl = NULL;
	temp->ll = NULL;
	if (obj->start != NULL)
	{
		Set_Node travel = obj->start;
		long double r;
		while (1)
		{
			r = obj->compare(travel->data, temp->data);
			if (r == 0.0)
			{
				free(temp->data);
				free(temp);
				return false;
			}
			else if (r > 0.0)
				if (travel->ll == NULL)
				{
					travel->ll = temp;
					obj->ctr++;
					return true;
				}
				else
					travel = travel->ll;
			else if (travel->rl == NULL)
			{
				travel->rl = temp;
				obj->ctr++;
				return true;
			}
			else
				travel = travel->rl;
		}
	}
	else
	{
		obj->start = temp;
		obj->ctr++;
		return true;
	}
}

// Traversing Set Data Structure;
static void print_set_inorder(Set_Node current_start, void (*display)(const void *), bool *wp)
{
	if (current_start == NULL)
		return;
	*wp = true;
	print_set_inorder(current_start->ll, display, wp);
	display(current_start->data);
	printf(", ");
	print_set_inorder(current_start->rl, display, wp);
}

static void print_set(const set start)
{
    if (start.display == NULL)
    {
        printf("\n [ No Display Function Passed ]\n");
        return;
    }
	Set_Node st = start.start;
	bool wp = false;
	printf("[ ");
	print_set_inorder(st, start.display, &wp);
	if (wp)
		printf("\b\b ]\n");
	else
		printf("]\n");
}

// Returning Set as an Array

// Search Operation in Set
static bool Search_Set(const Set_Node in, const void *key, long double (*compare)(const void *, const void *))
{
	if (in == NULL)
		return false;
	long double res = compare(in->data, key);
	if (res == 0.0)
		return true;
	else if (res > 0.0)
		return Search_Set(in->ll, key, compare);
	else
		return Search_Set(in->rl, key, compare);
}

static bool search_set(const set obj, const void *data)
{
	return Search_Set(obj.start, data, obj.compare);
}

// Delete In Set This Operation is Most Complicated One
/*
    The following function is detecting child of parent i.e. whether left child and right child is present or not
*/
static void detect_child(Set_Node parent, bool *lc, bool *rc)
{
	if (parent->ll == NULL && parent->rl == NULL)
	{
		*lc = false;
		*rc = false;
		return;
	}
	if (parent->ll != NULL && parent->rl != NULL)
	{
		*lc = true;
		*rc = true;
		return;
	}
	if (parent->ll == NULL)
	{
		*lc = false;
		*rc = true;
		return;
	}
	if (parent->rl == NULL)
	{
		*lc = true;
		*rc = false;
		return;
	}
}

/*
    The following function is setting the child to the minimum node (of the parent passed originally) and the parent points to the parent of the minimum child pointed by child
*/
static void minchild(Set_Node *parent, Set_Node *child)
{
	if ((*child)->ll == NULL)
		return;
	*parent = (*parent)->ll;
	*child = (*child)->ll;
	minchild(parent, child);
}

/*
    This function deletes the root of the BST
*/
static bool delete_root(pset in, void **data, Set_Node *data_link)
{
	bool l, r;
	detect_child(in->start, &l, &r);
	if (!l && !r)
	{
	    *data = NULL;
	    *data_link = NULL;
	    free(in->start->data);
	    free(in->start);
     	in->start = NULL;
		return true;
	}
	if (!l && r)
	{
	    *data = in->start->data;
	    *data_link = in->start;
		in->start = in->start->rl;
		return true;
	}
	if (l && !r)
	{
	    *data = in->start->data;
	    *data_link = in->start;
		in->start = in->start->ll;
		return true;
	}
	Set_Node parent, child;
	parent = in->start->rl;
	child = parent->ll;
	if (child == NULL)
	{
	    *data = in->start->data;
		in->start->data = parent->data;
		*data_link = in->start->rl;
		in->start->rl = parent->rl;
		return true;
	}
	else if (child->ll == NULL)
	{
	    *data = in->start->data;
		in->start->data = in->start->rl->ll->data;
		*data_link = in->start->rl->ll;
		in->start->rl->ll = in->start->rl->ll->rl;
		return true;
	}
	else
	{
		minchild(&parent, &child);
		*data = in->start->data;
		in->start->data = child->data;
		*data_link = parent->ll;
		parent->ll = child->rl;
		return true;
	}

	return false;
}

static bool delete_child(Set_Node parent, Set_Node child, which_child whichChildOfParent, void **data, Set_Node *data_link)
{
	bool l, r;
	detect_child(child, &l, &r);
	if (!l && !r)
	{
	    switch (whichChildOfParent)
	    {
        case LEFT_CHILD:
            *data = parent->ll->data;
            parent->ll->data = NULL;
            *data_link = parent->ll;
            parent->ll = NULL;
            break;
        case RIGHT_CHILD:
            *data = parent->rl->data;
            parent->rl->data = NULL;
            *data_link = parent->rl;
            parent->rl = NULL;
            break;
	    }

		return true;
	}
	if (!l && r)
	{
	    switch (whichChildOfParent)
	    {
        case LEFT_CHILD:
            parent->ll = child->rl;
            break;
        case RIGHT_CHILD:
            parent->rl = child->rl;
            break;
	    }

        *data = child->data;
        child->data = NULL;
        *data_link = child;
        child = NULL;
		return true;
	}
	if (l && !r)
	{
	    switch (whichChildOfParent)
	    {
        case LEFT_CHILD:
            parent->ll = child->ll;
            break;
        case RIGHT_CHILD:
            parent->rl = child->ll;
            break;
	    }

        *data = child->data;
        child->data = NULL;
        *data_link = child;
        child = NULL;
		return true;
	}
	Set_Node new_parent = child;
	parent = new_parent->rl;
	child = parent->ll;
	if (child == NULL)
	{
	    *data = new_parent->data;
		new_parent->data = parent->data;
		*data_link = new_parent->rl;
		new_parent->rl = parent->rl;
		return true;
	}
	else if (child->ll == NULL)
	{
	    *data = new_parent->data;
		new_parent->data = new_parent->rl->ll->data;
		*data_link = new_parent->rl->ll;
		new_parent->rl->ll = new_parent->rl->ll->rl;
		return true;
	}
	else
	{
		minchild(&parent, &child);
		*data = new_parent->data;
		new_parent->data = child->data;
		*data_link = parent->ll;
		parent->ll = child->rl;
		return true;
	}

	return false;
}

static bool delete_in_set(pset in, void *key)
{
    bool retVal = false;
	if (in->start == NULL)
		return retVal;
	long double res = in->compare(in->start->data, key);
	void *dat = NULL;
	Set_Node dat_link = NULL;
	if (res == 0.0)
	{
		retVal = delete_root(in,&dat,&dat_link);
		if (retVal)
		{
			if (dat != NULL)
                free(dat);	// To see the value in dat use *(int *)data
            if (dat_link != NULL)
                free(dat_link); // To See the value in dat_link use *(int *)(((Set_Node)dat)->data)
            in->ctr--;
		}
		return retVal;
	}
	Set_Node parent = in->start, child;
	which_child whichChildOfParent;
	if (res > 0.0)
	{
		child = parent->ll;
		whichChildOfParent = LEFT_CHILD;
	}
	else
	{
	    child = parent->rl;
		whichChildOfParent = RIGHT_CHILD;
	}
	while (child != NULL)
	{
		res = in->compare(child->data, key);
		if (res == 0.0)
		{
			dat = NULL;
			dat_link = NULL;
            retVal = delete_child(parent, child, whichChildOfParent,&dat,&dat_link);
            if (retVal)
			{
				if (dat != NULL)
					free(dat);	// To see the value in dat use *(int *)data
				if (dat_link != 0)
                    free(dat_link); // To See the value in dat_link use *(int *)(((Set_Node)dat)->data)
                in->ctr--;
			}
			return retVal;
		}
		parent = child;
		if (res > 0.0)
		{
			child = parent->ll;
			whichChildOfParent = LEFT_CHILD;
		}
		else
		{
			child = parent->rl;
			whichChildOfParent = RIGHT_CHILD;
		}
	}
	return retVal;
}
// Delete From Set Operation Section Completes

static bool build_set_operation_message(const set set1, const set set2, long *message, short mode)
{
	switch (mode)
	{
	case SET_UNION:
		*message = (long)set_operation_message[mode];
		break;
	case SET_INTERSECTION:
		*message = (long)set_operation_message[mode];
		break;
	case SET_DIFFERENCE:
		*message = (long)set_operation_message[mode];
		break;
	}

	bool retVal = true;
	if (set1.compare != set2.compare)
	{
		*message = (long)set_operation_message[0];
		retVal = false;
	}
	if (set1.display != set2.display)
	{
		*message = retVal ? (long)set_operation_message[1] : (long)set_operation_message[2];
		retVal = false;
	}
	return retVal;
}

// Union Operation
static void Set_Union(pset unionSet, const Set_Node current_from, size_t size, long double (*compare)(const void *, const void *))
{
	if (current_from == NULL)
		return;
	Set_Union(unionSet, current_from->ll, size, compare);
	add_in_set(unionSet, current_from->data);
	Set_Union(unionSet, current_from->rl, size, compare);
}

static set set_union(const set set1, const set set2, long *message)
{
	set unionSet;
	unionSet = initialize_set(set1.ESize, set1.compare, set1.display);
	if (!build_set_operation_message(set1, set2, message, SET_UNION))
		return unionSet;
	if (set2.start == NULL)
		return unionSet;
	Set_Union(&unionSet, set1.start, set1.ESize, set1.compare);
	Set_Union(&unionSet, set2.start, set2.ESize, set2.compare);
	return unionSet;
}

// Intersection Operation
static void set_intersect(pset add, const set to, const Set_Node current_from, size_t size, long double (*compare)(const void *, const void *))
{
	if (current_from == NULL)
		return;
	if (search_set(to, current_from->data))
		add_in_set(add, current_from->data);
	set_intersect(add, to, current_from->ll, size, compare);
	set_intersect(add, to, current_from->rl, size, compare);
}

static set set_intersection(const set set1, const set set2, long *message)
{
	set intersectSet;
	intersectSet = initialize_set(set1.ESize, set1.compare, set1.display);
	if (!build_set_operation_message(set1, set2, message, SET_INTERSECTION))
		return intersectSet;
	set_intersect(&intersectSet, set1, set2.start, set1.ESize, set1.compare);
	return intersectSet;
}

// Set Difference
static void set_diff(pset diffSet, const set set2, const Set_Node set1, long double (*compare)(const void *, const void *))
{
	if (set1 == NULL)
		return;
	if (!search_set(set2, set1->data))
		add_in_set(diffSet, set1->data);
	set_diff(diffSet, set2, set1->ll, compare);
	set_diff(diffSet, set2, set1->rl, compare);
}

static set set_difference(const set set1, const set set2, long *message)
{
	set diffSet;
	diffSet = initialize_set(set1.ESize, set1.compare, set1.display);
	if (!build_set_operation_message(set1, set2, message, SET_DIFFERENCE))
		return diffSet;
	if (set1.start == NULL)
		return diffSet;
	if (set2.start == NULL)
		return set1;
	set_diff(&diffSet, set2, set1.start, set1.compare);
	return diffSet;
}


// Set Traversal Section
static void get_iterator_object(const set obj, const set_node iter, Set_Node updatedIterator, bool toFree)
{
    updatedIterator->ll = NULL;
    updatedIterator->rl = NULL;
    int l;
    if (obj.ESize == STRING_SET || obj.ESize == MODIFIED_STRING_SET || obj.ESize == STRING_CASE_INSENSITIVE_SET)
		l = strlen(iter.data) + 1;
	else
		l = obj.ESize;

    if (toFree)
    {
        free(updatedIterator->data);
        updatedIterator->data = NULL;
    }
	updatedIterator->data = malloc(l);
	memcpy(updatedIterator->data, iter.data, l);
}

static void push_in_set_stack(pset obj,Set_Node data)
{
	JIT_Set_Stack_Elem *topElem = (JIT_Set_Stack_Elem *)malloc(sizeof(JIT_Set_Stack_Elem));
	topElem->node = data;
	topElem->next_link = ((JIT_Set_Iterator *)obj->dataRef)->jit_top;
	((JIT_Set_Iterator *)obj->dataRef)->jit_top = topElem;
}

static Set_Node pop_from_set_stack(pset obj)
{
	if (((JIT_Set_Iterator *)obj->dataRef)->jit_top == NULL)
		return NULL;
    Set_Node retVal = ((JIT_Set_Iterator *)obj->dataRef)->jit_top->node;
    //free(((JIT_Set_Iterator *)obj->dataRef)->jit_top);
    ((JIT_Set_Iterator *)obj->dataRef)->jit_top = ((JIT_Set_Iterator *)obj->dataRef)->jit_top->next_link;
    return retVal;
}

static bool get_iterator(pset obj, Set_Node updatedIterator)
{
    if (obj->start == NULL)
    {
        updatedIterator->data = NULL;
        updatedIterator->ll = NULL;
        updatedIterator->rl = NULL;
        return false;
    }
	get_iterator_object(*obj,*(obj->start),updatedIterator,false);
	// set_iterator iterator = obj->start;
	if (obj->start->ll != NULL)
	{
		if (obj->start->rl != NULL)
			push_in_set_stack(obj,obj->start->rl);
		((JIT_Set_Iterator *)obj->dataRef)->next_iterator = obj->start->ll;
	}
	else if (obj->start->rl != NULL)
	{
		((JIT_Set_Iterator *)obj->dataRef)->next_iterator = obj->start->rl;
	}
	else
	{
		((JIT_Set_Iterator *)obj->dataRef)->next_iterator = NULL;
	}

	return true;
}

static bool next_iterator(pset obj, Set_Node updatedIterator)
{
	if (((JIT_Set_Iterator *)obj->dataRef)->next_iterator == NULL)
    {
        free(updatedIterator->data);
        updatedIterator->ll = NULL;
        updatedIterator->rl = NULL;
		updatedIterator->data = NULL;
		return false;
    }

	get_iterator_object(*obj,*(((JIT_Set_Iterator *)obj->dataRef)->next_iterator),updatedIterator,true);
    // set_iterator iterator = obj->dataRef->next_iterator;

	if (((JIT_Set_Iterator *)obj->dataRef)->next_iterator->ll != NULL)
	{
		if (((JIT_Set_Iterator *)obj->dataRef)->next_iterator->rl != NULL)
			push_in_set_stack(obj,((JIT_Set_Iterator *)obj->dataRef)->next_iterator->rl);
		((JIT_Set_Iterator *)obj->dataRef)->next_iterator = ((JIT_Set_Iterator *)obj->dataRef)->next_iterator->ll;
	}
	else if (((JIT_Set_Iterator *)obj->dataRef)->next_iterator->rl != NULL)
	{
		((JIT_Set_Iterator *)obj->dataRef)->next_iterator = ((JIT_Set_Iterator *)obj->dataRef)->next_iterator->rl;
	}
	else
	{
		((JIT_Set_Iterator *)obj->dataRef)->next_iterator = pop_from_set_stack(obj);
	}

	return true;
}
// Set Traversal section ends

// Destroy Set Object Section

void delete_set_node_post_order(pset obj, Set_Node current_node, void (*addOnsClean)(const void *))
{
	if (current_node == NULL)
		return;
	delete_set_node_post_order(obj,current_node->ll,addOnsClean);
	delete_set_node_post_order(obj,current_node->rl,addOnsClean);
	if (addOnsClean != NULL)
		addOnsClean(current_node->data);
	free(current_node->data);
	current_node->data = NULL;
	free(current_node);
	current_node = NULL;
	obj->ctr--;
}

void destroy_set_object(pset obj, void (*addOnsClean)(const void *))
{
    delete_set_node_post_order(obj, obj->start,addOnsClean);
    obj->ctr = 0;
    obj->start = NULL;
    ((JIT_Set_Iterator *)obj->dataRef)->next_iterator = NULL;
    ((JIT_Set_Iterator *)obj->dataRef)->jit_top = NULL;
}

// Destroy Set Object Section Ends

const GLOBAL_SET_OBJECT Set =
{
    initialize_set,

    add_in_set,

    print_set,

    search_set,

    delete_in_set,

    set_union,
    set_intersection,
    set_difference,

    get_iterator,
    next_iterator,

    destroy_set_object,
    destroy_set_object
};
