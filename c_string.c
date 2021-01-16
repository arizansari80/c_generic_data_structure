#include "c_string.h"

// Check For Vowel
static bool isvowel(const char ch)
{
    if (isalpha(ch))
        switch (ch)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return true;
        default:
            return false;
        }
    else
        return false;
}

// Returning Substring of String
static string substring(const string source, const int start, int n)
{
    int l = strlen(source);
    if (start + n > l)
        n = l - start;
    string ret = (string)malloc(n + 1);
    strncpy(ret, source + start, n);
    ret[n] = NULL_CHAR;
    return ret;
}

// Giving String in C (Essence of Java String)
static string getstring()
{
    char ch[MAX_STR_SIZE];
    scanf("%[^\n]s", ch);
    getchar();
    string ret = substring(ch,0,strlen(ch) + 1);
    return ret;
}

// Checking for number of occurrences of Particular Character in String
static int occur(const string s, const int k)
{
    int ctr = 0;
    for (int i = 0; s[i] != NULL_CHAR; i++)
        if (s[i] == k)
            ctr++;
    return ctr;
}

// Splitting String according to given Delimeter and Returning an Array of String (Essence of Java String.split() method)
static string *split_array(const string s, const string exp, int *size)
{
    *size = occur(s, exp[0]) + 1;
    string *rstr = (string *)malloc(sizeof(string) * (*size + 1));
    int i = 0;
    *(rstr + i) = strtok(s, exp);
    while (*(rstr + i) != NULL)
    {
        i++;
        *(rstr + i) = strtok(NULL, exp);
    }
    return rstr;
}

static void insert_split(node_split **s, node_split **e, string str)
{
    int l = strlen(str);
    if (*s != NULL)
    {
        node_split *t = (node_split *)malloc(sizeof(node_split));
        t->s = (string)malloc(l);
        strcpy(t->s, str);
        t->l = NULL;
        (*e)->l = t;
        *e = (*e)->l;
    }
    else
    {
        *s = (node_split *)malloc(sizeof(node_split) + l);
        (*s)->s = (string)malloc(l);
        strcpy((*s)->s, str);
        (*s)->l = NULL;
        *e = *s;
    }
}

// Splitting String as per expression and returning a link list contains splitted parts
static node_split *split_link(const string str, const string exp, node_split **e)
{
    node_split *s = NULL;
    *e = NULL;
    string ch;
    ch = strtok(str, exp);
    while (ch != NULL)
    {
        insert_split(&s, e, ch);
        ch = strtok(NULL, exp);
    }
    return s;
}

// Trimming beginning of string for space
static string trimleft(string str)
{
    int i = 0;
    while (str[i] == SPACE_CHAR && str[i] != NULL_CHAR)
        i++;
    return str + i;
}

// Trimming end of string for space
static string trimright(string str)
{
    int i = strlen(str) - 1;
    while (str[i] == SPACE_CHAR && i >= 0)
        i--;
    str[i] = NULL_CHAR;
    return str;
}

// Trimming Beginning and End of String for Spaces
static string trim(string str)
{
    str = trimleft(str);
    str = trimright(str);
    return str;
}

// Trimming beginning of string for space
static string trimleftforchar(string str, int ch)
{
    int i = 0;
    while (str[i] == ch && str[i] != NULL_CHAR)
        i++;
    return str + i;
}

// Return Binary String Of Primitive Data Types
static string tobinarystring(const void *data, size_t size)
{
    string ret = (string)malloc(8 * size);
    int i = 0, k = 0;
    unsigned char ch2 = 1 << 7;
    unsigned char ch1;
    while (k < size)
    {
        ch1 = *((char *)data + (size - (k + 1)));
        for (int j = 0; j < 8; j++, i++)
        {
            ret[i] = ch1 & ch2 ? 49 : 48;
            ch1 <<= 1;
        }
        k++;
    }
    ret[i] = NULL_CHAR;
    ret = trimleftforchar(ret, '0');
    return ret;
}

// Return Index Of String in String if
static int indexof(const string str, const string key)
{
    char *ch = strstr(str, key);
    if (ch != NULL)
        return ch - str;
    return -1;
}

// Return Indexes of All Occurrences of String in String
static int *indexofall(const string str, const string key, int *size)
{
    *size = 0;
    char *ch = strstr(str, key);
    if (ch != NULL)
    {
        int *ptr1, *ptr2;
        int k = 0;
        ptr1 = (int *)malloc(sizeof(int) * strlen(str));
        *(ptr1 + k) = ch - str;
        while (ch != NULL)
        {
            ch = strstr(ch + 1, key);
            k++;
            *(ptr1 + k) = ch - str;
        }
        *size = k;
        ptr2 = (int *)malloc(sizeof(int) * k);
        for (int i = 0; i < k; i++)
        	ptr2[i] = ptr1[i];
        free(ptr1);
        return ptr2;
    }
    return NULL;
}

