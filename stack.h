#include <string.h>
#include <stdbool.h>

typedef struct stack_node{
	void *data;
	struct stack *next;
}stack_node;

typedef stack_node * Stack_Node;

typedef struct stack{
	size_t ESize;
	int ctr;
	Stack_Node top;
	void (*display)(const void *);
}stack;

typedef stack * Stack;

void initialize_stack(Stack *obj,size_t size,void (*display)(const void *)){
	*obj=(Stack)malloc(sizeof(stack));
	(*obj)->top=NULL;
	(*obj)->ESize=size;
	(*obj)->ctr=0;
	(*obj)->display=display;
}

bool empty_stack(Stack obj){
	if(obj->top==NULL)
		return true;
	return false;
}

void push_to_stack(Stack *obj,const void *data){
	int l;
	if((*obj)->ESize==0)
		l=strlen(data)+1;
	else
		l=(*obj)->ESize;
	if((*obj)->top!=NULL){
		Stack_Node temp=(Stack_Node)malloc(sizeof(stack_node));
		temp->data=malloc(l);
		memcpy(temp->data,data,l);
		temp->next=(*obj)->top;
		(*obj)->top=temp;
	}
	else{
		(*obj)->top=(Stack_Node)malloc(sizeof(stack_node));
		(*obj)->top->data=malloc(l);
		memcpy((*obj)->top->data,data,l);
		(*obj)->top->next=NULL;
	}
	(*obj)->ctr++;
}

void * pop_from_stack(Stack *obj){
	if((*obj)->top==NULL)
		return NULL;
	void *ret=(*obj)->top->data;
	(*obj)->top=(*obj)->top->next;
	(*obj)->ctr--;
	return ret;
}

int search_in_stack(Stack obj,const void *data){
	if(obj->top==NULL)
		return -1;
	int ctr=0,l;
	Stack_Node trav=obj->top;
	if(obj->ESize==0)
		l=strlen(data)+1;
	else
		l=obj->ESize;
	while(trav!=NULL){
		if(memcmp(trav->data,data,l)==0)
			return ctr;
		trav=trav->next;
		ctr++;
	}
	return -1;
}

void print_stack_rec(Stack_Node top,bool *wt,void (*display)(const void *)){
	if(top==NULL)
		return;
	*wt=true;
	print_stack_rec(top->next,wt,display);
	display(top->data);
	printf(", ");
}

void print_stack(Stack obj){
	bool wt=false;
	printf("[ ");

	// Calling This will make Top at right most corner
	print_stack_rec(obj->top,&wt,obj->display);
	
	// Uncommenting This will make Top at Left Most corner
	// while(obj!=NULL){
	// 	wt=true;
	// 	display(obj->data);
	// 	printf(", ");
	// 	obj=obj->next;
	// }
	if(wt)
		printf("\b\b ]\n");
	else
		printf("]");
}

void * seek_stack(Stack obj){
	return obj->top->data;
}



// STACK as ARRAY
typedef struct stack_array{
	int top;
	int size;
	size_t ESize;
	void (*display)(const void *);
	void **arr;     // Double Pointer is because we have to make array of void pointer that can point to any element
}stack_array;

typedef stack_array * Stack_Array;

void initialize_stack_array(Stack_Array *st,int n,size_t size,void (*display)(const void *)){
	(*st)=(Stack_Array)malloc(sizeof(stack_array));
	(*st)->size=n;
	(*st)->top=-1;
	(*st)->ESize=size;
	(*st)->display=display;
	if(size==0)
		(*st)->arr=(void **)malloc(sizeof(string)*n);
	else
		(*st)->arr=(void **)malloc(size*n);
}

bool push_to_stack_array(Stack_Array *st,const void *data){
	if((*st)->top==(*st)->size-1)
		return false;
	else{
		int k,l;
		k=++((*st)->top);
		if((*st)->ESize==0)
			l=strlen(data)+1;
		else
			l=(*st)->ESize;
		(*st)->arr[k]=malloc(l);
		memcpy((*st)->arr[k],data,l);
		return true;
	}
}

void * pop_from_stack_array(Stack_Array *st){
	if((*st)->top==-1)
		return NULL;
	void *ptr=(*st)->arr[(*st)->top];
	free((*st)->arr[(*st)->top]);
	(*st)->top--;
	return ptr;
}

int search_in_stack_array(Stack_Array st,const void *data){
	if(st->top==-1)
		return -1;
	int i=st->top,ctr=0,l;
	if(st->ESize==0)
		l=strlen(data)+1;
	else
		l=st->ESize;
	while(i>=0){
		if(memcmp(st->arr[i],data,l)==0)
			return ctr;
		ctr++;
		i--; 
	}
	return -1;
}

void * seek_stack_array(Stack_Array st){
	return st->arr[st->top];
}

void print_stack_array(Stack_Array st){
	if(st->top==-1)
		printf("[ ]\n");
	else{
		int i=0,j=st->top;
		printf("[ ");
		while(i<=j){
			st->display(st->arr[i]);
			printf(", ");
			i++;
		}
		printf("\b\b ]\n");
	}
}