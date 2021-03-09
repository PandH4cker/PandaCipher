
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
    //printf("%ld\n", time(NULL));
    //srand(time(NULL));

    // panda cipher :D!
    Block plaintext = 
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

    FastCipherData cipherData = { 0 };
    initFastCipher(&cipherData, &cipherKey);
    fastEncryptBlock(&cipherData, &plaintext);
    printf("Crypted\t\t");
    printBlock(&plaintext);
    decryptBlock(&cipherData, &plaintext);
    printf("Decrypted\t");
    printBlock(&plaintext);
    return EXIT_SUCCESS;
}