
#include "../includes/cipher.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_ZEROS

/// @brief La S-box du chiffrement.
byte sBox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

/// @brief L'inverse de la S-box du chiffrement.
byte invSBox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

/// @brief La permutation des bits du chiffrement
int perm[128] = {
    0,   16,  32,  48,  64,  80, 96,  112,  1,   17,  33,  49,  65,  81, 97 , 113,
    2,   18,  34,  50,  66,  82, 98,  114,  3,   19,  35,  51,  67,  83, 99 , 115,
    4,   20,  36,  52,  68,  84, 100, 116,  5,   21,  37,  53,  69,  85, 101, 117,
    6,   22,  38,  54,  70,  86, 102, 118,  7,   23,  39,  55,  71,  87, 103, 119,
    8,   24,  40,  56,  72,  88, 104, 120,  9,   25,  41,  57,  73,  89, 105, 121,
    10,  26,  42,  58,  74,  90, 106, 122,  11,  27,  43,  59,  75,  91, 107, 123,
    12,  28,  44,  60,  76,  92, 108, 124,  13,  29,  45,  61,  77,  93, 109, 125,
    14,  30,  46,  62,  78,  94, 110, 126,  15,  31,  47,  63,  79,  95, 111, 127
};

/// @brief L'inverse de la permutation des bits du chiffrement
int invPerm[128] = {
    0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88, 96,  104, 112, 120,
    1,   9,   17,  25,  33,  41,  49,  57,  65,  73,  81,  89, 97,  105, 113, 121,
    2,   10,  18,  26,  34,  42,  50,  58,  66,  74,  82,  90, 98,  106, 114, 122,
    3,   11,  19,  27,  35,  43,  51,  59,  67,  75,  83,  91, 99,  107, 115, 123,
    4,   12,  20,  28,  36,  44,  52,  60,  68,  76,  84,  92, 100, 108, 116, 124,
    5,   13,  21,  29,  37,  45,  53,  61,  69,  77,  85,  93, 101, 109, 117, 125,
    6,   14,  22,  30,  38,  46,  54,  62,  70,  78,  86,  94, 102, 110, 118, 126,
    7,   15,  23,  31,  39,  47,  55,  63,  71,  79,  87,  95, 103, 111, 119, 127,
};

void Block_xor(Block *block, Block *value)
{
    for (int i = 0; i < sizeof(block->bundles)/sizeof(block->bundles[0]); ++i)
        block->bundles[i] ^= value->bundles[i];
}

void Block_substitution(Block *block)
{
    for (int i = 0; i < sizeof(block->bundles)/sizeof(block->bundles[0]); ++i)
        block->bundles[i] = sBox[block->bundles[i]];
}

void Block_invSubstitution(Block *block)
{
    for (int i = 0; i < sizeof(block->bundles)/sizeof(block->bundles[0]); ++i)
        block->bundles[i] = invSBox[block->bundles[i]];
}

void Block_permutation(Block *block)
{
    Block blk = *block;
    int count = 0;
    for (int i = sizeof(block->bundles)/sizeof(block->bundles[0]) - 1; i > -1; --i)
        for (int j = 0; j < 8; ++j)
        { 
            int blockIndex = 15 - ((int)(perm[count] / 8));
            int bitIndex = perm[count++] - (8 * (15 - blockIndex));
            int valuetopermut = (blk.bundles[i] >> j) & 1;
            if (valuetopermut)
                block->bundles[blockIndex] |= 1 << bitIndex;
            else
                block->bundles[blockIndex] &= ~(1 << bitIndex);
        }
}

void Block_invPermutation(Block *block)
{
    Block blk = *block;
    int count = 0;
    for (int i = sizeof(block->bundles)/sizeof(block->bundles[0]) - 1; i > -1; --i)
        for (int j = 0; j < 8; ++j)
        { 
            int blockIndex = 15 - ((int)(invPerm[count] / 8));
            int bitIndex = invPerm[count++] - (8 * (15 - blockIndex));
            int valuetopermut = (blk.bundles[i] >> j) & 1;
            if (valuetopermut)
                block->bundles[blockIndex] |= 1 << bitIndex;
            else
                block->bundles[blockIndex] &= ~(1 << bitIndex);
        }
}