// Return Last Index Of String in String if
static int lastindexof(const string str, const string key)
{
	string temp = (string)malloc(strlen(str) + 1);
	strcpy(temp,str);
	char ch = key[0];
	char *lIndCh = strrchr(temp,ch);
	if (lIndCh == NULL)
	{
		free(temp);
		return -1;
	}

	int lenKey = strlen(key);
	while (lIndCh != NULL)
	{
		if (strlen(lIndCh) < lenKey)
			continue;
		if (strncmp(lIndCh,key,lenKey) == 0)
		{
			int retVal = lIndCh - temp;
			free(temp);
			return retVal;
		}
		temp[lIndCh - temp] = NULL_CHAR;
		lIndCh = strrchr(temp,ch);
	}
	free(temp);
	return -1;
}

// Return Index Of Character in String if
static int indexofchar(const string str, const int key)
{
    char *ch = strchr(str, key);
    if (ch != NULL)
        return ch - str;
    return -1;
}

// Return Last Index Of Char in String
static int lastindexofchar(const string str, const int key)
{
    char *ch = strrchr(str, key);
    if (ch != NULL)
        return ch - str;
    return -1;
}

// Return Indexes of All Occurrences of Character in String
static int *indexofallchar(const string str, const int key, int *size)
{
    *size = 0;
    char *ch = strchr(str, key);
    if (ch != NULL)
    {
        int *ptr1, *ptr2;
        int k = 0;
        ptr1 = (int *)malloc(sizeof(int) * strlen(str));
        *(ptr1 + k) = ch - str;
        while (ch != NULL)
        {
            ch = strchr(ch + 1, key);
            k++;
            *(ptr1 + k) = ch - str;
        }
        *size = k;
        ptr2 = (int *)malloc(sizeof(int) * k);
        for (int i = 0; i < k; i++)
        	ptr2[i] = ptr1[i];
        free(ptr1);
        return ptr2;
    }
    return NULL;
}

// Return Index Of String in String From Offset (Included)
static int indexoffrom(const string str, const string key, const int offset)
{
	if (offset <= 0)
		return indexof(str,key);
    char *ch = strstr(str + offset, key);
    if (ch != NULL)
        return ch - str;
    return -1;
}

// Return Index Of String in String Upto maxset (Included)
static int indexofupto(const string str, const string key, const int maxset)
{
	if (maxset >= strlen(str))
		return indexof(str,key);
    char *ch = strstr(str, key);
    if (ch != NULL && (ch - str) <= maxset)
        return ch - str;
    return -1;
}

// Return Index Of String in String In Between offset, maxset (Both Included)
static int indexofbetween(const string str, const string key, const int offset, const int maxset)
{
	if (offset <= 0)
		return indexofupto(str,key,maxset);
	int ind = indexoffrom(str,key,offset);
	return ind <= maxset ? ind : -1;
}

// Return Last Index Of String in String From Offset (Included)
static int lastindexoffrom(const string str, const string key, const int offset)
{
    int ind = lastindexof(str + (offset < 0 ? 0 : offset),key);
    return ind < offset ? -1 : ind;
}

// Return Last Index Of String in String Upto maxset (Included)
static int lastindexofupto(const string str, const string key, const int maxset)
{
	if (maxset >= strlen(str))
		return lastindexof(str,key);
    string temp = (string)malloc(maxset + 1);
    strncpy(temp,str,maxset);
    temp[maxset] = NULL_CHAR;
    int ind = lastindexof(temp,key);
    free(temp);
    return ind;
}

// Return Last Index Of String in String In Between offset, maxset (Both Included)
static int lastindexofbetween(const string str, const string key, const int offset, const int maxset)
{
	if (offset <= 0)
		return lastindexofupto(str,key,maxset);
	string temp = (string)malloc(maxset - offset + 2);
	strncpy(temp,str + offset,maxset - offset + 1);
	temp[maxset - offset + 1] = NULL_CHAR;
	int ind =  lastindexof(temp,key);
	free(temp);
	return ind != -1 ? ind + offset : ind;
}

// Return All Index Of String in String From Offset (Included)
static int  *allindexoffrom(const string str, const string key, const int offset, int *size)
{
	if (offset <= 0)
		return indexofall(str,key,size);
    int *ind =  indexofall(str + offset,key,size);
    for (int i = 0; i < *size; i++)
    	ind[i] += offset;
    return ind;
}

// Return All Index Of String in String Upto maxset (Included)
static int *allindexofupto(const string str, const string key, const int maxset, int *size)
{
	if (maxset >= strlen(str))
		return indexofall(str,key,size);
	string temp = (string)malloc(maxset + 1);
	strncpy(temp,str,maxset);
	temp[maxset] = NULL_CHAR;
	int *ind = indexofall(temp,key,size);
	free(temp);
	return ind;
}

