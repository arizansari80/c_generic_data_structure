#include <string.h>
#include <stdbool.h>

// Declaring Set structure;
typedef struct set{
	void * data;
	struct set *ll;
	struct set *rl;
}set;

typedef set * Set;

// Adding Unique Element in Set;
bool add_in_set(Set *start,const void *data,size_t size,float (*compare)(const void *,const void *)){
	Set temp=(Set)malloc(sizeof(set));
	temp->data=malloc(size);
	memcpy(temp->data,data,size);
	temp->rl=NULL;
	temp->ll=NULL;
	if(*start!=NULL){
		Set travel=*start;
		float r;
		while(1){
			r=compare(travel->data,temp->data);
			if(r==0){
				free(temp->data);
				free(temp);
				return false;
			}
			else if(r>0)
				if(travel->ll==NULL){
					travel->ll=temp;
					return true;
				}
				else
					travel=travel->ll;
			else
				if(travel->rl==NULL){
					travel->rl=temp;
					return true;
				}
				else
					travel=travel->rl;
		}
	}
	else{
		*start=temp;
		return true;
	}
}

// Traversing Set Data Structure;
void print_set_inorder(Set current_start,void (*display)(const void *),bool *wp){
	if(current_start==NULL)
		return;
	*wp=true;
	print_set_inorder(current_start->ll,display,wp);
	display(current_start->data);
	printf(", ");
	print_set_inorder(current_start->rl,display,wp);
}

void print_set(Set start,void (*display)(const void *)){
	bool wp=false;
	printf("[ ");
	print_set_inorder(start,display,&wp);
	if(wp)
		printf("\b\b ]\n");
	else
		printf("]\n");
}

// Returning Set as an Array

// Search Operation in Set
bool search_set(const Set in,const void *key,float (*compare)(const void *,const void *)){
	if(in==NULL)
		return false;
	int res=compare(in->data,key);
	if(res==0)
		return true;
	else if(res>0)
		return search_set(in->ll,key,compare);
	else
		return search_set(in->rl,key,compare);
}

// Delete In Sets This Operation is Most Complicated One

void detect_child(Set parent,bool *lc,bool *rc){
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

void minchild(Set *parent,Set *child){
	if((*child)->ll==NULL)
		return;
	*parent=(*parent)->ll;
	*child=(*child)->ll;
	minchild(parent,child);
}

bool delete_root(Set *in){
	bool l,r;
	detect_child(*in,&l,&r);
	if(!l&&!r){
		*in=NULL;
		return true;
	}
	if(!l&&r){
		*in=(*in)->rl;
		return true;
	}
	if(l&&!r){
		*in=(*in)->ll;
		return true;
	}
	Set parent,child;
	parent=(*in)->rl;
	child=parent->ll;
	if(child==NULL){
		(*in)->data=parent->data;
		(*in)->rl=parent->rl;
		return true;
	}
	else if(child->ll==NULL){
		(*in)->data=(*in)->rl->ll->data;
		(*in)->rl->ll=(*in)->rl->ll->rl;
		return true;
	}
	else{
		minchild(&parent,&child);
		(*in)->data=child->data;
		parent->ll=child->rl;
		return true;
	}
}

bool delete_child(Set parent,Set child,bool which){
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
	Set p=child;
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

bool delete_in_set(Set *in,void *key,float (*compare)(const void *,const void *)){
	if(*in==NULL)
		return false;
	float res=compare((*in)->data,key);
	if(res==0)
		return delete_root(in);
	Set parent=*in,child;
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
		res=compare(child->data,key);
		if(res==0)
			return delete_child(parent,child,which);
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
void set_union(Set *to,const Set current_from,size_t size,float (*compare)(const void *,const void *)){
	if(current_from==NULL)
		return;
	set_union(to,current_from->ll,size,compare);
	if(size==0)//Pass Size=0 for string as Set element
		add_in_set(to,current_from->data,strlen(current_from->data)+1,compare);
	else
		add_in_set(to,current_from->data,size,compare);
	set_union(to,current_from->rl,size,compare);
}

// Intersection Operation
Set set_intersect(Set to,const Set current_from,size_t size,float (*compare)(const void *,const void *)){
	static Set NEW=NULL;
	if(current_from==NULL)
		return NEW;
	if(search_set(to,current_from->data,compare))
		if(size==0)//Pass Size=0 for string as Set element
			add_in_set(&NEW,current_from->data,strlen(current_from->data)+1,compare);
		else
			add_in_set(&NEW,current_from->data,size,compare);
	set_intersect(to,current_from->ll,size,compare);
	set_intersect(to,current_from->rl,size,compare);
}

void set_intersection(Set *to,const Set from,size_t size,float (*compare)(const void *,const void *)){
	*to=set_intersect(*to,from,size,compare);
}

// Set Difference
void set_difference(Set *source,const Set current_from,float (*compare)(const void *,const void *)){
	if(*source==NULL)
		return;
	if(current_from==NULL)
		return;
	delete_in_set(source,current_from->data,compare);
	set_difference(source,current_from->ll,compare);
	set_difference(source,current_from->rl,compare);
}