
#include "../includes/bonus.h"
#include "../includes/cipher.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DiffTable *newDiffTable(int nbBits)
{
    DiffTable *diffTable = NULL;
    int nbElts = 1 << nbBits;

    diffTable = (DiffTable *)calloc(1, sizeof(DiffTable));
    if (!diffTable) goto ERROR_LABEL;

    diffTable->nbBits = nbBits;
    diffTable->nbElts = nbElts;
    diffTable->max = 0;

    diffTable->coeffs = (int **)calloc(nbElts, sizeof(int *));
    if (!diffTable->coeffs) goto ERROR_LABEL;

    for (int i = 0; i < nbElts; i++)
    {
        diffTable->coeffs[i] = (int *)calloc(nbElts, sizeof(int));
        if (!diffTable->coeffs[i]) goto ERROR_LABEL;
    }

    return diffTable;

ERROR_LABEL:
    printf("ERROR - newDiffTable()\n");
    freeDiffTable(diffTable);
    return NULL;
}

void freeDiffTable(DiffTable *diffTable)
{
    if (!diffTable) return;

    if (diffTable->coeffs)
    {
        int nbElts = diffTable->nbElts;
        for (int i = 0; i < nbElts; i++)
        {
            if (diffTable->coeffs[i])
                free(diffTable->coeffs[i]);
        }
        free(diffTable->coeffs);
    }

    // Clear the memory (security)
    memset(diffTable, 0, sizeof(*diffTable));
}

void swap(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int * sBox, unsigned int size)
{
    for (int i = size - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        swap(&sBox[i], &sBox[j]);
    }
}

void littleShuffle(int * sBox, unsigned int size, float percent)
{
    unsigned int newSize = percent * size/2;
    while(newSize--)
        swap(&sBox[rand() % size], &sBox[rand() % size]);
}

int numberOfMax(int * sBox, unsigned int size, unsigned int max)
{
    int count = 0;
    for (int i = 0; i < size; ++i) if (sBox[i] == max) ++count;
    return count;
}

void randomSBox(int * sBox, int nbBits)
{
    unsigned int size = 1 << nbBits;
    for (int i = 0; i < size; ++i) sBox[i] = i;
    shuffle(sBox, size);
}

void initDiffTable(DiffTable *diffTable, int *sBox)
{
    DiffTable d = *diffTable;
    d.max = 0;
    for (int i = 0; i < d.nbElts; ++i)
        memset(d.coeffs[i], 0, sizeof(int) * d.nbElts);
    for (int i = 0; i < d.nbElts; ++i)
        for (int j = 0; j < d.nbElts; ++j)
        {
            int diff = sBox[j] ^ sBox[j ^ i];
            if (++d.coeffs[i][diff] > d.max && ((i + diff) != 0))
                d.max = d.coeffs[i][diff];
        }
    *diffTable = d;
}

int * getBestSBox(int nbBits)
{
    DiffTable * diffTable = newDiffTable(nbBits);
    int size = diffTable->nbElts;

    int * sBox = malloc(size * sizeof(int));
    randomSBox(sBox, diffTable->nbBits);

    int * bestSBox = malloc(size * sizeof(int));
        
    initDiffTable(diffTable, sBox);
    int max = diffTable->max;
    int nbMax = -1;

    for (int i = 0; i < 1 << 10; ++i)
    {
        memcpy(bestSBox, sBox, size * sizeof(int));
        littleShuffle(bestSBox, size, 0.50);

        initDiffTable(diffTable, bestSBox);
        int n = numberOfMax(bestSBox, size, diffTable->max);
        if (max > diffTable->max || 
           (max == diffTable->max && (nbMax == -1 || nbMax > n)))
        {
            max = diffTable->max;
            nbMax = n;
            memcpy(sBox, bestSBox, size * sizeof(int));
        }
    }
    free(bestSBox);

    initDiffTable(diffTable, sBox);
    printf("Max in DiffTable: %d\n", diffTable->max);
    printf("Number of max: %d\n", nbMax);
    return sBox;
}

