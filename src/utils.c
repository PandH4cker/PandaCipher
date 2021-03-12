#include "../includes/utils.h"
#include "../includes/stringUtils.h"
#include "../includes/sha3.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

size_t getFileSize(const char * path)
{
    FILE * f = fopen(path, "rb");
    if (!f)
    {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    fseek(f, 0L, SEEK_END);
    size_t size = ftell(f);
    fclose(f);
    return size;
}

void fileToBlock(Block * message, size_t size, const char * path)
{
    FILE * f = fopen(path, "rb");
    if (!f)
    {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    fread(message, BLOCK_SIZE * size, 1, f);
    fclose(f);
}

void blocktoFile(Block * message, size_t size, const char * path)
{
    FILE * f = fopen(path, "wb");
    if (!f)
    {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }
    fwrite(message, BLOCK_SIZE * size, 1, f);
    fclose(f);
}

void encryptFile(CipherData * data, Block * iv, const char * path)
{
    size_t fileSize = getFileSize(path);
    size_t blockNeeded = ceil(fileSize / 16.0);

    Block * message = malloc(blockNeeded * sizeof(Block));
    fileToBlock(message, blockNeeded, path);

    encryptCBC(data, iv, message, blockNeeded);
    char * concatenedString = concat(path, ".crypt");
    blocktoFile(message, blockNeeded, concatenedString);

    free(concatenedString);
    free(message);
}

void decryptFile(CipherData * data, Block * iv, const char * path)
{
    size_t fileSize = getFileSize(path);
    size_t blockNeeded = ceil(fileSize / 16.0);

    Block * message = malloc(blockNeeded * sizeof(Block));
    fileToBlock(message, blockNeeded, path);

    decryptCBC(data, iv, message, blockNeeded);
    char * concatenedString = concat(path, ".decrypted");
    blocktoFile(message, blockNeeded, concatenedString);

    free(concatenedString);
    free(message);
}

Block sha3CipherKeyBlock(char * cipherKey)
{
    Block blk = { 0 };

    sha3_context c;
    const byte * hash;

    sha3_Init256(&c);
    sha3_SetFlags(&c, SHA3_FLAGS_KECCAK);
    sha3_Update(&c, cipherKey, strlen(cipherKey));
    hash = sha3_Finalize(&c);

    for (int i = 0; i < BLOCK_SIZE; ++i) blk.bundles[i] = hash[i];

    return blk;
}