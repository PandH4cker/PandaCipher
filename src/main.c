
#include "../includes/cipher.h"
#include "../includes/bonus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------------------------------------
//  Chiffrement et déchiffrement

int main(int argc, char ** argv)
{
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

    printf("Plain  ");
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

    printf("Key    ");
    printBlock(&cipherKey);

    printf("\n[+] XORing with the cipherkey..\n");
    Block_xor(&plaintext, &cipherKey);

    printf("Xored    ");
    printBlock(&plaintext);

    // p`lge%enxaoy,7J.
    Block expected = 
    { 
        .bundles = 
        {
            0x70, 0x60, 0x6c, 0x67, 
            0x65, 0x25, 0x65, 0x6e, 
            0x78, 0x61, 0x6f, 0x79, 
            0x2c, 0x37, 0x4a, 0x2e
        }
    };
    printf("Expected ");
    printBlock(&expected);

    Block_permutation(&plaintext);
    /*CipherData cipherData = { 0 };
    Block cipherKey = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF };
    Block block = { 0 };
    int i;

    printf("Plain  ");
    printBlock(&block);
    printf("Key    ");
    printBlock(&cipherKey);

    // Initialisation du chiffrement
    initCipher(&cipherData, &cipherKey);

    // Chiffrement du block clair
    encryptBlock(&cipherData, &block);

    // Affichage du chiffré
    printf("Cipher ");
    printBlock(&block);

    // Déchiffrement du block chiffré
    decryptBlock(&cipherData, &block);

    // Affichage du résultat (normalement identique au clair)
    printf("Plain  ");
    printBlock(&block);*/
    return EXIT_SUCCESS;
}