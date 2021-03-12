#include "../includes/argutils.h"

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