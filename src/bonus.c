
#include "../includes/bonus.h"
#include "../includes/cipher.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void randomSBox(int * sBox, int nbBits)
{
    unsigned int size = 1 << nbBits;
    for (int i = 0; i < size; ++i) sBox[i] = i;
    for (int i = size - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        swap(&sBox[i], &sBox[j]);
    }
}

void initDiffTable(DiffTable *diffTable, int *sBox)
{
    // TODO
}

void initFastCipher(FastCipherData *data, Block *cipherKey)
{
    // TODO
}

void fastEncryptBlock(FastCipherData *data, Block *block)
{
    // TODO
}
