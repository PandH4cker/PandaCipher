#ifndef STRING_UTILS_H
#define STRING_UTILS_H

typedef unsigned char byte;
typedef unsigned long size_t;

void charToByte(char * chars, byte * bytes, unsigned int count);
byte * hexStringToByteArray(char * s);
char * __splitInParts(const char *str, size_t size);
char ** splitInParts(char *str, size_t parts, size_t * size);
char * concat(const char * s1, const char * s2);

#endif