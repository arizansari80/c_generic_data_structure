#include <string.h>
#include <stdbool.h>

// Declaring Set structure;
typedef struct set_node{
	void * data;
	struct set_node *ll;
	struct set_node *rl;
}set_node;

typedef set_node * Set_Node;

typedef struct set{
	size_t ESize;
	int ctr;
	float (*compare)(const void *,const void *);
	void (*display)(const void *);
	Set_Node start;
}set;

typedef set * Set;

void initialize_set(Set *obj,size_t size,float (*compare)(const void *,const void *),void (*display)(const void *)){
	*obj=(Set)malloc(sizeof(set));
	(*obj)->ESize=size;
	(*obj)->ctr=0;
	(*obj)->compare=compare;
	(*obj)->display=display;
	(*obj)->start=NULL;
}

// Adding Unique Element in Set;
bool add_in_set(Set *start,const void *data){
	int l;
	Set_Node temp=(Set_Node)malloc(sizeof(set_node));
	if((*start)->ESize==0)
		l=strlen(data)+1;
	else
		l=(*start)->ESize;
	temp->data=malloc(l);
	memcpy(temp->data,data,l);
	temp->rl=NULL;
	temp->ll=NULL;
	if((*start)->start!=NULL){
		Set_Node travel=(*start)->start;
		float r;
		while(1){
			r=(*start)->compare(travel->data,temp->data);
			if(r==0){
				free(temp->data);
				free(temp);
				return false;
			}
			else if(r>0)
				if(travel->ll==NULL){
					travel->ll=temp;
					(*start)->ctr++;
					return true;
				}
				else
					travel=travel->ll;
			else
				if(travel->rl==NULL){
					travel->rl=temp;
					(*start)->ctr++;
					return true;
				}
				else
					travel=travel->rl;
		}
	}
	else{
		(*start)->start=temp;
		(*start)->ctr++;
		return true;
	}
}

// Traversing Set Data Structure;
void print_set_inorder(Set_Node current_start,void (*display)(const void *),bool *wp){
	if(current_start==NULL)
		return;
	*wp=true;
	print_set_inorder(current_start->ll,display,wp);
	display(current_start->data);
	printf(", ");
	print_set_inorder(current_start->rl,display,wp);
}

void print_set(Set start){
	Set_Node st=start->start;
	bool wp=false;
	printf("[ ");
	print_set_inorder(st,start->display,&wp);
	if(wp)
		printf("\b\b ]\n");
	else
		printf("]\n");
}

// Returning Set as an Array

// Search Operation in Set
bool Search_Set(const Set_Node in,const void *key,float (*compare)(const void *,const void *)){
	if(in==NULL)
		return false;
	int res=compare(in->data,key);
	if(res==0)
		return true;
	else if(res>0)
		return Search_Set(in->ll,key,compare);
	else
		return Search_Set(in->rl,key,compare);
}

bool search_set(const Set obj,const void *data){
	return Search_Set(obj->start,data,obj->compare);
}

// Delete In Sets This Operation is Most Complicated One

void detect_child(Set_Node parent,bool *lc,bool *rc){
	if(parent->ll==NULL&&parent->rl==NULL){
		*lc=false;
		*rc=false;
		return;
	}
	if(parent->ll!=NULL&&parent->rl!=NULL){
		*lc=true;
		*rc=true;
		return;
	}
	if(parent->ll==NULL){
		*lc=false;
		*rc=true;
		return;
	}
	if(parent->rl==NULL){
		*lc=true;
		*rc=false;
		return;
	}
}

void minchild(Set_Node *parent,Set_Node *child){
	if((*child)->ll==NULL)
		return;
	*parent=(*parent)->ll;
	*child=(*child)->ll;
	minchild(parent,child);
}

