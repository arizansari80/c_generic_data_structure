#include <string.h>
#include <stdbool.h>

typedef struct linklist{
	void *data;
	struct linklist *link;
	struct linklist *end;
}linklist;

typedef linklist * LinkList;

void insert_start(LinkList *st,const void *data,size_t size){
	int l;
	if(*st==NULL){
		*st=(LinkList)malloc(sizeof(linklist));
		if(size==0)
			l=strlen(data)+1;
		else
			l=size;
		(*st)->data=malloc(l);	
		memcpy((*st)->data,data,l);
		(*st)->end=*st;
		(*st)->link=NULL;
	}
	else{
		LinkList temp=(LinkList)malloc(sizeof(linklist));
		if(size==0)
			l=strlen(data)+1;
		else
			l=size;
		temp->data=malloc(l);
		temp->link=*st;
		temp->end=NULL;
		memcpy(temp->data,data,l);
		*st=temp;
	}
}

void insert_end(LinkList *st,const void *data,size_t size){
	int l;
	if(*st==NULL){
		*st=(LinkList)malloc(sizeof(linklist));
		if(size==0)
			l=strlen(data)+1;
		else
			l=size;
		(*st)->data=malloc(l);	
		(*st)->end=*st;
		(*st)->link=NULL;
		memcpy((*st)->data,data,l);
	}
	else{
		LinkList temp=(LinkList)malloc(sizeof(linklist));
		if(size==0)
			l=strlen(data)+1;
		else
			l=size;
		temp->data=malloc(l);	
		temp->link=NULL;
		temp->end=NULL;
		memcpy(temp->data,data,l);
		(*st)->end->link=temp;
		(*st)->end=temp;
	}	
}

void * delete_start(LinkList *st){
	LinkList temp=*st;
	*st=temp->link;
	(*st)->end=temp->end;
	return temp->data;
}

void * delete_end(LinkList *st){
	LinkList temp=*st;
	while(temp->link!=(*st)->end)
		temp=temp->link;
	void * ptr=(*st)->end->data;
	(*st)->end=temp;
	(*st)->end->link=NULL;
	return ptr;
}

void print_linklist(LinkList ll,void (*display)(const void *)){
	printf("[ ");
	LinkList temp=ll;
	if(temp==NULL){
		printf("]\n");
		return;
	}
	while(temp!=NULL){
		display(temp->data);
		printf(", ");
		temp=temp->link;
	}
	printf("\b\b ]\n");
}