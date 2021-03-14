#include "../includes/argutils.h"
#include "../includes/cipher.h"
#include "../includes/utils.h"
#include "../includes/stringUtils.h"
#include "../includes/colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const char * argp_program_version = COLOR_YELLOW "PandaCipher 1.0.0" COLOR_RESET;
const char doc[] = 
    COLOR_YELLOW
        "PandaCipher - Symetrical encryption/decryption program (https://github.com/MrrRaph/PandaCipher)"
    COLOR_RESET;
const char * argp_program_bug_address = 
    COLOR_BLUE
        "<dray@et.esiea.fr>|<samenaire@et.esiea.fr>"
    COLOR_RESET;
const char args_doc[] = COLOR_RED "...args" COLOR_RESET;
const struct argp_option options[] = 
{
    {"list-modes", OPT_LIST_MODES, NULL, 0, COLOR_MAGENTA "Print cryptographic modes that can be used" COLOR_RESET},
    {"encrypt", 'e', COLOR_CYAN "STR" COLOR_RESET, OPTION_ARG_OPTIONAL, COLOR_MAGENTA "Specify encrypt mode" COLOR_RESET},
    {"decrypt", 'd', COLOR_CYAN "DIGEST" COLOR_RESET, OPTION_ARG_OPTIONAL, COLOR_MAGENTA "Specify decrypt mode" COLOR_RESET},
    {"cipher-key", 'k', COLOR_CYAN "KEY", 0, COLOR_MAGENTA "Key for crypting" COLOR_RESET},
    {"input-file", 'i', COLOR_CYAN "FILE", 0, COLOR_MAGENTA "Input file to be encrypted/decrypted" COLOR_RESET},
    {"encrypt-mode", 'm', COLOR_CYAN "MODE", 0, COLOR_MAGENTA "Mode to use/used in the encryption. Specify the number of the mode that you can see by using --list-modes command (Default: 0, CBC)" COLOR_RESET},
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
            arguments->encryptFlag = 1;
            if (arg)
                arguments->encrypt = arg;
            break;
        
        case 'd':
            arguments->decryptFlag = 1;
            if (arg)
                arguments->decrypt = arg;
            break;
        
        case 'k':
            arguments->cipherKeyFlag = 1;
            arguments->cipherKey = arg;
            break;
        
        case 'i':
            arguments->inputFileFlag = 1;
            arguments->inputFile = arg;
            break;

        case 'm':
            arguments->mode = atoi(arg);
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
    arguments->mode = 0;
    arguments->encryptFlag = 0;
    arguments->decryptFlag = 0;
    arguments->cipherKeyFlag = 0;
    arguments->inputFileFlag = 0;
    arguments->encrypt = "";
    arguments->cipherKey = "";
    arguments->inputFile = "";
    arguments->decrypt = "";
}

void listCryptographicModes(void)
{
    printf(
        "╔═══════════════════════════════╗\n"
        "║0\t" COLOR_GREEN "CBC(CipherBlockChaining)" COLOR_RESET "║\n"
        "╚═══════════════════════════════╝\n"
    );
}

int handleArgs(int argc, char ** argv)
{
    struct arguments arguments;
    initArgumentsStructure(&arguments);

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if(arguments.listModes)
    {
        listCryptographicModes();
        return EXIT_SUCCESS;
    }

    //FILE MODE
    if (strcmp(arguments.inputFile, "") && arguments.inputFileFlag)
    {
        if(!strcmp(arguments.encrypt, "") && arguments.encryptFlag)
        {
            if (strcmp(arguments.cipherKey, "") && arguments.cipherKeyFlag)
            {
                CipherData data = { 0 };
                Block cipherKey = sha3CipherKeyBlock(arguments.cipherKey);
                initCipher(&data, &cipherKey);
                encryptFile(&data, &initVect, arguments.inputFile, arguments.mode);
                return EXIT_SUCCESS;
            }
            else
            {
                fprintf(stderr, "[" COLOR_RED "!" COLOR_RESET "] You must specify the cipherkey\n");
                return EXIT_FAILURE;
            }
        }

        else if (!strcmp(arguments.decrypt, "") && arguments.decryptFlag)
        {
            if (strcmp(arguments.cipherKey, "") && arguments.cipherKeyFlag)
            {
                CipherData data = { 0 };
                Block cipherKey = sha3CipherKeyBlock(arguments.cipherKey);
                initCipher(&data, &cipherKey);
                decryptFile(&data, &initVect, arguments.inputFile, arguments.mode);
                return EXIT_SUCCESS;
            }
            else
            {
                fprintf(stderr, "[" COLOR_RED "!" COLOR_RESET "] You must specify the cipherkey\n");
                return EXIT_FAILURE;
            }
        }

        else
        {
            fprintf(stderr, "[" COLOR_RED "!" COLOR_RESET "] You must specify the task: encrypt/decrypt\n");
            return EXIT_FAILURE;
        }
    }

    if(strcmp(arguments.encrypt, "") && arguments.encryptFlag)
    {
        if (strcmp(arguments.cipherKey, "") && arguments.cipherKeyFlag)
        {
            CipherData data = { 0 };
            Block cipherKey = sha3CipherKeyBlock(arguments.cipherKey);
            initCipher(&data, &cipherKey);
            encryptString(&data, &initVect, arguments.encrypt, arguments.mode);
            return EXIT_SUCCESS;
        }

        else
        {
            fprintf(stderr, "[" COLOR_RED "!" COLOR_RESET "] You must specify the cipherkey\n");
            return EXIT_FAILURE;
        }
    }

    if(strcmp(arguments.decrypt, "") && arguments.decryptFlag)
    {
        if (strcmp(arguments.cipherKey, "") && arguments.cipherKeyFlag)
        {
            CipherData data = { 0 };
            Block cipherKey = sha3CipherKeyBlock(arguments.cipherKey);
            initCipher(&data, &cipherKey);
            decryptString(&data, &initVect, arguments.decrypt, arguments.mode);
            return EXIT_SUCCESS;
        }

        else
        {
            fprintf(stderr, "[" COLOR_RED "!" COLOR_RESET "] You must specify the cipherkey\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_FAILURE;
}