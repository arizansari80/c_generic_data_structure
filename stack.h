#include <string.h>
#include <stdbool.h>

typedef struct stack{
	void *data;
	struct stack *next;
}stack;

typedef stack * Stack;

bool empty_stack(Stack top){
	if(top==NULL)
		return true;
	return false;
}

void push_to_stack(Stack *top,const void *data,size_t size){
	int l;
	if(size==0)
		l=strlen(data)+1;
	else
		l=size;
	if(*top!=NULL){
		Stack temp=(Stack)malloc(sizeof(stack));
		temp->data=malloc(l);
		memcpy(temp->data,data,l);
		temp->next=*top;
		*top=temp;
	}
	else{
		*top=(Stack)malloc(sizeof(stack));
		(*top)->data=malloc(l);
		memcpy((*top)->data,data,l);
		(*top)->next=NULL;
	}
}

void * pop_from_stack(Stack *top){
	if(*top==NULL)
		return NULL;
	void *ret=(*top)->data;
	*top=(*top)->next;
	return ret;
}

int search_in_stack(Stack top,const void *data,size_t size){
	if(top==NULL)
		return -1;
	int ctr=0;
	while(top!=NULL){
		if(memcmp(top->data,data,size)==0)
			return ctr;
		top=top->next;
		ctr++;
	}
	return -1;
}

void print_stack_rec(Stack top,bool *wt,void (*display)(const void *)){
	if(top==NULL)
		return;
	*wt=true;
	print_stack_rec(top->next,wt,display);
	display(top->data);
	printf(", ");
}

void print_stack(Stack top,void (*display)(const void *)){
	bool wt=false;
	printf("[ ");

	// Calling This will make Top at right most corner
	print_stack_rec(top,&wt,display);
	
	// Uncommenting This will make Top at Left Most corner
	// while(top!=NULL){
	// 	wt=true;
	// 	display(top->data);
	// 	printf(", ");
	// 	top=top->next;
	// }
	if(wt)
		printf("\b\b ]\n");
	else
		printf("]");
}

void * seek_stack(Stack top){
	return top->data;
}

// STACK as ARRAY
typedef struct stack_array{
	int top;
	int size;
	int ESize;
	void **arr;     // Double Pointer is because we have to make array of void pointer that can point to any element
}stack_array;

typedef stack_array * Stack_Array;

void initialize_stack(Stack_Array *st,int n,size_t size){
	(*st)=(Stack_Array)malloc(sizeof(stack_array));
	(*st)->size=n;
	(*st)->top=-1;
	(*st)->ESize=size;
	if(size==0)
		(*st)->arr=(void **)malloc(sizeof(string)*n);
	else
		(*st)->arr=(void **)malloc(size*n);
}

bool push_stack_array(Stack_Array *st,const void *data){
	if((*st)->top==(*st)->size-1)
		return false;
	else{
		(*st)->top++;
		if((*st)->ESize==0){
			int l=strlen(data);
			(*st)->arr[(*st)->top]=malloc(l+1);
			memcpy((*st)->arr[(*st)->top],data,l+1);
		}
		else{
			(*st)->arr[(*st)->top]=malloc((*st)->ESize);
			memcpy((*st)->arr[(*st)->top],data,(*st)->ESize);
		}
		return true;
	}
}

void * pop_stack_array(Stack_Array *st){
	if((*st)->top==-1)
		return NULL;
	void *ptr=(*st)->arr[(*st)->top];
	free((*st)->arr[(*st)->top]);
	(*st)->top--;
	return ptr;
}

int search_stack_array(Stack_Array st,const void *data){
	if(st->top==-1)
		return -1;
	int i=st->top,ctr=0;
	if(st->ESize==0)
		while(i>=0){
			if(memcmp(st->arr[i],data,strlen(data))==0)
				return ctr;
			ctr++;
			i--; 
		}
	else
		while(i>=0){
			if(memcmp(st->arr[i],data,st->ESize)==0)
				return ctr;
			ctr++;
			i--; 
		}
	return -1;
}

void * seek_stack_array(Stack_Array st){
	return st->arr[st->top];
}

void print_stack_array(Stack_Array st,void (*display)(const void *)){
	if(st->top==-1)
		printf("[ ]\n");
	else{
		int i=0,j=st->top;
		printf("[ ");
		while(i<=j){
			display(st->arr[i]);
			printf(", ");
			i++;
		}
		printf("\b\b ]\n");
	}
}