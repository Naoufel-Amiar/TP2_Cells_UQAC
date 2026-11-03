#ifndef TRANS_TERMINAL_H
#define TRANS_TERMINAL_H

#include <memory>
#include <string>

#include "ColorCell.h"
#include "ChromoCell.h"
#include "Population.h"

class TransTerminal
{
private:
    // Type de cellule actuellement selectionne
    enum class TypeCourant
    {
        Aucun,
        ColorCell,
        ChromoCell
    };

    TypeCourant typeCourant_ = TypeCourant::Aucun;

    // Populations des deux types
    std::unique_ptr<Population<ColorCell>>
        populationColor_;

    std::unique_ptr<Population<ChromoCell>>
        populationChromo_;

    // Initialisation d'une population
    void creerPopulation(TypeCourant type);

    // Traitement d'une transaction
    void traiterLigne(const std::string& ligne);

    // Commandes du fichier TRANSACTIONS
    void commandeCreer(const std::string& type);

    void commandeAjouter(const std::string& valeurs);

    void commandeOuvrir(const std::string& fichier);

    void commandeSauvegarder(const std::string& fichier);

    void commandeCombiner(int id1, int id2);

    void commandeSupprimer(int id);

    void commandeAncetre(int id1, int id2);

    void commandeAfficher(int id);

public:
    // Constructeur et destructeur
    TransTerminal() = default;
    ~TransTerminal() = default;

    // Lecture et execution des transactions
    void executer(
        const std::string& fichierTransactions
    );
};

#endif
