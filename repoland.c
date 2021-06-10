#include <stdio.h>
// 仅仅能判断整数
int is_number(char* ch){
    int count = 0;
    while (ch[count]>='0'&&ch[count]<='9')
    {
        count++;
    }
    return count;
}

/**
 * 假设有以下生成式
 * E=>E+T|E-T|T
 * T=>T*F|T/F|F
 * F=>F^P|P
 * P=>(E)|i
 */


/**
 * 消除左递归
 * 课本p126
 */

/**
 * 减小参数传递
 * 使用全局变量
 */
#define MAX_LEN 20
// 记录逆波兰式,大小可以调节
char res[MAX_LEN];
char* input;
// 访问input的位置
int ind=0;
// 访问res的位置
int res_i=0;
/**
 * 构造状态
 * 根据消除左递归后的文法构建
 */
void E();
void E1();
void T();
void T1();
void F();
void F1();

// E1 ☞ E'
// E=>TE1
E(){
    T();
    E1();
}

// E1=>+TE1|-TE1|e(空)
E1(){
    // enter the first status
    if(input[ind]=='+'){
        ind++;
        T();
        // record
        res[res_i]='+';
        res_i++;
        E1();
    }else{
        if (input[ind]=='-')
        {
            ind++;
            T();
            // record
            res[res_i]='-';
            res_i++;
            E1();
        }else{
            if (input[ind]==')')
            {
                ind++;
            }
            
        }
    }
}

T(){
    F();
    T1();
}

T1(){
        // enter the first status
    if(input[ind]=='*'){
        ind++;
        F();
        // record
        res[res_i]='*';
        res_i++;
        T1();
    }else{
        if (input[ind]=='/')
        {
            ind++;
            F();
            // record
            res[res_i]='/';
            res_i++;
            T1();
        }else{
            // T's follow set , merely contains ')'
            if (input[ind]==')')
            {
                ind++;
            }
        }
    }
}

F(){
    if (input[ind]=='(')
    {
        E();
    }else{
        // offset is the number's length
        int offset = is_number(input+ind);
        // write input to res directly
        for (int i =0;i<offset;i++){
            res[res_i]=input[ind];
            res_i++;
            ind++;
        }
    }
    
}

int main(int argc, char const *argv[])
{
    input="12-4/3";
    E();
    puts(res);
    return 0;
}