void initFastCipher(FastCipherData *data, Block *cipherKey)
{
    FastCipherData d = *data;
    d.roundKeys[0] = *cipherKey;
    for (byte i = 1; i < NB_ROUNDS + 1; ++i)
    {
        d.roundKeys[i].bundles[0] = sBox[d.roundKeys[i - 1].bundles[3]];
        d.roundKeys[i].bundles[1] = sBox[d.roundKeys[i - 1].bundles[4]];
        d.roundKeys[i].bundles[2] = sBox[d.roundKeys[i - 1].bundles[5]];        
        d.roundKeys[i].bundles[3] = d.roundKeys[i - 1].bundles[6] ^ i;
        d.roundKeys[i].bundles[4] = d.roundKeys[i - 1].bundles[7];
        d.roundKeys[i].bundles[5] = d.roundKeys[i - 1].bundles[8];
        d.roundKeys[i].bundles[6] = d.roundKeys[i - 1].bundles[9];
        d.roundKeys[i].bundles[7] = d.roundKeys[i - 1].bundles[10];
        d.roundKeys[i].bundles[8] = d.roundKeys[i].bundles[0] ^ d.roundKeys[i - 1].bundles[11];
        d.roundKeys[i].bundles[9] = d.roundKeys[i].bundles[1] ^ d.roundKeys[i - 1].bundles[12];
        d.roundKeys[i].bundles[10] = d.roundKeys[i].bundles[2] ^ d.roundKeys[i - 1].bundles[13];
        d.roundKeys[i].bundles[11] = d.roundKeys[i].bundles[3] ^ d.roundKeys[i - 1].bundles[14];
        d.roundKeys[i].bundles[12] = d.roundKeys[i].bundles[4] ^ d.roundKeys[i - 1].bundles[15];
        d.roundKeys[i].bundles[13] = d.roundKeys[i].bundles[5] ^ d.roundKeys[i - 1].bundles[0];
        d.roundKeys[i].bundles[14] = d.roundKeys[i].bundles[6] ^ d.roundKeys[i - 1].bundles[1];
        d.roundKeys[i].bundles[15] = d.roundKeys[i].bundles[7] ^ d.roundKeys[i - 1].bundles[2];
    }
    *data = d;
}

void fastEncryptBlock(FastCipherData *data, Block *block)
{
    for (byte i = 0; i < NB_ROUNDS - 1; ++i)
    {
        //XOR
        Block b = *block; 
        Block v = data->roundKeys[i];
        for (byte j = 0; j < BLOCK_SIZE; ++j)
            b.bundles[j] ^= v.bundles[j];
        *block = b;

        //SUBSTITUTION
        b = *block;
        for (byte j = 0; j < BLOCK_SIZE; ++j)
            b.bundles[j] = sBox[b.bundles[j]];
        *block = b;

        //PERMUTATION
        Block blk = *block;
        b = blk;
        byte count = 0;
        for (int j = BLOCK_SIZE - 1; j >= 0; --j)
            for (byte k = 0; k < 8; ++k)
            { 
                byte blockIndex = 15 - perm[count] / 8;
                byte bitIndex = perm[count++] - (8 * (15 - blockIndex));
                byte valuetopermut = (blk.bundles[j] >> k) & 1;
                b.bundles[blockIndex] = (b.bundles[blockIndex] & ~(1UL << bitIndex)) | 
                                        (valuetopermut << bitIndex);
            }
        *block = b;
    }

    //XOR
    Block b = *block; 
    Block v = data->roundKeys[NB_ROUNDS - 1];
    for (byte j = 0; j < BLOCK_SIZE; ++j)
        b.bundles[j] ^= v.bundles[j];
    *block = b;

    //SUBSTITUTION
    b = *block;
    for (byte j = 0; j < BLOCK_SIZE; ++j)
        b.bundles[j] = sBox[b.bundles[j]];
    *block = b;

    //XOR
    b = *block;
    v = data->roundKeys[NB_ROUNDS];
    for (byte j = 0; j < BLOCK_SIZE; ++j)
        b.bundles[j] ^= v.bundles[j];
    *block = b;
}
