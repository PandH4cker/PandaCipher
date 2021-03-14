#include "../includes/argutils.h"

//-------------------------------------------------------------------------------------------------
//  Chiffrement et déchiffrement

int main(int argc, char ** argv)
{

    return handleArgs(argc, argv);

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
}