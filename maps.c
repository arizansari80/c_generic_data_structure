// Tree Map Implementation

#include "maps.h"

// Map Initialization Section
static void modify_compare_display_map(pmap obj, size_t key_size, size_t value_size, long double (*key_compare)(const void *, const void *), long double (*value_compare)(const void *, const void *), void (*display)(const void *,const void *))
{
	switch (key_size)
	{
    case STRING_KEY :
        obj->key_compare = key_compare == NULL ? string_comparator : key_compare;
        break;
    case STRING_CASE_INSENSITIVE_KEY :
        obj->key_compare = key_compare == NULL ? string_case_insensitive_comparator : key_compare;
        break;
    case DEFAULT_KEY :
    case INT_KEY:
        obj->key_compare = key_compare == NULL ? int_comparator : key_compare;
        obj->key_size = sizeof(int);
        break;
    case CHAR_KEY :
        obj->key_compare = key_compare == NULL ? char_comparator : key_compare;
        obj->key_size = sizeof(char);
        break;
    case BYTE_KEY :
        obj->key_compare = key_compare == NULL ? byte_comparator : key_compare;
        obj->key_size = sizeof(byte);
        break;
    case SHORT_KEY :
        obj->key_compare = key_compare == NULL ? short_comparator : key_compare;
        obj->key_size = sizeof(short);
        break;
    case LONG_KEY :
        obj->key_compare = key_compare == NULL ? long_comparator : key_compare;
        obj->key_size = sizeof(long);
        break;
    case FLOAT_KEY :
        obj->key_compare = key_compare == NULL ? float_comparator : key_compare;
        obj->key_size = sizeof(float);
        break;
    case DOUBLE_KEY :
        obj->key_compare = key_compare == NULL ? double_comparator : key_compare;
        obj->key_size = sizeof(double);
        break;
    case LONG_DOUBLE_KEY :
        obj->key_compare = key_compare == NULL ? long_double_comparator : key_compare;
        obj->key_size = sizeof(long double);
        break;
    case UNSIGNED_INT_KEY :
        obj->key_compare = key_compare == NULL ? unsigned_int_comparator : key_compare;
        obj->key_size = sizeof(unsigned int);
        break;
    case UNSIGNED_SHORT_KEY :
        obj->key_compare = key_compare == NULL ? unsigned_short_comparator : key_compare;
        obj->key_size = sizeof(unsigned short);
        break;
    case UNSIGNED_LONG_KEY :
        obj->key_compare = key_compare == NULL ? unsigned_long_comparator : key_compare;
        obj->key_size = sizeof(unsigned long);
        break;
    case LONG_LONG_KEY :
        obj->key_compare = key_compare == NULL ? long_long_comparator : key_compare;
        obj->key_size = sizeof(long long);
        break;
    case UNSIGNED_LONG_LONG_KEY :
        obj->key_compare = key_compare == NULL ? unsigned_long_long_comparator : key_compare;
        obj->key_size = sizeof(unsigned long long);
        break;
    default:
        obj->key_compare = key_compare;
	}

	switch (value_size)
	{
    case STRING_VALUE :
        obj->value_compare = value_compare == NULL ? string_comparator : value_compare;
        break;
    case STRING_CASE_INSENSITIVE_VALUE :
        obj->value_compare = value_compare == NULL ? string_case_insensitive_comparator : value_compare;
        break;
    case DEFAULT_VALUE :
    case INT_VALUE:
        obj->value_compare = value_compare == NULL ? int_comparator : value_compare;
        obj->value_size = sizeof(int);
        break;
    case CHAR_VALUE :
        obj->value_compare = value_compare == NULL ? char_comparator : value_compare;
        obj->value_size = sizeof(char);
        break;
    case BYTE_VALUE :
        obj->value_compare = value_compare == NULL ? byte_comparator : value_compare;
        obj->value_size = sizeof(byte);
        break;
    case SHORT_VALUE :
        obj->value_compare = value_compare == NULL ? short_comparator : value_compare;
        obj->value_size = sizeof(short);
        break;
    case LONG_VALUE :
        obj->value_compare = value_compare == NULL ? long_comparator : value_compare;
        obj->value_size = sizeof(long);
        break;
    case FLOAT_VALUE :
        obj->value_compare = value_compare == NULL ? float_comparator : value_compare;
        obj->value_size = sizeof(float);
        break;
    case DOUBLE_VALUE :
        obj->value_compare = value_compare == NULL ? double_comparator : value_compare;
        obj->value_size = sizeof(double);
        break;
    case LONG_DOUBLE_VALUE :
        obj->value_compare = value_compare == NULL ? long_double_comparator : value_compare;
        obj->value_size = sizeof(long double);
        break;
    case UNSIGNED_INT_VALUE :
        obj->value_compare = value_compare == NULL ? unsigned_int_comparator : value_compare;
        obj->value_size = sizeof(unsigned int);
        break;
    case UNSIGNED_SHORT_VALUE :
        obj->value_compare = value_compare == NULL ? unsigned_short_comparator : value_compare;
        obj->value_size = sizeof(unsigned short);
        break;
    case UNSIGNED_LONG_VALUE :
        obj->value_compare = value_compare == NULL ? unsigned_long_comparator : value_compare;
        obj->value_size = sizeof(unsigned long);
        break;
    case LONG_LONG_VALUE :
        obj->value_compare = value_compare == NULL ? long_long_comparator : value_compare;
        obj->value_size = sizeof(long long);
        break;
    case UNSIGNED_LONG_LONG_VALUE :
        obj->value_compare = value_compare == NULL ? unsigned_long_long_comparator : value_compare;
        obj->value_size = sizeof(unsigned long long);
        break;
    default:
        obj->value_compare = value_compare;
	}

	obj->display = display;
}

