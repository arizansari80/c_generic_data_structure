#include <string.h>
#include <stdbool.h>

// Vector as array
typedef struct vector_array{
	int ESize;
	int size;
	int ctr;
	void **arr;
}vector_array;

typedef vector_array * Vector_Array;

void initialize_vector(vector_array *v,size_t ES){
	v->size=10;
	v->ctr=0;
	if(ES==0){
		v->ESize=0;
		v->arr=(void **)malloc(sizeof(string)*v->size);
	}
	else{
		v->ESize=ES;
		v->arr=(void **)malloc(ES*v->size);
	}
}

void insert_vector(vector_array *v,const void *data){
	if(v->ctr==v->size){
		v->size+=10;
		if(v->ESize==0)
			v->arr=(void **)realloc(v->arr,sizeof(string)*v->size);
		else
			v->arr=(void **)realloc(v->arr,v->ESize*v->size);
	}
	int l;
	if(v->ESize==0)
		l=strlen(data)+1;
	else
		l=v->ESize;
	v->arr[v->ctr]=malloc(l);
	memcpy(v->arr[v->ctr],data,l);
	v->ctr++;
}