#ifndef C_STRING_H_INCLUDED
#define C_STRING_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

#include "util_def.h"

// Splitting String and Return as a Link List
typedef struct node_split
{
    struct node_split *l;
    string s;
} node_split;

typedef struct
{
	string (*getString)();
	string (*subString)(const string source, const int start_index, int num);
	string (*trimLeft)(string source);
	string (*trimRight)(string source);
	string (*trim)(string source);
	string (*toBinaryString)(const void *data, size_t size);

	int (*numberOfOccurrences)(const string source, const int ch);
	int (*indexOf)(const string source, const string key);
	int * (*allIndexOf)(const string source, const string key, int *size);
	int (*lastIndexOf)(const string source, const string key);
	int (*indexOfChar)(const string source, const int ch);
	int (*lastIndexOfChar)(const string source, const int ch);
	int * (*allIndexOfChar)(const string source, const int ch, int *size);

	string * (*split)(const string source, const string tokens, int *size);
	//node_split *(*splitInLink)(const string, const string, node_split **);

	// Start Including New Function From Here
	int (*indexOfFrom)(const string source, const string key, const int from);
	int (*indexOfUpto)(const string source, const string key, const int upto);
	int (*indexOfBetween)(const string source, const string key, const int from, const int upto);
	int (*lastIndexOfFrom)(const string source, const string key, const int from);
	int (*lastIndexOfUpto)(const string source, const string key, const int upto);
	int (*lastIndexOfBetween)(const string source, const string key, const int from, const int upto);
	int * (*allIndexOfFrom)(const string source, const string key, const int from, int *size);
	int * (*allIndexOfUpto)(const string source, const string key, const int upto, int *size);
	int * (*allIndexOfBetween)(const string source, const string key, const int from, const int upto, int *size);

	int (*indexOfCharFrom)(const string source, const int ch, const int from);
	int (*indexOfCharUpto)(const string source, const int ch, const int upto);
	int (*indexOfCharBetween)(const string source, const int ch, const int from, const int upto);
	int (*lastIndexOfCharFrom)(const string source, const int ch, const int from);
	int (*lastIndexOfCharUpto)(const string source, const int ch, const int upto);
	int (*lastIndexOfCharBetween)(const string source, const int ch, const int from, const int upto);
	int * (*allIndexOfCharFrom)(const string source, const int ch, const int from, int *size);
	int * (*allIndexOfCharUpto)(const string source, const int ch, const int upto, int *size);
	int * (*allIndexOfCharBetween)(const string source, const int ch, const int from, const int upto, int *size);
} GLOBAL_STRING_OBJECT;

#endif // C_STRING_H_INCLUDED