map initialize_map(size_t key_size, size_t value_size, long double (*key_compare)(const void *, const void *), long double (*value_compare)(const void *, const void *), void (*display)(const void *,const void *))
{
    map obj;
	obj.ctr = 0;
	obj.start = NULL;
	obj.key_size = key_size;
	obj.value_size = value_size;
	modify_compare_display_map(&obj, key_size, value_size, key_compare, value_compare, display);
	obj.dataRef = (JIT_Map_Iterator *)malloc(sizeof(JIT_Map_Iterator));
	((JIT_Map_Iterator *)obj.dataRef)->jit_top = NULL;
	((JIT_Map_Iterator *)obj.dataRef)->next_iterator = NULL;
	return obj;
}

// Map Initialization Section Ends Here

// Helper Function Section Begins Here
static void get_key_value_length(const map obj, int *key_length, int *value_length, const void *key, const void *value)
{
	switch (obj.key_size)
	{
	case STRING_KEY:
    case STRING_CASE_INSENSITIVE_KEY:
	case MODIFIED_STRING_KEY:
		*key_length = strlen(key) + 1;
		break;
	default:
		*key_length = obj.key_size;
	}

	switch (obj.value_size)
	{
	case STRING_VALUE:
    case STRING_CASE_INSENSITIVE_VALUE:
	case MODIFIED_STRING_VALUE:
		*value_length = strlen(value) + 1;
		break;
	default:
		*value_length = obj.value_size;
	}
}

static private_map_data_for_library *build_map_node_data(const map obj, const void *key, const void *value)
{
	int key_length, value_length;
	get_key_value_length(obj,&key_length,&value_length,key,value);
	private_map_data_for_library *ret_data = (private_map_data_for_library *)malloc(sizeof(private_map_data_for_library));
	ret_data->key = malloc(key_length);
	ret_data->value = malloc(value_length);
	memcpy(ret_data->key, key, key_length);
	memcpy(ret_data->value, value, value_length);
	return ret_data;
}

// Helper Function Section Ends Here

