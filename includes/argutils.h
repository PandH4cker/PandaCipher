#ifndef ARGUTILS_H
#define ARGUTILS_H

#include <argp.h>

#define OPT_LIST_MODES 500

extern const char * argp_program_version;
extern const char doc[];
extern const char * argp_program_bug_address;
extern const char args_doc[];
extern const struct argp_option options[];
extern struct argp argp;


struct arguments
{
    int listModes, encryptFlag, decryptFlag, 
        cipherKeyFlag, inputFileFlag;
    char * args;
    char * encrypt;
    char * decrypt;
    char * cipherKey;
    char * inputFile;
    char ** strings;
};

error_t parse_opt(int key, char * arg, struct argp_state * state);
void listCryptographicModes(void);
void initArgumentsStructure(struct arguments * arguments);
int handleArgs(int argc, char ** argv);

#endif