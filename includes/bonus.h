
/// @file bonus.h
/// @defgroup Bonus
/// @{

#ifndef _BONUS_H_
#define _BONUS_H_

#include "cipher.h"

//-------------------------------------------------------------------------------------------------
//  Cryptanalyse différentielle

/// @brief Structure représentant la table différentielle d'une S-box.
typedef struct DiffTable_s
{
    /// @brief Nombre de bits de la S-box.
    int   nbBits;

    /// @brief Nombre d'entrées ou sorties possibles pour la S-box (= 2^nbBits).
    int   nbElts;

    /// @brief Tableau 2D de taille [nbElts][nbElts].
    /// La case coeffs[a][b] donne la probabilité de la différentielle de la S-box
    /// ayant 'a' comme motif d'entrée et 'b' comme motif de sortie multipliée par nbElts
    /// pour obtenir un coefficient entre 0 et nbElts inclus.
    int **coeffs;

    /// @brief Le coefficient maximal de la table pour des motifs non nuls.
    /// Représente la résistance de la S-box à la cryptanalyse différentielle.
    int   max;
} DiffTable;

/// @brief Alloue une table différentielle.
/// La table peut ensuite être initialisée avec la fonction initDiffTable().
/// @param[in] nbBits le nombre de bits des potentielles S-boxes associées.
/// @return La table différentielle ou NULL en cas d'erreur.
DiffTable *newDiffTable(int nbBits);

/// @brief Détruit une table différentielle.
/// La table doit être préalablement allouée avec newDiffTable().
/// @param[in,out] diffTable la table à détruire.
void freeDiffTable(DiffTable *diffTable);

/// @brief Initialise la table avec une S-box.
/// La table doit être préalablement allouée avec newDiffTable().
/// Le nombre de bits de la table doit correspondre au nombre de bits de la S-box.
/// @param[out] diffTable la table à initialiser.
/// @param[in]  sBox      la S-box dont on veut calculer la table différentielle.
void initDiffTable(DiffTable *diffTable, int *sBox);

/// @brief Génère une S-box aléatoire.
/// @param[out] sBox   la S-box générée.
///                    Le tableau doit impérativement avoir (au moins) 2^nbBits cases. 
/// @param[in]  nbBits le nombre de bits de la S-box.
void randomSBox(int * sBox, int nbBits);

//-------------------------------------------------------------------------------------------------
//  Fonction de chiffrement optimisée

/// @brief Structure contenant les informations nécessaires au chiffrement pour chiffrer ou déchiffrer un bloc.
/// Elle contient en particulier les clés de rondes calculée avec la fonction initFastCipher().
/// Vous pouvez modifier les champs de cette structure.
typedef struct FastCipherData_s
{
    /// @brief Les clés des rondes calculées lors du dernier appel à initFastCipher().
    Block roundKeys[NB_ROUNDS + 1];
} FastCipherData;

/// @brief Initialise une structure FastCipherData.
/// Cette fonction permet de spécifier la clé de chiffrement à utiliser pour chiffrer/déchiffrer un bloc.
/// Elle réalise également les éventuels précalculs pour accélerer le chiffrement.
/// @param[out]    data      la structure à initialiser.
/// @param[in]     cipherKey la clé de chiffrement.
void initFastCipher(FastCipherData *data, Block *cipherKey);

/// @brief Chiffre un bloc avec la clé spécifiée dans la structure CipherData.
/// Cette fonction représente votre chiffrement optimisé.
/// @param[in]     data  les données nécessaires pour le chiffrement.
///                      Cette structure doit être initialisée avec la fonction initCipher().
/// @param[in,out] block le bloc à chiffrer.
void fastEncryptBlock(FastCipherData *data, Block *block);

void swap(int * a, int * b);
void shuffle(int * sBox, unsigned int size);
void littleShuffle(int * sBox, unsigned int size, float percent);
int numberOfMax(int * sBox, unsigned int size, unsigned int max);


#endif // !_BONUS_H_

/// @}