// Add In Map Section Begins Here
bool add_in_map(pmap obj, const void *data,const void *value)
{
	Map_Node temp = (Map_Node)malloc(sizeof(map_node));
	temp->data = build_map_node_data(*obj, data, value);
	temp->rl = NULL;
	temp->ll = NULL;
	if (obj->start != NULL)
	{
		Map_Node travel = obj->start;
		long double r;
		while (1)
		{
			r = obj->key_compare(travel->data->key, temp->data->key);
			if (r == 0.0)
			{
				free(temp->data->key);
				free(temp->data->value);
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
// Add In Map Section Ends Here

// Search Operation in Map
static void *Search_Map(const map obj, const Map_Node in, const void *key, long double (*key_compare)(const void *, const void *), private_map_data_for_library **ptr_searched)
{
	if (in == NULL)
		return NULL;
	long double res = key_compare(in->data->key, key);
	if (res == 0.0)
	{
		if (ptr_searched != NULL)
			*ptr_searched = in->data;
		int key_length,value_length;
		get_key_value_length(obj,&key_length,&value_length,key,in->data->value);
		void *val = malloc(value_length);
		memcpy(val,in->data->value,value_length);
		return val;
		//return in->data->value;
	}
	else if (res > 0.0)
		return Search_Map(obj,in->ll, key, key_compare,ptr_searched);
	else
		return Search_Map(obj,in->rl, key, key_compare,ptr_searched);
}

static void *get_value_of_key_in_map(const map obj, const void *key)
{
	return Search_Map(obj,obj.start, key, obj.key_compare,NULL);
}

static bool map_contains_key(const map obj, const void *key)
{
	return get_value_of_key_in_map(obj,key) != NULL;
}

// Search Operation in Map
static bool Search_Value_Map(const Map_Node in, const void *value, long double (*value_compare)(const void *, const void *))
{
	if (in == NULL)
		return false;
	long double res = value_compare(in->data->value, value);
	if (res == 0.0)
		return true;
	else if (res > 0.0)
		return Search_Value_Map(in->ll, value, value_compare);
	else
		return Search_Value_Map(in->rl, value, value_compare);
}

static bool map_contains_value(const map obj, const void *value)
{
	return Search_Value_Map(obj.start, value, obj.value_compare);
}

static bool map_contains_key_with_value(const map obj, const void *key, const void *value)
{
	void *v = get_value_of_key_in_map(obj,key);
	return v != NULL ? obj.value_compare(v,value) == 0.0 : false;
}
// Traversing Map Data Structure;
static void print_map_inorder(Map_Node current_start, void (*display)(const void *,const void *), bool *wp)
{
	if (current_start == NULL)
		return;
	*wp = true;
	print_map_inorder(current_start->ll, display, wp);
	display(current_start->data->key,current_start->data->value);
	printf(", ");
	print_map_inorder(current_start->rl, display, wp);
}

void print_map(const map start)
{
    if (start.display == NULL)
    {
        printf("\n [ No Display Function Passed ]\n");
        return;
    }
	Map_Node st = start.start;
	bool wp = false;
	printf("[ ");
	print_map_inorder(st, start.display, &wp);
	if (wp)
		printf("\b\b ]\n");
	else
		printf("]\n");
}

// Delete From Map Operation Section Begins

static void detect_map_child(Map_Node parent, bool *lc, bool *rc)
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

static void map_minchild(Map_Node *parent, Map_Node *child)
{
	if ((*child)->ll == NULL)
		return;
	*parent = (*parent)->ll;
	*child = (*child)->ll;
	map_minchild(parent, child);
}

static bool delete_map_root(pmap in, private_map_data_for_library **data, Map_Node *data_link)
{
	bool l, r;
	detect_map_child(in->start, &l, &r);
	if (!l && !r)
	{
	    *data = in->start->data;
	    *data_link = in->start;
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
	Map_Node parent, child;
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
		map_minchild(&parent, &child);
		*data = in->start->data;
		in->start->data = child->data;
		*data_link = parent->ll;
		parent->ll = child->rl;
		return true;
	}

	return false;
}

static bool delete_map_child(Map_Node parent, Map_Node child, which_child whichChildOfParent, private_map_data_for_library **data, Map_Node *data_link)
{
	bool l, r;
	detect_map_child(child, &l, &r);
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
	Map_Node new_parent = child;
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
		map_minchild(&parent, &child);
		*data = new_parent->data;
		new_parent->data = child->data;
		*data_link = parent->ll;
		parent->ll = child->rl;
		return true;
	}

	return false;
}

static bool delete_in_map(pmap in, const void *key, const void *value)
{
    bool retVal = false;
	if (in->start == NULL)
		return retVal;
    private_map_data_for_library *dat = NULL;
    Map_Node dat_link = NULL;
	long double res = in->key_compare(in->start->data->key, key);
	if (res == 0.0)
	{
		if (value != NULL)
			res = in->value_compare(in->start->data->value, value);

		if (res == 0.0)
		{
			retVal = delete_map_root(in,&dat,&dat_link);
			if (retVal)
			{
				if (dat != NULL)
				{
					free(dat->key);	// To see the value in dat use *(int *)data
					free(dat->value);
					free(dat);
				}
				if (dat_link != NULL)
					free(dat_link); // To See the value in dat_link use *(int *)(((Set_Node)dat)->data)
				in->ctr--;
			}
		}

		return retVal;
	}
	Map_Node parent = in->start, child;
	which_child which;
	if (res > 0.0)
	{
		child = parent->ll;
		which = LEFT_CHILD;
	}
	else
	{
		child = parent->rl;
		which = RIGHT_CHILD;
	}
	while (child != NULL)
	{
		res = in->key_compare(child->data->key, key);
		if (res == 0.0)
		{
			if (value != NULL)
				res = in->value_compare(child->data->value, value);

			if (res == 0.0)
			{
				dat = NULL;
				dat_link = NULL;
				retVal = delete_map_child(parent, child, which, &dat, &dat_link);
				if (retVal)
				{
					if (dat != NULL)
					{
						free(dat->key);	// To see the value in dat use *(int *)data
						free(dat->value);
						free(dat);
					}
					if (dat_link != NULL)
						free(dat_link); // To See the value in dat_link use *(int *)(((Set_Node)dat)->data)
					in->ctr--;
				}
			}

            return retVal;
		}
		parent = child;
		if (res > 0.0)
		{
			child = parent->ll;
			which = LEFT_CHILD;
		}
		else
		{
			child = parent->rl;
			which = RIGHT_CHILD;
		}
	}
	return retVal;
}

static bool delete_key_from_map(pmap in, const void *key)
{
	return delete_in_map(in,key,NULL);
}

static bool delete_key_with_value_from_map(pmap in, const void *key, const void *value)
{
	return delete_in_map(in,key,value);
}
// Delete From Map Operation Section Completes Here

// Map Traversal Section
static void get_iterator_object_map(const map obj,const map_node iter, Map_Node updatedIterator, bool toFree)
{
    updatedIterator->ll = NULL;
    updatedIterator->rl = NULL;
	int key_length, value_length;
	get_key_value_length(obj,&key_length,&value_length,iter.data->key,iter.data->value);
    if (toFree)
    {
        free(updatedIterator->data->key);
		free(updatedIterator->data->value);
        updatedIterator->data->key = NULL;
		updatedIterator->data->value = NULL;
    }
	else
	{
		updatedIterator->data = (private_map_data_for_library *)malloc(sizeof(private_map_data_for_library));
	}
	updatedIterator->data->key = malloc(key_length);
	updatedIterator->data->value = malloc(value_length);
	memcpy(updatedIterator->data->key, iter.data->key, key_length);
	memcpy(updatedIterator->data->value, iter.data->value, value_length);
}

static void push_in_map_stack(pmap obj,Map_Node data)
{
	JIT_Map_Stack_Elem *topElem = (JIT_Map_Stack_Elem *)malloc(sizeof(JIT_Map_Stack_Elem));
	topElem->node = data;
	topElem->next_link = ((JIT_Map_Iterator *)obj->dataRef)->jit_top;
	((JIT_Map_Iterator *)obj->dataRef)->jit_top = topElem;
}

static Map_Node pop_from_map_stack(pmap obj)
{
	if (((JIT_Map_Iterator *)obj->dataRef)->jit_top == NULL)
		return NULL;
    Map_Node retVal = ((JIT_Map_Iterator *)obj->dataRef)->jit_top->node;
    ((JIT_Map_Iterator *)obj->dataRef)->jit_top = ((JIT_Map_Iterator *)obj->dataRef)->jit_top->next_link;
    return retVal;
}

static bool get_iterator_map(pmap obj, Map_Node updatedIterator)
{
	if (obj->start == NULL)
    {
        updatedIterator->data = NULL;
        updatedIterator->ll = NULL;
        updatedIterator->rl = NULL;
        return false;
    }
	get_iterator_object_map(*obj,*(obj->start),updatedIterator,false);
	// map_iterator iterator = obj->start;
	if (obj->start->ll != NULL)
	{
		if (obj->start->rl != NULL)
			push_in_map_stack(obj,obj->start->rl);
		((JIT_Map_Iterator *)obj->dataRef)->next_iterator = obj->start->ll;
	}
	else if (obj->start->rl != NULL)
	{
		((JIT_Map_Iterator *)obj->dataRef)->next_iterator = obj->start->rl;
	}
	else
	{
		((JIT_Map_Iterator *)obj->dataRef)->next_iterator = NULL;
	}

    return true;
}

static bool next_iterator_map(pmap obj, Map_Node updatedIterator)
{
	if (((JIT_Map_Iterator *)obj->dataRef)->next_iterator == NULL)
	{
		free(updatedIterator->data->key);
		free(updatedIterator->data->value);
        free(updatedIterator->data);
        updatedIterator->ll = NULL;
        updatedIterator->rl = NULL;
		updatedIterator->data = NULL;
		return false;
    }
	get_iterator_object_map(*obj,*(((JIT_Map_Iterator *)obj->dataRef)->next_iterator),updatedIterator,true);
    // map_iterator iterator = ((JIT_Map_Iterator *)obj->dataRef)->next_iterator;

	if (((JIT_Map_Iterator *)obj->dataRef)->next_iterator->ll != NULL)
	{
		if (((JIT_Map_Iterator *)obj->dataRef)->next_iterator->rl != NULL)
			push_in_map_stack(obj,((JIT_Map_Iterator *)obj->dataRef)->next_iterator->rl);
		((JIT_Map_Iterator *)obj->dataRef)->next_iterator = ((JIT_Map_Iterator *)obj->dataRef)->next_iterator->ll;
	}
	else if (((JIT_Map_Iterator *)obj->dataRef)->next_iterator->rl != NULL)
	{
		((JIT_Map_Iterator *)obj->dataRef)->next_iterator = ((JIT_Map_Iterator *)obj->dataRef)->next_iterator->rl;
	}
	else
	{
		((JIT_Map_Iterator *)obj->dataRef)->next_iterator = pop_from_map_stack(obj);
	}

	return true;
}
// Map Traversal section ends

// Map Replace Section Begins Here

static bool replace_value_of_key(pmap obj, const void *key, const void *value, const void *old_value)
{
	bool retVal = false;
    private_map_data_for_library *ptr_searched;
    void *value_of_key = Search_Map(*obj,obj->start,key,obj->key_compare,&ptr_searched);
    if (value_of_key != NULL)
	{
		if (old_value != NULL && obj->value_compare(value_of_key,old_value) != 0.0)
		{
			retVal = false;
		}
		else
		{
			int key_length,value_length;
			get_key_value_length(*obj,&key_length,&value_length,ptr_searched->key,value);
			free(ptr_searched->value);
			ptr_searched->value = NULL;
			ptr_searched->value = malloc(value_length);
			memcpy(ptr_searched->value,value,value_length);
			retVal = true;
		}
	}

	return retVal;
}


static bool replace_old_value_of_key(pmap obj, const void *key, const void *value)
{
	return replace_value_of_key(obj,key,value,NULL);
}

static bool replace_old_value_of_key_with_new_value(pmap obj, const void *key, const void *old_value, const void *new_value)
{
	return replace_value_of_key(obj,key,new_value,old_value);
}
// Map Replace Section Ends Here


// Destroy Map Object Section

void delete_map_node_post_order(pmap obj, Map_Node current_node)
{
	if (current_node == NULL)
		return;
	delete_map_node_post_order(obj,current_node->ll);
	delete_map_node_post_order(obj,current_node->rl);
	free(current_node->data->key);
	free(current_node->data->value);
	current_node->data->key = NULL;
	current_node->data->value = NULL;
	free(current_node->data);
	current_node->data = NULL;
	free(current_node);
	current_node = NULL;
	obj->ctr--;
}

void destroy_map_object(pmap obj)
{
    delete_map_node_post_order(obj, obj->start);
    obj->ctr = 0;
    obj->start = NULL;
    ((JIT_Map_Iterator *)obj->dataRef)->next_iterator = NULL;
    ((JIT_Map_Iterator *)obj->dataRef)->jit_top = NULL;
}

// Destroy Map Object Section Ends

const GLOBAL_MAP_OBJECT Map =
{
    initialize_map,

    add_in_map,

    print_map,

    get_value_of_key_in_map,
    map_contains_key,
    map_contains_value,
    map_contains_key_with_value,

    delete_key_from_map,
    delete_key_with_value_from_map,

    get_iterator_map,
    next_iterator_map,

    destroy_map_object,
	destroy_map_object,

	replace_old_value_of_key,
	replace_old_value_of_key_with_new_value
};
