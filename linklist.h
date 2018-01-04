#include <string.h>
#include <stdbool.h>

typedef struct link_node{
	void *data;
	struct link_node *link;
}link_node;

typedef link_node * Link_Node;

typedef struct linklist{
	size_t ESize;
	int ctr;
	Link_Node start,end;
	void (*display)(const void *);
}linklist;

typedef linklist * LinkList;

void initialize_linklist(LinkList *ll,size_t size,void (*display)(const void *)){
	*ll=(LinkList)malloc(sizeof(linklist));
	(*ll)->ESize=size;
	(*ll)->ctr=0;
	(*ll)->display=display;
	(*ll)->start=NULL;
	(*ll)->end=NULL;
}

void insert_start_link(LinkList *ll,const void *data){
	int l;
	if((*ll)->ESize==0)
		l=strlen(data)+1;
	else
		l=(*ll)->ESize;
	if((*ll)->start==NULL){
		(*ll)->start=(Link_Node)malloc(sizeof(link_node));
		(*ll)->start->data=malloc(l);	
		memcpy((*ll)->start->data,data,l);
		(*ll)->start->link=NULL;
		(*ll)->end=(*ll)->start;
	}
	else{
		Link_Node temp=(Link_Node)malloc(sizeof(link_node));
		temp->data=malloc(l);
		memcpy(temp->data,data,l);
		temp->link=(*ll)->start;
		(*ll)->start=temp;
	}
	(*ll)->ctr++;
}

void insert_end_link(LinkList *ll,const void *data){
	int l;
	if((*ll)->ESize==0)
		l=strlen(data)+1;
	else
		l=(*ll)->ESize;
	if((*ll)->start==NULL){
		(*ll)->start=(Link_Node)malloc(sizeof(link_node));
		(*ll)->start->data=malloc(l);	
		memcpy((*ll)->start->data,data,l);
		(*ll)->start->link=NULL;
		(*ll)->end=(*ll)->start;
	}
	else{
		Link_Node temp=(Link_Node)malloc(sizeof(link_node));
		temp->data=malloc(l);
		memcpy(temp->data,data,l);
		temp->link=NULL;
		(*ll)->end->link=temp;
		(*ll)->end=temp;
	}	
	(*ll)->ctr++;
}

void * delete_start_link(LinkList *ll){
	if((*ll)->start==NULL)
		return NULL;
	void *ptr;
	if((*ll)->ctr==1){
		ptr=(*ll)->start->data;
		(*ll)->ctr=0;
		(*ll)->start=NULL;
		(*ll)->end=NULL;
		return ptr;
	}
	ptr=(*ll)->start->data;
	(*ll)->start=(*ll)->start->link;
	(*ll)->ctr--;
	return ptr;
}

void * delete_end_link(LinkList *ll){
	if((*ll)->start==NULL)
		return NULL;
	void *ptr;
	if((*ll)->ctr==1){
		ptr=(*ll)->start->data;
		(*ll)->ctr=0;
		(*ll)->start=NULL;
		(*ll)->end=NULL;
		return ptr;
	}
	Link_Node temp=(*ll)->start;
	while(temp->link!=(*ll)->end)
		temp=temp->link;
	ptr=(*ll)->end->data;
	(*ll)->end=temp;
	(*ll)->end->link=NULL;
	(*ll)->ctr--;
	return ptr;
}

void print_linklist(LinkList ll){
	printf("[ ");
	Link_Node temp=ll->start;
	if(temp==NULL){
		printf("]\n");
		return;
	}
	while(temp!=NULL){
		ll->display(temp->data);
		printf(", ");
		temp=temp->link;
	}
	printf("\b\b ]\n");
}

bool insert_at_index_link(LinkList *ll,const void *data,int i){
	if(i>(*ll)->ctr||i<0||(*ll)->ctr==0)
		return false;
	if(i==0)
		insert_start_link(ll,data);
	else if(i==(*ll)->ctr)
		insert_end_link(ll,data);
	else{
		Link_Node trav=(*ll)->start;
		Link_Node temp=(Link_Node)malloc(sizeof(link_node));
		int l;
		if((*ll)->ESize==0)
			l=strlen(data)+1;
		else
			l=(*ll)->ESize;
		temp->data=malloc(l);
		memcpy(temp->data,data,l);
		l=0;
		while(l<i-1){
			trav=trav->link;
			l++;
		}
		temp->link=trav->link;
		trav->link=temp;
		(*ll)->ctr++;
	}
	return true;
}

bool insert_after_data_link(LinkList *ll,const void *data,const void *search){
	if((*ll)->ctr==0)
		return false;
	int l,l1;
	if((*ll)->ESize==0){
		l=strlen(search)+1;
		l1=strlen(data)+1;
	}
	else{
		l=(*ll)->ESize;
		l1=l;
	}
	int i=1;
	Link_Node trav=(*ll)->start;
	while(trav!=NULL){
		if(memcmp(trav->data,search,l)==0)
			return insert_at_index_link(ll,data,i);
		trav=trav->link;
		i++;
	}
	return false;
}

bool insert_before_data_link(LinkList *ll,const void *data,const void *search){
	if((*ll)->ctr==0)
		return false;
	int l,l1;
	if((*ll)->ESize==0){
		l=strlen(search)+1;
		l1=strlen(data)+1;
	}
	else{
		l=(*ll)->ESize;
		l1=l;
	}
	int i=0;
	Link_Node trav=(*ll)->start;
	Link_Node end=(*ll)->end;
	while(trav!=end->link){
		if(memcmp(trav->data,search,l)==0)
			return insert_at_index_link(ll,data,i);
		trav=trav->link;
		i++;
	}
}

bool delete_index_link(LinkList *ll,int i){
	if(i>(*ll)->ctr||i<0||(*ll)->ctr==0)
		return false;
	if(i==0)
		delete_start_link(ll);
	else if(i==(*ll)->ctr-1)
		delete_end_link(ll);
	else{
		Link_Node trav=(*ll)->start;
		int l=0;
		while(l<i-1){
			trav=trav->link;
			l++;
		}
		trav->link=trav->link->link;
		(*ll)->ctr--;
	}
	return true;
}

bool delete_after_data_link(LinkList *ll,const void *data){
	if((*ll)->ctr==0)
		return false;
	int l;
	if((*ll)->ESize==0)
		l=strlen(data)+1;
	else
		l=(*ll)->ESize;
	int i=1;
	Link_Node trav=(*ll)->start;
	Link_Node end=(*ll)->end;
	while(trav!=end){
		if(memcmp(trav->data,data,l)==0)
			return delete_index_link(ll,i);
		trav=trav->link;
		i++;
	}
	return false;
}

bool delete_before_data_link(LinkList *ll,const void *data){
	if((*ll)->ctr==0)
		return false;
	int l;
	if((*ll)->ESize==0)
		l=strlen(data)+1;
	else
		l=(*ll)->ESize;
	int i=0;
	Link_Node trav=(*ll)->start;
	if(memcmp(trav->data,data,l)==0)
		return false;
	trav=trav->link;
	Link_Node end=(*ll)->end;
	while(trav!=end->link){
		if(memcmp(trav->data,data,l)==0)
			return delete_index_link(ll,i);
		trav=trav->link;
		i++;
	}
	return false;
}