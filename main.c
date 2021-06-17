#include<stdio.h>
typedef enum Boolean{False,True} Boolean;

Boolean is_num(){
	return True;
}
int main(int argc, char const *argv[])
{
	if (is_num()){
		puts("hello");
	}
	return 0;
}
