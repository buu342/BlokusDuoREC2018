#include "str_ar.h"

char *strchr_ar(char *str, int ch)
{
    do 
    {
        if (*str == ch) 
            return str;
    } 
    while (*str++);
    return 0;
}