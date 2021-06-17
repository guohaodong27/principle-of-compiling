#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define NUM_MAX 10
#define MSG_MAX (NUM_MAX+32)
// input recore the input string
// ind record cur point in input string
char * input;
int ind=0;

void back_space(int back){
	ind = ind-back;
}

// declare function
int unsign();
int unsign_real();
int sign();
int unsign_int();
int num_string();
int num(char ch);
int rate_factor();

void end();

// error message
// if end normally , it is the type of the cur number
char msg[MSG_MAX];

// use count as a tmp offset of index, like a transaction manager
int unsign(){
	int count = ind;
	if (unsign_real()){
		return TRUE;
	}
	if (unsign_int()){
		return TRUE;
	}

	// other characters,forward
	ind++;
	end(count,"syntax error ,not a unsign number:");
	return FALSE;
}

int unsign_real(){
	int count = ind;
	int is_flashback = TRUE;
	// if not a unsign int in head ,return FALSE
	if(!unsign_int()){
		return FALSE;
	}
	ind++;
	if (input[ind]=='.'){
		ind++;
		is_flashback = FALSE;
		num_string();
	}

	if (input[ind]=='E'){
		ind++;
		is_flashback = FALSE;
		if(!rate_factor()){
			return FALSE;
		}
	}

	if (is_flashback){
		back_space(ind-count);
		return FALSE;
	}
	end(count,"real number:");
	return TRUE;
}

int unsign_int(){
	int count = ind;
	int is_flashback = TRUE;
	if (num_string()){
		is_flashback = FALSE;
	}

	if (is_flashback){
		back_space(ind-count);
		return FALSE;
	}
	end(count,"int number:");
	return TRUE;
}

int num_string(){
	int count = ind;
	int is_flashback = TRUE;
	while(num(input[ind])){
		ind++;
	}
	if(ind != count){
		is_flashback = FALSE;
	}
	// if count == ind ,not need flash back,and not a num string
	return !is_flashback;
}

int num(char ch){
	if(ch < '9'&&ch>'0'){
		return TRUE;
	}else{
		return FALSE;
	}
}

int rate_factor(){
	int count = ind;
	int is_flashback = TRUE;
	if (input[ind]=='-'||input[ind]=='+'){
		ind++;
	}
	if(num_string()){
		is_flashback = FALSE;
	}

	if (is_flashback){
		back_space(ind-count);
		return FALSE;
	}
	return TRUE;
}

void end(int count,const char* type_msg){
	strcpy(msg,"");
	char number[NUM_MAX];
	strcat(msg,type_msg);
	strncpy(number,input+count,ind-count);
	back_space(1);
	number[ind-count+1]='\0';
	strcat(msg,number);
}

void main(){
	// msg = malloc(sizeof(char)*100);
	input = "345.6&d*&7$6E4^6.7E4;";
	int count = 0;
	while (input[ind]!=';')
	{
		int res = unsign();
		printf("%d\n",res);
		printf("%s\n",msg);
		ind++;
		count+=res;
	}
	printf("the number of unsign num:%d\n",count);
	
	// free(msg);
}