bool delete_root(Set *in){
	bool l,r;
	detect_child((*in)->start,&l,&r);
	if(!l&&!r){
		(*in)->start=NULL;
		return true;
	}
	if(!l&&r){
		(*in)->start=(*in)->start->rl;
		return true;
	}
	if(l&&!r){
		(*in)->start=(*in)->start->ll;
		return true;
	}
	Set_Node parent,child;
	parent=(*in)->start->rl;
	child=parent->ll;
	if(child==NULL){
		(*in)->start->data=parent->data;
		(*in)->start->rl=parent->rl;
		return true;
	}
	else if(child->ll==NULL){
		(*in)->start->data=(*in)->start->rl->ll->data;
		(*in)->start->rl->ll=(*in)->start->rl->ll->rl;
		return true;
	}
	else{
		minchild(&parent,&child);
		(*in)->start->data=child->data;
		parent->ll=child->rl;
		return true;
	}
}

bool delete_child(Set_Node parent,Set_Node child,bool which){
	bool l,r;
	detect_child(child,&l,&r);
	if(!l&&!r){
		if(which)
			parent->rl=NULL;
		else
			parent->ll=NULL;
		return true;
	}
	if(!l&&r){
		if(which)
			parent->rl=child->rl;
		else
			parent->ll=child->rl;
		return true;
	}
	if(l&&!r){
		if(which)
			parent->rl=child->ll;
		else
			parent->ll=child->ll;
		return true;	
	}
	Set_Node p=child;
	parent=p->rl;
	child=parent->ll;
	if(child==NULL){
		p->data=parent->data;
		p->rl=parent->rl;
		return true;
	}
	else if(child->ll==NULL){
		p->data=p->rl->ll->data;
		p->rl->ll=p->rl->ll->rl;
		return true;
	}
	else{
		minchild(&parent,&child);
		p->data=child->data;
		parent->ll=child->rl;
		return true;
	}
}

bool delete_in_set(Set *in,void *key){
	if((*in)->start==NULL)
		return false;
	float res=(*in)->compare((*in)->start->data,key);
	if(res==0){
		(*in)->ctr--;
		return delete_root(in);
	}
	Set_Node parent=(*in)->start,child;
	bool which;
	if(res>0){
		child=parent->ll;
		which=false;
	}
	else{
		which=true;
		child=parent->rl;
	}
	while(child!=NULL){
		res=(*in)->compare(child->data,key);
		if(res==0){
			(*in)->ctr--;
			return delete_child(parent,child,which);
		}
		parent=child;
		if(res>0){
			child=parent->ll;
			which=false;
		}
		else{
			child=parent->rl;
			which=true;
		}
	}
	return false;
}

// Union Operation
void Set_Union(Set *to,const Set_Node current_from,size_t size,float (*compare)(const void *,const void *)){
	if(current_from==NULL)
		return;
	Set_Union(to,current_from->ll,size,compare);
	add_in_set(to,current_from->data);
	Set_Union(to,current_from->rl,size,compare);
}

void set_union(Set *to,const Set from){
	if(from->start==NULL)
		return;
	Set_Union(to,from->start,(*to)->ESize,(*to)->compare);
}

// Intersection Operation
void set_intersect(Set *add,Set to,const Set_Node current_from,size_t size,float (*compare)(const void *,const void *)){
	if(current_from==NULL)
		return;
	if(search_set(to,current_from->data))
		add_in_set(add,current_from->data);
	set_intersect(add,to,current_from->ll,size,compare);
	set_intersect(add,to,current_from->rl,size,compare);
}

void set_intersection(Set *to,const Set from){
	Set NEW=NULL;
	initialize_set(&NEW,(*to)->ESize,(*to)->compare,(*to)->display);
	set_intersect(&NEW,*to,from->start,(*to)->ESize,(*to)->compare);
	*to=NEW;
}

// Set Difference
void set_diff(Set *source,const Set_Node current_from,float (*compare)(const void *,const void *)){
	if(current_from==NULL)
		return;
	delete_in_set(source,current_from->data);
	set_diff(source,current_from->ll,compare);
	set_diff(source,current_from->rl,compare);
}

void set_difference(Set *source,const Set from){
	if((*source)->start==NULL)
		return;
	set_diff(source,from->start,(*source)->compare);
}