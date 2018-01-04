#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef char * string;

// Check For Vowel
bool isvowel(char ch){
	if(isalpha(ch))
		switch(ch){
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U': return true;
			default : return false;
		}
	else
		return false;
}

// Giving String in C (Essence of Java String)
string givemestr(){
	string ch=(string)malloc(1024);
	scanf("%[^\n]s",ch);
	getchar();
	string ret=(string)realloc(ch,strlen(ch)+1);
	return ret;
}

// Checking for occurrence of Particular Character in String
int occur(string s,int k){
	int ctr=0;
	for(int i=0;s[i]!='\0';i++)
		if(s[i]==k)
			ctr++;
	return ctr;
}	

// Splitting String according to given Delimeter and Returning an Array of String (Essence of Java String.split() method)
string * split_array(string s,string exp,int *size){
	*size=occur(s,exp[0])+1;
	string *rstr=(string *)malloc(sizeof(string)*(*size+1));
	int i=0;
	*(rstr+i)=strtok(s,exp);
	while(*(rstr+i)!=NULL){
		i++;
		*(rstr+i)=strtok(NULL,exp);
	}
	return rstr;
}

// Splitting String and Return as a Link List
typedef struct node_split{
	struct node_split *l;
	string s;
}node_split;

void insert_split(node_split **s,node_split **e,string str){
	int l=strlen(str);
	if(*s!=NULL){
		node_split *t=(node_split *)malloc(sizeof(node_split));
		t->s=(string)malloc(l);
		strcpy(t->s,str);
		t->l=NULL;
		(*e)->l=t;
		*e=(*e)->l;
	}
	else{
		*s=(node_split *)malloc(sizeof(node_split)+l);
		(*s)->s=(string)malloc(l);
		strcpy((*s)->s,str);
		(*s)->l=NULL;
		*e=*s;
	}
}

node_split * split_link(string str,string exp,node_split **e){
	node_split *s=NULL;
	*e=NULL;
	string ch;
	ch=strtok(str,exp);
	while(ch!=NULL){
		insert_split(&s,e,ch);
		ch=strtok(NULL,exp);
	}
	return s;
}

// Returning Substring of String
string substring(string source,int start,int n){
	int l=strlen(source);
	if(source+n>l)
		n=l-start;
	string ret=(string)malloc(n+1);
	strncpy(ret,source+start,n);
	ret[n]='\0';
	return ret;
}

string trimleft(string str,int ch){
	int i=0;
	while(str[i]==ch&&str[i]!='\0')
		i++;
	return str+i;
}

string trim(string str){
	int i=0,j=strlen(str);
	j--;
	while(str[i]==32&&str[j]==32)
		i++,j--;
	while(str[i]==32)
		i++;
	while(str[j]==32)
		j--;
	str[j+1]='\0';
	return str+i;
}
// Return Binary String Of Primitive Data Types
string tobinarystring(void *data,size_t size){
	string ret=(string)malloc(8*size);
	int i=0,k=0;
	unsigned char ch2=1<<7;
	unsigned char ch1;
	while(k<size){
		ch1=*((char *)data+(size-(k+1)));
		for(int j=0;j<8;j++,i++){
			ret[i]=ch1&ch2?49:48;
			ch1<<=1;
		}
		k++;
	}
	ret[i]='\0';
	ret=trimleft(ret,'0');
	return ret;
}

// Return Index Of String in String if
int indexof(string str,string key){
	char *ch=strstr(str,key);
	if(ch!=NULL)
		return ch-str;
	return -1;
}

// Return Indexes of All Occurrences of String in String
int * indexofall(string str,string key,int *size){
	*size=0;
	char *ch=strstr(str,key);
	if(ch!=NULL){
		int *ptr1,*ptr2;
		int k=0;
		ptr1=(int *)malloc(sizeof(int)*256);
		*(ptr1+k)=ch-str;	
		while(ch!=NULL){
			ch=strstr(ch+1,key);
			k++;
			*(ptr1+k)=ch-str;
		}
		*size=k;
		ptr2=(int *)realloc(ptr1,sizeof(int)*k);
		return ptr2;
	}
	return NULL;
}

// Return Last Index Of String in String if
int lastindexof(string str,string key){
	int s;
	int *a=indexofall(str,key,&s);
	if(a!=NULL)
		return a[s-1];
	return -1;
}

// Return Index Of Character in String if
int indexofchar(string str,int key){
	char *ch=strchr(str,key);
	if(ch!=NULL)
		return ch-str;
	return -1;
}

// Return Last Index Of Char in String
int lastindexofchar(string str,int key){
	char *ch=strrchr(str,key);
	if(ch!=NULL)
		return ch-str;
	return -1;
}

// Return Indexes of All Occurrences of Character in String
int * indexofallchar(string str,int key,int *size){
	*size=0;
	char *ch=strchr(str,key);
	if(ch!=NULL){
		int *ptr1,*ptr2;
		int k=0;
		ptr1=(int *)malloc(sizeof(int)*256);
		*(ptr1+k)=ch-str;	
		while(ch!=NULL){
			ch=strchr(ch+1,key);
			k++;
			*(ptr1+k)=ch-str;
		}
		*size=k;
		ptr2=(int *)realloc(ptr1,sizeof(int)*k);
		return ptr2;
	}
	return NULL;
}