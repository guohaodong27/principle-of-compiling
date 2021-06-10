#define TRUE 1
#define FALSE 0
#include <stdio.h>

// 状态指示器
// 0 正常状态
// 1 不符合的语法
int static status = 0;

/** 
 * 判断字符是否为数字
 * @param c 字符
 * @return 仅当为0-9时返回1,否则返回0
 */
int is_num(char c)
{
    if (c <= '9' && c >= '0')
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * 获取字符串中的后一个字符
 * @param c 字符串指针(首地址)
 * @return 后一个字符
 */

// 全局的字符索引位置,禁止修改
static int _index = 0;
char get_next(const char *c)
{
    if (_index > -1)
    {
        char res = *(c + _index++);
        if (res == '\0'||res == ';'){
            return '#';
        }else{
            return res;
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int count = 0;
    const char *str = argv[1];
    char cur;
    // \d+\.[+,-]?\d
    while ('#'!=(cur=get_next(str)))
    {
        if (!is_num(cur)){
            continue;
        }
        // 如果遇到数字一直读
        while (is_num(cur))
        {
            cur = get_next(str);
        }

        // 判断是否是小数
        if (cur == '.')
        {
            // 无需判断,小数点后没有数字认为是整数
            // if(!is_num(cur)){
            //     continue;
            // }
            cur = get_next(str);
            while (is_num(cur))
            {
                cur = get_next(str);
            }
            
        }

        // 判断是否为指数
        if (cur == 'E' | cur == 'e')
        {
            cur = get_next(str);
            if (cur == '-' || cur == '+')
            {
                cur = get_next(str);
            }
            if(!is_num(cur)){
                continue;
            }
            while (is_num(cur))
            {
                cur = get_next(str);
            }
        }
        // 识别到一个
        count++;
    }
    printf("the input string is:%s\n",str);
    printf("the count of number is:%d\n",count);
    return 0;
}
