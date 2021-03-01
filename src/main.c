
#include "../includes/cipher.h"
#include "../includes/bonus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------------------------------------
//  Chiffrement et déchiffrement

int main()
{
    CipherData cipherData = { 0 };
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
    printBlock(&block);
}