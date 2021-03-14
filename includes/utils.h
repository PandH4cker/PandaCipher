#ifndef UTILS_H
#define UTILS_H

#include "cipher.h"
#include <stdio.h>

#define CBC_MODE 0

size_t getFileSize(const char * path);
void fileToBlock(Block * message, size_t size, const char * path);
void blocktoFile(Block * message, size_t size, const char * path);
void encryptFile(CipherData * data, Block * iv, const char * path, const int mode);
void decryptFile(CipherData * data, Block * iv, const char * path, const int mode);
void encryptString(CipherData * data, Block * iv, char * s, const int mode);
void decryptString(CipherData * data, Block * iv, char * s, const int mode);
void printDigest(Block * message, size_t size);
Block sha3CipherKeyBlock(char * cipherKey);

#endif