# PandaCipher

---

## Authors: <br/><br/> [Raphael Dray](www.linkedin.com/in/raphaeldray), [Alex Samenaire](https://www.linkedin.com/in/alexsamenaire/) <br/>

---

## Introduction:

> This program is a CLI application. <br/> <br/>
> It allows to encrypt/decrypt a string/file using its own cipher method defined by: XORing, Substitutions and Permutations. <br/> <br/>
> The avaible encryption modes are as follow:
> + CBC

> In bonus.h, a function named getBestSBox(...) is defined but not used in the whole program. This function allow you to search in 2<sup>10</sup> tries 
```C
int * getBestSBox(int nbBits)
{
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
        littleShuffle(bestSBox, size, 0.50);

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
    return sBox;
}

```

> It's written in __C programming language including some libraries like so:__
> + [SHA3 - Keccak](https://github.com/brainhub/SHA3IUF)
> + [Argp](https://github.com/coreutils/gnulib/blob/master/lib/argp.h)

---

## Usage:

```
❯ ./pandaCipher --help
Usage: pandaCipher [OPTION...] ...args
PandaCipher - Symetrical encryption/decryption program
(https://github.com/MrrRaph/PandaCipher)

  -d, --decrypt[=DIGEST]
                             Specify decrypt mode
  -e, --encrypt[=STR]   Specify encrypt mode
  -i, --input-file=FILE Input file to be encrypted/decrypted
  -k, --cipher-key=KEY  Key for crypting
      --list-modes           Print cryptographic modes that can be
                             used
  -m, --encrypt-mode=MODE   Mode to use/used in the encryption.
                             Specify the number of the mode that you can see by
                             using --list-modes command (Default: 0, CBC)
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.

Report bugs to <dray@et.esiea.fr>|<samenaire@et.esiea.fr>.

```

### Example:

> You can encrypt/decrypt strings/files (with -i) on the command line.
> When encrypt/decrypt the program return the hex digest in case of non printable string when decrypting. Then you could use for example xxd with "-r -p" to convert hex string to string and recover the message.

```
❯ ./pandaCipher -e"Les Panda c'est la vie" -k "Pandanimal"
AA2D3C4CBC6D5E0C43ACC93AA22146DB47F54A9F9DE07175D3A2D92B8E898BE8
❯ ./pandaCipher -d"AA2D3C4CBC6D5E0C43ACC93AA22146DB47F54A9F9DE07175D3A2D92B8E898BE8" -k "Pandanimal"
4C65732050616E6461206327657374206C612076696500000000000000000000
❯ ./pandaCipher -d"AA2D3C4CBC6D5E0C43ACC93AA22146DB47F54A9F9DE07175D3A2D92B8E898BE8" -k "Pandanimal" | xxd -r -p
Les Panda c'est la vie%                                                       
```