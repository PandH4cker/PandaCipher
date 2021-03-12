
#include "../includes/cipher.h"
#include "../includes/bonus.h"
#include "../includes/utils.h"
#include "../includes/stringUtils.h"
#include "../includes/argutils.h"
#include "../includes/sha3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


Block iv = 
{
    .bundles = 
    {
        0x01, 0x18, 0xde, 0xad,
        0xbe, 0xef, 0xba, 0xd0,
        0xca, 0xb0, 0xac, 0xe0,
        0xad, 0xb0, 0x20, 0x47
    }
};

//-------------------------------------------------------------------------------------------------
//  Chiffrement et déchiffrement

int main(int argc, char ** argv)
{
    struct arguments arguments;

    arguments.listModes = 0;
    arguments.encrypt = "";
    arguments.cipherKey = "";
    arguments.inputFile = "";

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if(arguments.listModes)
    {
        printf("CBC\tCipherBlockChaining");
        return EXIT_SUCCESS;
    }

    //FILE MODE
    if(!strcmp(arguments.encrypt, "") && strcmp(arguments.inputFile, ""))
        if (strcmp(arguments.cipherKey, ""))
        {
            CipherData data = { 0 };
            Block cipherKey = sha3CipherKeyBlock(arguments.cipherKey);

            printBlock(&cipherKey);
            initCipher(&data, &cipherKey);

            encryptFile(&data, &iv, arguments.inputFile);
            return EXIT_SUCCESS;
        }
    
    if(strcmp(arguments.encrypt, ""))
        if (strcmp(arguments.cipherKey, ""))
        {
            CipherData data = { 0 };
            Block cipherKey = sha3CipherKeyBlock(arguments.cipherKey);

            printBlock(&cipherKey);
            initCipher(&data, &cipherKey);

            size_t strSize = strlen(arguments.encrypt);
            size_t blockNeeded = ceil(strSize / 16.0);
            Block * message = malloc(blockNeeded * sizeof(Block));

            size_t size;
            char ** splitted = splitInParts(arguments.encrypt, BLOCK_SIZE, &size);

            for (int i = 0; i < blockNeeded; ++i)
                charToByte(splitted[i], message[i].bundles, strlen(splitted[i]));

            encryptCBC(&data, &iv, message, blockNeeded);

            for (int i = 0; i < blockNeeded; ++i)
                for (int j = 0; j < BLOCK_SIZE; ++j)
                    printf("%02X", message[i].bundles[j]);
            printf("\n");

            for (int i = 0; i < size; ++i)
                free(splitted[i]);
            free(splitted);
            free(message);
            return EXIT_SUCCESS;
        }


    //1615231972
    //printf("%ld\n", time(NULL));
    //srand(time(NULL));

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
    printBlock(&plaintext);*/

    // 0x0123456789ABCDEF
    /*Block cipherKey = 
    { 
        .bundles = 
        {
            0x0, 0x1, 0x2, 0x3, 
            0x4, 0x5, 0x6, 0x7, 
            0x8, 0x9, 0xA, 0xB, 
            0xC, 0xD, 0xE, 0xF
        }
    };

    Block iv =
    {
        .bundles =
        {
            0xFF, 0xEE, 0xDD, 0xCC,
            0xBB, 0xAA, 0x99, 0x88,
            0x77, 0x66, 0x55, 0x44,
            0x33, 0x22, 0x11, 0x00
        }
    };

    CipherData cipherData = { 0 };
    initCipher(&cipherData, &cipherKey);

    encryptFile(&cipherData, &iv, argv[1]);
    decryptFile(&cipherData, &iv, argv[2]);*/
    return EXIT_FAILURE;
}