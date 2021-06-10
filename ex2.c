#include <stdio.h>
#define NULL 0
#define MAX_STACK 20
static char stack[MAX_STACK] = {0};
static int _index;
static char rpn[64];
/**
 * 模拟pop方法
 */
char pop(){
    if (_index<20 && _index >-1){
        char res = stack[_index];
        stack[_index] = 0;
        return res;
    }
    return NULL;
}
char peek(){
    if (_index<20 && _index >-1){
        char res = stack[_index];
        return res;
    }
    return NULL;
}

int is_not_empty(){
    return _index;
}

int is_priority(char cur){
    return priority[is_operator(peek())][is_operator(cur)]=='<';
}
/**
 * 模拟push方法
 * @param c 压入栈的元素
 */
void push(char c){
    if(_index<MAX_STACK-1){
        stack[_index+1] = c;
    }
}

static char operator[] = {'+','-','*','/','^','(',')'};
static char priority[7][7] = {
    {'>','>','<','<','<','<','>'},
    {'>','>','<','<','<','<','>'},
    {'>','>','>','>','<','<','>'},
    {'>','>','>','>','<','<','>'},
    {'>','>','>','>','>','<','>'},
    {'<','<','<','<','<','<','='},
    {'>','>','>','>','>','>','>'},
};

/**
 * 判断是否是运算符
 */
int is_operator(char c){
    for (int i = 0; i < 7; i++)
    {
        if (operator[i] == c){
            return i;
        }
    }
    return -1;
}

/**
 * 获取下一个字符
 */
static int _str_index = 0;
char get_next(const char* str){
    if (_str_index >-1)
    {
        char res = *(str+_str_index);
        if (res == '\0'){
            return -1;
        }
        return res;
    }
    
}

int main(int argc, char const *argv[])
{
    const char* str = argv[1];
    char cur;
    while (-1 != (cur = get_next(str)))
    {
        if (is_operator(cur)){
            if(!is_not_empty()){
                push(cur);
            }
        }else{
            //todo 直接添加到rpn
        }
    }
    
    return 0;
}


