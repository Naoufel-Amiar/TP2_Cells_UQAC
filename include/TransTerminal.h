#ifndef TRANS_TERMINAL_H
#define TRANS_TERMINAL_H

#include <memory>
#include <string>

#include "ChromoCell.h"
#include "ColorCell.h"
#include "Population.h"

class TransTerminal
{
private:
    enum class TypeCourant
    {
        Aucun,
        ColorCell,
        ChromoCell
    };

    TypeCourant typeCourant_ = TypeCourant::Aucun;

    std::unique_ptr<Population<ColorCell>>
        populationColor_;

    std::unique_ptr<Population<ChromoCell>>
        populationChromo_;

    void creerPopulation(TypeCourant type);

    void traiterLigne(const std::string& ligne);

    void commandeCreer(const std::string& type);

    void commandeAjouter(const std::string& valeurs);

    void commandeOuvrir(const std::string& fichier);

    void commandeSauvegarder(const std::string& fichier);

    void commandeCombiner(int id1, int id2);

    void commandeSupprimer(int id);

    void commandeAncetre(int id1, int id2);

    void commandeAfficher(int id);

public:
    TransTerminal() = default;
    ~TransTerminal() = default;

    void executer(
        const std::string& fichierTransactions
    );
};

#endif
