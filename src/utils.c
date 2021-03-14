#include "../includes/utils.h"
#include "../includes/stringUtils.h"
#include "../includes/sha3.h"
#include "../includes/colors.h"

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

void encryptFile(CipherData * data, Block * iv, const char * path, const int mode)
{
    size_t fileSize = getFileSize(path);
    size_t blockNeeded = ceil(fileSize / 16.0);

    Block * message = malloc(blockNeeded * sizeof(Block));
    fileToBlock(message, blockNeeded, path);

    switch (mode)
    {
        case CBC_MODE:
            encryptCBC(data, iv, message, blockNeeded);
            break;
        
        default:
            fprintf(stderr, "[" COLOR_RED "!" COLOR_RESET "] The specified mode is unknown. List available modes by using --list-modes command\n");
            exit(EXIT_FAILURE);
    }

    char * concatenedString = concat(path, ".crypt");
    blocktoFile(message, blockNeeded, concatenedString);

    free(concatenedString);
    free(message);
}

void decryptFile(CipherData * data, Block * iv, const char * path, const int mode)
{
    size_t fileSize = getFileSize(path);
    size_t blockNeeded = ceil(fileSize / 16.0);

    Block * message = malloc(blockNeeded * sizeof(Block));
    fileToBlock(message, blockNeeded, path);

    switch (mode)
    {
        case CBC_MODE:
            decryptCBC(data, iv, message, blockNeeded);
            break;
        
        default:
            fprintf(stderr, "[" COLOR_RED "!" COLOR_RESET "] The specified mode is unknown. List available modes by using --list-modes command\n");
            exit(EXIT_FAILURE);
    }

    char * concatenedString = concat(path, ".decrypted");
    blocktoFile(message, blockNeeded, concatenedString);

    free(concatenedString);
    free(message);
}

void printDigest(Block * message, size_t size)
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < BLOCK_SIZE; ++j)
            printf("%02X", message[i].bundles[j]);
    printf("\n");
}

void encryptString(CipherData * data, Block * iv, char * s, const int mode)
{
    size_t strSize = strlen(s);
    size_t blockNeeded = ceil(strSize / 16.0);
    Block * message = malloc(blockNeeded * sizeof(Block));

    size_t size;
    char ** splitted = splitInParts(s, BLOCK_SIZE, &size);

    for (int i = 0; i < blockNeeded; ++i)
        charToByte(splitted[i], message[i].bundles, strlen(splitted[i]));
    
    switch (mode)
    {
        case CBC_MODE:
            encryptCBC(data, iv, message, blockNeeded);
            break;
        
        default:
            fprintf(stderr, "[" COLOR_RED "!" COLOR_RESET "] The specified mode is unknown. List available modes by using --list-modes command\n");
            exit(EXIT_FAILURE);
    }

    printDigest(message, blockNeeded);

    for (int i = 0; i < size; ++i)
        free(splitted[i]);
    free(splitted);
    free(message);
}

void decryptString(CipherData * data, Block * iv, char * s, const int mode)
{
    byte * byteArray = hexStringToByteArray(s);
    size_t arraySize = strlen(s) / 2;
    size_t blockNeeded = ceil(arraySize / 16.0);
    Block * message = malloc(blockNeeded * sizeof(Block));
        
    for (int i = 0; i < blockNeeded; ++i)
        for (int j = 0; j < BLOCK_SIZE; ++j)
            message[i].bundles[j] = byteArray[j + BLOCK_SIZE * i];

    switch (mode)
    {
        case CBC_MODE:
            decryptCBC(data, iv, message, blockNeeded);
            break;
        
        default:
            fprintf(stderr, "[" COLOR_RED "!" COLOR_RESET "] The specified mode is unknown. List available modes by using --list-modes command\n");
            exit(EXIT_FAILURE);
    }

    printDigest(message, blockNeeded);

    free(message);
    free(byteArray);
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