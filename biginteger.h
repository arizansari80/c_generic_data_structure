#include <string.h>
#include <stdlib.h>
typedef char * string;

// BigInteger Implementation In C

// Defining BigInteger Structure
typedef struct bigint{
	string data;
	int length;
}bigint;

typedef bigint * biginteger;

biginteger givemebigint(){
	string temp=(string)malloc(4096);
	string temp1=(string)malloc(4096);
	scanf("%[0-9]s",temp);
	fgets(temp1,4096,stdin);
	free(temp1);
	biginteger ret=(biginteger)malloc(sizeof(bigint));
	ret->length=strlen(temp);
	ret->data=(string)malloc(ret->length+1);
	strcpy(ret->data,temp);
	free(temp);
	return ret;
}

// Addition of BigInteger
biginteger add_biginteger(biginteger b1,biginteger b2){
	char carry=0,res=0;
	int i,j;
	i=b1->length;
	j=b2->length;
	int k=i>j?i:j;
	biginteger ret=(biginteger)malloc(sizeof(biginteger));
	ret->data=(string)malloc(k+2);
	ret->data[k+1]='\0';
	ret->data[0]='0';
	ret->length=k+1;
	int *table=(int *)malloc(sizeof(int)*20);
	for(i=0;i<10;i++)
		*(table+i)=i;
	int z=256;
	for(;i<20;i++,z++)
		*(table+i)=z;
	i=b1->length;
	i--,j--;
	while(i>=0&&j>=0){
		res=carry+(b1->data[i--]-48)+(b2->data[j--]-48);
		carry=*((char *)(table+res)+1);
		res=*(char *)(table+res);
		ret->data[k--]=res+48;
	}
	if(carry==0){
		while(i>=0)
			ret->data[k--]=b1->data[i--];
		while(j>=0)
			ret->data[k--]=b2->data[j--];
	}
	else{
		while(i>=0){
			res=carry+(b1->data[i--]-48);
			carry=*((char *)(table+res)+1);
			res=*(char *)(table+res);
			ret->data[k--]=res+48;	
		}
		while(j>=0){
			res=carry+(b2->data[j--]-48);
			carry=*((char *)(table+res)+1);
			res=*(char *)(table+res);
			ret->data[k--]=res+48;		
		}
	}
	ret->data[k--]=carry+48;
	if(ret->data[0]=='0'){
		ret->data+=1;
		ret->length-=1;
	}
	free(table);
	return ret;
}