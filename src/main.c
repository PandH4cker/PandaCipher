
#include "../includes/cipher.h"
#include "../includes/bonus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//-------------------------------------------------------------------------------------------------
//  Chiffrement et déchiffrement

int main(int argc, char ** argv)
{
    //1615231972
    printf("%ld\n", time(NULL));
    srand(time(NULL));
    int nbBits = 8;
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
        littleShuffle(bestSBox, size, 0.42);

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

    free(sBox);
    freeDiffTable(diffTable);
    // panda cipher :D!
    /*Block plaintext = 
    { 
        .bundles = 
        {
            0x70, 0x61, 0x6e, 0x64, 
            0x61, 0x20, 0x63, 0x69, 
            0x70, 0x68, 0x65, 0x72, 
            0x20, 0x3a, 0x44, 0x21
        }
    };

    printf("Plain\t\t");
    printBlock(&plaintext);

    // 0x0123456789ABCDEF
    Block cipherKey = 
    { 
        .bundles = 
        {
            0x0, 0x1, 0x2, 0x3, 
            0x4, 0x5, 0x6, 0x7, 
            0x8, 0x9, 0xA, 0xB, 
            0xC, 0xD, 0xE, 0xF
        }
    };

    printf("Key\t\t");
    printBlock(&cipherKey);

    CipherData cipherData = { 0 };
    initCipher(&cipherData, &cipherKey);
    encryptBlock(&cipherData, &plaintext);
    printf("Crypted\t\t");
    printBlock(&plaintext);
    decryptBlock(&cipherData, &plaintext);
    printf("Decrypted\t");
    printBlock(&plaintext);*/
    return EXIT_SUCCESS;
}