// Return All Index Of String in String In Between offset, maxset (Both Included)
static int *allindexofbetween(const string str, const string key, const int offset, const int maxset, int *size)
{
	if (offset <= 0)
		return allindexofupto(str,key,maxset,size);
	string temp = (string)malloc(maxset - offset + 2);
	strncpy(temp,str + offset,maxset - offset + 1);
	temp[maxset - offset + 1] = NULL_CHAR;
	int *ind =  indexofall(temp,key,size);
	free(temp);
	for (int i = 0; i < *size; i++)
		ind[i] += offset;
	return ind;
}

// Return Index Of char in String From Offset (Included)
static int indexofcharfrom(const string str, const int key, const int offset)
{
	if (offset <= 0)
		return indexofchar(str,key);
    char *ch = strchr(str + offset, key);
    if (ch != NULL)
        return ch - str;
    return -1;
}

// Return Index Of char in String Upto maxset (Included)
static int indexofcharupto(const string str, const int key, const int maxset)
{
	if (maxset >= strlen(str))
		return indexofchar(str,key);
    char *ch = strchr(str, key);
    if (ch != NULL && (ch - str) <= maxset)
        return ch - str;
    return -1;
}

// Return Index Of char in String in between offset, maxset (Both Included)
static int indexofcharbetween(const string str, const int key, const int offset, const int maxset)
{
	if (offset <= 0)
		return indexofcharupto(str,key,maxset);
	int ind =  indexofcharfrom(str,key,offset);
	return ind <= maxset ? ind : -1;
}

// Return Last Index Of char in String From Offset (Included)
static int lastindexofcharfrom(const string str, const int key, const int offset)
{
	if (offset <= 0)
		return lastindexofchar(str,key);
    char *ch = strrchr(str + offset, key);
    if (ch != NULL)
        return ch - str;
    return -1;
}

// Return Last Index Of char in String Upto maxset (Included)
static int lastindexofcharupto(const string str, const int key, const int maxset)
{
	if (maxset >= strlen(str))
		return lastindexofchar(str,key);
	int retVal = -1;
	string temp = (string)malloc(maxset + 1);
	strncpy(temp,str,maxset);
    char *ch = strrchr(temp, key);
    if (ch != NULL && (ch - temp) <= maxset)
        retVal =  ch - temp;
    free(temp);
    return retVal;
}

// Return Last Index Of char in String in between offset, maxset (Both Included)
static int lastindexofcharbetween(const string str, const int key, const int offset, const int maxset)
{
	if (offset <= 0)
		return lastindexofcharupto(str,key,maxset);
	string temp = (string)malloc(maxset - offset + 2);
	strncpy(temp,str + offset,maxset - offset + 1);
	temp[maxset - offset + 1] = NULL_CHAR;
	int ind =  lastindexofchar(temp,key);
	free(temp);
	return ind != -1 ? ind + offset : ind;
}

// Return Index Of char in String From Offset (Included)
static int *allindexofcharfrom(const string str, const int key, const int offset, int *size)
{
    return indexofallchar(str + (offset < 0 ? 0 : offset),key,size);
}

// Return Index Of char in String Upto maxset (Included)
static int *allindexofcharupto(const string str, const int key, const int maxset, int *size)
{
	if (maxset >= strlen(str))
		return indexofallchar(str,key,size);
    string temp = (string)malloc(maxset + 1);
    strncpy(temp,str,maxset);
    temp[maxset] = NULL_CHAR;
    int *ind = indexofallchar(temp,key,size);
    free(temp);
    return ind;
}

// Return Index Of char in String in between offset, maxset (Both Included)
static int *allindexofcharbetween(const string str, const int key, const int offset, const int maxset, int *size)
{
	if (offset <= 0)
		return allindexofcharupto(str,key,maxset,size);
	string temp = (string)malloc(maxset - offset + 2);
	strncpy(temp,str + offset,maxset - offset + 1);
	temp[maxset - offset + 1] = NULL_CHAR;
	int *ind =  indexofallchar(temp,key,size);
	free(temp);
	for (int i = 0; i < *size; i++)
		ind[i] += offset;
	return ind;
}

const GLOBAL_STRING_OBJECT String =
{
    getstring,
    substring,
    trimleft,
    trimright,
    trim,
    tobinarystring,
    occur,
    indexof,
    indexofall,
    lastindexof,
    indexofchar,
    lastindexofchar,
    indexofallchar,
    split_array,
    //split_link,
	indexoffrom,
	indexofupto,
	indexofbetween,
	lastindexoffrom,
	lastindexofupto,
	lastindexofbetween,
	allindexoffrom,
	allindexofupto,
	allindexofbetween,
	indexofcharfrom,
	indexofcharupto,
	indexofcharbetween,
	lastindexofcharfrom,
	lastindexofcharupto,
	lastindexofcharbetween,
	allindexofcharfrom,
	allindexofcharupto,
	allindexofcharbetween
};
