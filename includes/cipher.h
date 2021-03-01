
/// @file cipher.h
/// @defgroup Cipher
/// @{

#ifndef _CIPHER_H_
#define _CIPHER_H_

// Nombre de rondes de la fonction de chiffrement.
#define NB_ROUNDS 16

//-------------------------------------------------------------------------------------------------
//  Structures

/// @brief Type représentant un entier non signé codé sur 1 octet.
typedef unsigned char byte;

/// @brief La S-box du chiffrement.
extern byte sBox[256];

/// @brief L'inverse de la S-box du chiffrement.
extern byte invSBox[256];

/// @brief La permutation des bits du chiffrement
extern int perm[128];

/// @brief L'inverse de la permutation des bits du chiffrement
extern int invPerm[128];

/// @brief Structure représentant un bloc de donnée.
/// Il s'agit d'une zone mémoire contigüe de 128 bits regroupés en 16 paquets d'un octet.
typedef struct Block_s
{
    /// @brief Tableau contenant les 16 paquets du bloc.
    byte bundles[16];
} Block;

/// @brief Structure contenant les informations nécessaires au chiffrement pour chiffrer ou déchiffrer un bloc.
/// Elle contient les clés de rondes calculée avec la fonction initCipher().
/// @sa initCipher(), encryptBlock(), decryptBlock()
typedef struct CipherData_s
{
    /// @brief Les clés des rondes calculées lors du dernier appel à initCipher().
    Block roundKeys[NB_ROUNDS + 1];
} CipherData;

//-------------------------------------------------------------------------------------------------
//  Fonctions de chiffrement/déchiffrement

/// @brief Initialise une structure CipherData.
/// Cette fonction permet de spécifier la clé de chiffrement à utiliser pour chiffrer/déchiffrer un bloc.
/// @param[out]    data      la structure à initialiser.
/// @param[in]     cipherKey la clé de chiffrement.
void initCipher(CipherData *data, Block *cipherKey);

/// @brief Chiffre un bloc avec la clé spécifiée dans la structure CipherData.
/// @param[in]     data  les données nécessaires pour le chiffrement.
///                      Cette structure doit être initialisée avec la fonction initCipher().
/// @param[in,out] block le bloc à chiffrer.
void encryptBlock(CipherData *data, Block *block);

/// @brief Déchiffre un bloc avec la clé spécifiée dans la structure CipherData.
/// @param[in]     data  les données nécessaires pour le déchiffrement.
///                      Cette structure doit être initialisée avec la fonction initCipher().
/// @param[in,out] block le bloc à déchiffrer.
void decryptBlock(CipherData *data, Block *block);

/// @brief Chiffre un message composé de plusieurs blocs en utilisant le mode d'opération CBC.
/// @param[in]     data     les données nécessaires pour le chiffrement.
///                         Cette structure doit être initialisée avec la fonction initCipher().
/// @param[in]     iv       le vecteur d'initialisation du mode CBC.
/// @param[in,out] message  le message à chiffrer.
/// @param[in]     nbBlocks le nombre de blocs du message.
void encryptCBC(CipherData *data, Block *iv, Block *message, int nbBlocks);

/// @brief Déchiffre un message composé de plusieurs blocs en utilisant le mode d'opération CBC.
/// @param[in]     data     les données nécessaires pour le déchiffrement.
///                         Cette structure doit être initialisée avec la fonction initCipher().
/// @param[in]     iv       le vecteur d'initialisation du mode CBC.
/// @param[in,out] message  le message à déchiffrer.
/// @param[in]     nbBlocks le nombre de blocs du message.
void decryptCBC(CipherData *data, Block *iv, Block *message, int nbBlocks);

//-------------------------------------------------------------------------------------------------
//  Fonctions auxiliaires

/// @brief Fonction auxiliaire réalisation un ou exclusif bit-à-bit entre deux blocs.
/// @param[in,out] block le bloc auquel ajouter le second bloc. Cet arguement est modifié par la fonction.
/// @param[in]     value la valeur à ajouter au premier bloc.
void Block_xor(Block *block, Block *value);

/// @brief Réalise la couche de substitution du chiffrement.
/// @param[in,out] block le bloc auquel appliquer la substitution.
void Block_substitution(Block *block);

/// @brief Réalise la couche de permutation du chiffrement
/// @param[in,out] block le bloc auquel appliquer la permutation des bits.
void Block_permutation(Block *block);

/// @brief Réalise la couche de substitution du déchiffrement.
/// @param[in,out] block le bloc auquel appliquer la substitution inverse.
void Block_invSubstitution(Block *block);

/// @brief Réalise la couche de permutation du déchiffrement
/// @param[in,out] block le bloc auquel appliquer la permutation inverse des bits.
void Block_invPermutation(Block *block);

/// @brief Affiche les valeurs des octets d'un bloc.
/// @param[in]     block le bloc à afficher.
void printBlock(Block *block);

#endif

/// @}
