# PandaCipher

---

## Authors: <br/><br/> [Raphael Dray](www.linkedin.com/in/raphaeldray), [Alex Samenaire](https://www.linkedin.com/in/alexsamenaire/) <br/>

---

## Introduction:

> This program is a CLI application. <br/> <br/>
> It allows to encrypt/decrypt a string/file using its own cipher method defined by: XORing, Substitutions and Permutations. <br/> <br/>
> The avaible encryption modes are as follow:
> + CBC

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