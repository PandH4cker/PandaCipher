#ifndef UTILS_H
#define UTILS_H

#include "cipher.h"
#include <stdio.h>

size_t getFileSize(const char * path);
void fileToBlock(Block * message, size_t size, const char * path);
void blocktoFile(Block * message, size_t size, const char * path);
void encryptFile(CipherData * data, Block * iv, const char * path);
void decryptFile(CipherData * data, Block * iv, const char * path);
Block sha3CipherKeyBlock(char * cipherKey);

#endif