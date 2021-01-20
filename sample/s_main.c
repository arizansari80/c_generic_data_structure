/*
Created on: 16-Jan-2021
 Author: arizansari80
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sets.h"
#include "../c_string.h"

typedef struct student {
	int rollNumber;
	string name;
}student;

long double student_compare(const void *P1, const void *P2)
{
	student p1 = *(student *)P1;
	student p2 = *(student *)P2;
	if (p1.rollNumber == p2.rollNumber)
		return 0;
	return p1.rollNumber - p2.rollNumber;
}

void student_display(const void *P)
{
	student p = *(student *)P;
	puts("");
	printf("Name : %s",p.name);
	printf("Roll No. : %d", p.rollNumber);
	puts("");
}

void student_clean(const void *P)
{
	student *p = (student *)P;
	if (p->name != NULL)
	{
		free(p->name);
		p->name = NULL;
	}
}

extern const GLOBAL_STRING_OBJECT String;	// For Using String Library Functions
extern const GLOBAL_SET_OBJECT Set;			// For Using Set Library Functions

int main(int argc, char *args[]) {
	set structSet;
	structSet = Set.getSet(sizeof(student), student_compare, student_display);
	int startRoll = 123;
	string name;
	string n_name;
	for (int i = 0; i < 3; i++) {
		printf("Enter Name : ");
		name = String.getString();
		student *s = malloc(sizeof(student));
		if (s == 0)
			return 1;
		s->rollNumber = startRoll++;
		s->name = malloc(sizeof(char) * strlen(name));
		n_name = s->name;
		if (s->name == 0)
			return 1;
		strcpy(s->name,name);
		free(name);
		Set.addInSet(&structSet,s);
		free(s->name);
		s->name = NULL;
		free(s);
		s = NULL;
	}

	Set.printSet(structSet);
	Set.clearSet(&structSet,student_clean);
	puts(n_name);
	return 0;
}
