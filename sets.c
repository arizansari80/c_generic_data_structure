#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <mystrings.h>
#include <sets.h>
#define endl puts("")

typedef struct cord{
	int x;
	int y;
}cord;

float compare(const void *p1,const void *p2){
	// return *(int *)p1-*(int *)p2;
	// return strcmp(p1,p2);
	cord X=*(cord *)p1;
	cord Y=*(cord *)p2;
	if(X.x==Y.x)
		return X.y-Y.y;
	return X.x-Y.x;
}

void display(const void *data){
	cord X=*(cord *)data;
	// printf("%d",*(int *)data);
	printf("(%d,%d)",X.x,X.y);
	// fputs(data,stdout);
}

int main(int argc,char **argv){
	Set s=NULL,w=NULL;
	initialize_set(&s,sizeof(cord),compare,display);
	initialize_set(&w,sizeof(cord),compare,display);
	cord a;
	a.x=1;
	a.y=1;
	while(a.x!=0&&a.y!=0){
		scanf("%d%d",&a.x,&a.y);
		add_in_set(&s,&a);
	}
	a.x=1;
	a.y=1;
	while(a.x!=0&&a.y!=0){
		scanf("%d%d",&a.x,&a.y);
		add_in_set(&w,&a);
	}
	printf("\nSet S\n");
	print_set(s);
	printf("\nSet W\n");
	print_set(w);
	printf("S Union W\n");
	set_union(&s,w);
	printf("\nSet S\n");
	print_set(s);
	printf("\nSet W\n");
	print_set(w);
	printf("S Intersection W\n");
	set_intersection(&s,w);
	printf("\nSet S\n");
	print_set(s);
	printf("\nSet W\n");
	print_set(w);
	printf("S - w\n");
	set_difference(&s,w);
	printf("\nSet S\n");
	print_set(s);
	printf("\nSet W\n");
	print_set(w);
	return 0;
}