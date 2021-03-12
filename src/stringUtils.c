#include "../includes/stringUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void charToByte(char * chars, byte * bytes, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i)
        bytes[i] = (byte)chars[i];
}

char * __splitInParts(const char *str, size_t size)
{
    static const char *p=NULL;
    char *temp;
    int i;

    if(str != NULL) p=str;

    if(p==NULL || *p=='\0') return NULL;

    temp=(char*)malloc((size+1)*sizeof(char));
    for(i=0;*p && i<size;++i){
        temp[i]=*p++;
    }
    
    temp[i]='\0';
    return temp;
}

char ** splitInParts(char *str, size_t parts, size_t * size)
{
    *size = ceil(strlen(str) / (double) parts);
    char ** splitted = malloc(*size);
    for (int i = 0; i < *size; ++i)
        splitted[i] = malloc(parts * sizeof(char *));

    for (int i = 0; NULL != (str=__splitInParts(str, parts)); str = NULL)
        splitted[i++] = str;
    
    return splitted;
}

char * concat(const char * s1, const char * s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}