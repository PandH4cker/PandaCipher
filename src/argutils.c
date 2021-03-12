#include "../includes/argutils.h"
#include "../includes/cipher.h"
#include "../includes/utils.h"
#include "../includes/stringUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const char * argp_program_version = "PandaCipher 1.0.0";
const char doc[] = "PandaCipher Help Prompt";
const char * argp_program_bug_address = "<dray@et.esiea.fr>|<samenaire@et.esiea.fr>";
const char args_doc[] = 
            "ARG1";
const struct argp_option options[] = 
{
    {"list-modes", OPT_LIST_MODES, NULL, 0, "Print cryptographic modes that can be used"},
    {"encrypt", 'e', "STR", OPTION_ARG_OPTIONAL, "Specify encrypt mode"},
    {"cipher-key", 'k', "KEY", 0, "Key for crypting"},
    {"input-file", 'i', "FILE", 0, "Input file to be encrypted"},
    {0}
};

error_t parse_opt(int key, char * arg, struct argp_state * state)
{
    struct arguments * arguments = (struct arguments *) state->input;
    switch(key){

        case OPT_LIST_MODES:
            arguments->listModes = 1;
            break;
        
        case 'e':
            if (arg)
                arguments->encrypt = arg;
            break;
        
        case 'k':
            arguments->cipherKey = arg;
            break;
        
        case 'i':
            arguments->inputFile = arg;
            break;

        case ARGP_KEY_ARG:
            arguments->args = arg;
            arguments->strings = &state->argv[state->next];
            state->next = state->argc;
            break;
        
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

struct argp argp = {options, parse_opt, args_doc, doc};

void initArgumentsStructure(struct arguments * arguments)
{
    arguments->listModes = 0;
    arguments->encrypt = "";
    arguments->cipherKey = "";
    arguments->inputFile = "";
}

int handleArgs(int argc, char ** argv)
{
    struct arguments arguments;
    initArgumentsStructure(&arguments);

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

            encryptFile(&data, &initVect, arguments.inputFile);
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

            encryptCBC(&data, &initVect, message, blockNeeded);

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

    return EXIT_FAILURE;
}