void initCipher(CipherData *data, Block *cipherKey)
{
    data->roundKeys[0] = *cipherKey;
    for (int i = 1; i < NB_ROUNDS + 1; ++i)
    {
        Block b =
        {
            .bundles = { 0 }
        };

        //k3[r - 1]
        b.bundles[3] = data->roundKeys[i - 1].bundles[3];
        Block_substitution(&b);
        data->roundKeys[i].bundles[0] = b.bundles[3];

        b.bundles[3] = 0;

        //k4[r - 1]
        b.bundles[4] = data->roundKeys[i - 1].bundles[4];
        Block_substitution(&b);
        data->roundKeys[i].bundles[1] = b.bundles[4];

        b.bundles[4] = 0;

        //k5[r - 1]
        b.bundles[5] = data->roundKeys[i - 1].bundles[5];
        Block_substitution(&b);
        data->roundKeys[i].bundles[2] = b.bundles[5];

        b.bundles[5] = 0;
        
        //k6[r - 1]
        b.bundles[6] = data->roundKeys[i - 1].bundles[6] ^ i;
        data->roundKeys[i].bundles[3] = b.bundles[6];

        b.bundles[6] = 0;

        data->roundKeys[i].bundles[4] = data->roundKeys[i - 1].bundles[7];
        data->roundKeys[i].bundles[5] = data->roundKeys[i - 1].bundles[8];
        data->roundKeys[i].bundles[6] = data->roundKeys[i - 1].bundles[9];
        data->roundKeys[i].bundles[7] = data->roundKeys[i - 1].bundles[10];
        data->roundKeys[i].bundles[8] = data->roundKeys[i].bundles[0] ^ data->roundKeys[i - 1].bundles[11];
        data->roundKeys[i].bundles[9] = data->roundKeys[i].bundles[1] ^ data->roundKeys[i - 1].bundles[12];
        data->roundKeys[i].bundles[10] = data->roundKeys[i].bundles[2] ^ data->roundKeys[i - 1].bundles[13];
        data->roundKeys[i].bundles[11] = data->roundKeys[i].bundles[3] ^ data->roundKeys[i - 1].bundles[14];
        data->roundKeys[i].bundles[12] = data->roundKeys[i].bundles[4] ^ data->roundKeys[i - 1].bundles[15];
        data->roundKeys[i].bundles[13] = data->roundKeys[i].bundles[5] ^ data->roundKeys[i - 1].bundles[0];
        data->roundKeys[i].bundles[14] = data->roundKeys[i].bundles[6] ^ data->roundKeys[i - 1].bundles[1];
        data->roundKeys[i].bundles[15] = data->roundKeys[i].bundles[7] ^ data->roundKeys[i - 1].bundles[2];
    }
}

void encryptBlock(CipherData *data, Block *block)
{
    for (int i = 0; i < NB_ROUNDS - 1; ++i)
    {
        Block_xor(block, &data->roundKeys[i]);
        Block_substitution(block);
        Block_permutation(block);
    }

    Block_xor(block, &data->roundKeys[NB_ROUNDS - 1]);
    Block_substitution(block);
    Block_xor(block, &data->roundKeys[NB_ROUNDS]);
}

void decryptBlock(CipherData *data, Block *block)
{
    Block_xor(block, &data->roundKeys[NB_ROUNDS]);
    Block_invSubstitution(block);
    Block_xor(block, &data->roundKeys[NB_ROUNDS - 1]);

    for (int i = NB_ROUNDS - 2; i >= 0; --i)
    {
        Block_invPermutation(block);
        Block_invSubstitution(block);
        Block_xor(block, &data->roundKeys[i]);
    }
}

void encryptCBC(CipherData *data, Block *iv, Block *message, int nbBlocks)
{
    Block_xor(&message[0], iv);
    encryptBlock(data, &message[0]);
    for (int i = 1; i < nbBlocks; ++i)
    {
        Block_xor(&message[i], &message[i - 1]);
        encryptBlock(data, &message[i]);
    }
}

void decryptCBC(CipherData *data, Block *iv, Block *message, int nbBlocks)
{
    for (int i = nbBlocks - 1; i >= 1; --i)
    {
        decryptBlock(data, &message[i]);
        Block_xor(&message[i - 1], &message[i]);
    }
    decryptBlock(data, &message[0]);
    Block_xor(&message[0], iv);
}

void printBlock(Block *block)
{
    int i;
    printf("[");
    for (i = 0; i < 15; i++)
    {
    #ifdef PRINT_ZEROS
        printf("%02X ", block->bundles[i]);
    #else
        if (block->bundles[i])
            printf("%02X ", block->bundles[i]);
        else
            printf("-- ");
    #endif
    }

#ifdef PRINT_ZEROS
    printf("%02X]\n", block->bundles[15]);
#else
    if (block->bundles[15])
        printf("%02X]\n", block->bundles[15]);
    else
        printf("--]\n");
#endif
}