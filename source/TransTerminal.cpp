#include "TransTerminal.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace
{
    template<typename T>
    T lireValeur(const std::string& texte)
    {
        std::istringstream flux(texte);
        T valeur;

        if (!(flux >> valeur))
        {
            throw std::invalid_argument(
                "Valeurs de cellule invalides : " + texte
            );
        }

        flux >> std::ws;

        if (!flux.eof())
        {
            throw std::invalid_argument(
                "Donnees supplementaires : " + texte
            );
        }

        return valeur;
    }

    void verifierFin(std::istringstream& flux)
    {
        flux >> std::ws;

        if (!flux.eof())
        {
            throw std::invalid_argument(
                "Arguments supplementaires dans la transaction."
            );
        }
    }
}

// ==========================================
// CREATION / REMPLACEMENT DE POPULATION
// ==========================================

void TransTerminal::creerPopulation(TypeCourant type)
{
    populationColor_.reset();
    populationChromo_.reset();

    typeCourant_ = TypeCourant::Aucun;

    if (type == TypeCourant::ColorCell)
    {
        populationColor_ =
            std::make_unique<Population<ColorCell>>();
    }
    else if (type == TypeCourant::ChromoCell)
    {
        populationChromo_ =
            std::make_unique<Population<ChromoCell>>();
    }
    else
    {
        throw std::invalid_argument(
            "Type de population inconnu."
        );
    }

    typeCourant_ = type;
}

// ==========================================
// COMMANDE C : CREER UNE POPULATION
// ==========================================

void TransTerminal::commandeCreer(const std::string& type)
{
    if (type == "COLORCELL")
    {
        creerPopulation(TypeCourant::ColorCell);
    }
    else if (type == "CHROMOCELL")
    {
        creerPopulation(TypeCourant::ChromoCell);
    }
    else
    {
        throw std::invalid_argument(
            "Type inconnu : " + type
        );
    }

    std::cout << "Population creee : " << type << '\n';
}

// ==========================================
// COMMANDE A : AJOUTER UN INDIVIDU
// ==========================================

void TransTerminal::commandeAjouter(
    const std::string& valeurs
)
{
    if (typeCourant_ == TypeCourant::ColorCell)
    {
        ColorCell cellule =
            lireValeur<ColorCell>(valeurs);

        int id = populationColor_->ajouter(cellule);

        std::cout << id << " : " << cellule << '\n';
    }
    else if (typeCourant_ == TypeCourant::ChromoCell)
    {
        ChromoCell cellule =
            lireValeur<ChromoCell>(valeurs);

        int id = populationChromo_->ajouter(cellule);

        std::cout << id << " : " << cellule << '\n';
    }
    else
    {
        throw std::runtime_error(
            "Aucune population courante. Utilisez C ou O."
        );
    }
}

// ==========================================
// COMMANDE O : OUVRIR UNE POPULATION
// ==========================================

void TransTerminal::commandeOuvrir(
    const std::string& fichier
)
{
    std::ifstream entree(fichier);

    if (!entree)
    {
        throw std::runtime_error(
            "Impossible d'ouvrir : " + fichier
        );
    }

    std::string type;
    std::size_t nombre = 0;

    if (!(entree >> type >> nombre))
    {
        throw std::runtime_error(
            "En-tete de population invalide."
        );
    }

    // Charger avant de remplacer la population
    // courante pour eviter de perdre les donnees
    // si la lecture echoue.

    if (type == "COLORCELL")
    {
        auto nouvelle =
            std::make_unique<Population<ColorCell>>();

        nouvelle->charger(entree, nombre);

        populationColor_ = std::move(nouvelle);
        populationChromo_.reset();

        typeCourant_ = TypeCourant::ColorCell;
    }
    else if (type == "CHROMOCELL")
    {
        auto nouvelle =
            std::make_unique<Population<ChromoCell>>();

        nouvelle->charger(entree, nombre);

        populationChromo_ = std::move(nouvelle);
        populationColor_.reset();

        typeCourant_ = TypeCourant::ChromoCell;
    }
    else
    {
        throw std::invalid_argument(
            "Type du fichier inconnu : " + type
        );
    }

    std::cout
        << "Population chargee : " << type
        << " (" << nombre << " individus)\n";
}

// ==========================================
// COMMANDE S : SAUVEGARDER
// ==========================================

void TransTerminal::commandeSauvegarder(
    const std::string& fichier
)
{
    if (typeCourant_ == TypeCourant::Aucun)
    {
        throw std::runtime_error(
            "Aucune population courante."
        );
    }

    std::ofstream sortie(fichier);

    if (!sortie)
    {
        throw std::runtime_error(
            "Impossible de creer : " + fichier
        );
    }

    if (typeCourant_ == TypeCourant::ColorCell)
    {
        populationColor_->sauvegarder(
            sortie, "COLORCELL"
        );
    }
    else
    {
        populationChromo_->sauvegarder(
            sortie, "CHROMOCELL"
        );
    }

    sortie.close();

    if (!sortie)
    {
        throw std::runtime_error(
            "Echec de la sauvegarde : " + fichier
        );
    }

    std::cout
        << "Population sauvegardee : "
        << fichier << '\n';
}

// ==========================================
// COMMANDE + : COMBINER
// ==========================================

void TransTerminal::commandeCombiner(int id1, int id2)
{
    if (typeCourant_ == TypeCourant::ColorCell)
    {
        int id = populationColor_->combiner(id1, id2);

        std::cout << id << " : "
                  << populationColor_->trouver(id)->getValeur()
                  << " (" << id1 << " + " << id2 << ")\n";
    }
    else if (typeCourant_ == TypeCourant::ChromoCell)
    {
        int id = populationChromo_->combiner(id1, id2);

        std::cout << id << " : "
                  << populationChromo_->trouver(id)->getValeur()
                  << " (" << id1 << " + " << id2 << ")\n";
    }
    else
    {
        throw std::runtime_error(
            "Aucune population courante."
        );
    }
}

// ==========================================
// COMMANDE - : SUPPRIMER
// ==========================================

void TransTerminal::commandeSupprimer(int id)
{
    bool supprime = false;

    if (typeCourant_ == TypeCourant::ColorCell)
    {
        supprime = populationColor_->supprimer(id);
    }
    else if (typeCourant_ == TypeCourant::ChromoCell)
    {
        supprime = populationChromo_->supprimer(id);
    }
    else
    {
        throw std::runtime_error(
            "Aucune population courante."
        );
    }

    if (!supprime)
    {
        throw std::invalid_argument(
            "Individu introuvable : " + std::to_string(id)
        );
    }

    std::cout << "Individu " << id << " supprime.\n";
}

// ==========================================
// COMMANDE ? : ANCETRE COMMUN
// ==========================================

void TransTerminal::commandeAncetre(int id1, int id2)
{
    std::optional<AncetreCommun> ancetre;

    if (typeCourant_ == TypeCourant::ColorCell)
    {
        ancetre =
            populationColor_->rechercherAncetreCommun(
                id1, id2
            );
    }
    else if (typeCourant_ == TypeCourant::ChromoCell)
    {
        ancetre =
            populationChromo_->rechercherAncetreCommun(
                id1, id2
            );
    }
    else
    {
        throw std::runtime_error(
            "Aucune population courante."
        );
    }

    if (!ancetre)
    {
        std::cout
            << "Aucun ancetre commun entre "
            << id1 << " et " << id2 << ".\n";

        return;
    }

    std::cout
        << "Ancetre commun de "
        << id1 << " et " << id2
        << " : " << ancetre->id << " (";

    if (typeCourant_ == TypeCourant::ColorCell)
    {
        std::cout
            << populationColor_
                   ->trouver(ancetre->id)
                   ->getValeur();
    }
    else
    {
        std::cout
            << populationChromo_
                   ->trouver(ancetre->id)
                   ->getValeur();
    }

    std::cout << ")\n";

    std::cout
        << id1 << " est a "
        << ancetre->distance1
        << " generation(s) de "
        << ancetre->id << ".\n";

    std::cout
        << id2 << " est a "
        << ancetre->distance2
        << " generation(s) de "
        << ancetre->id << ".\n";
}

// ==========================================
// COMMANDE $ : AFFICHER L'ARBRE
// ==========================================

void TransTerminal::commandeAfficher(int id)
{
    if (typeCourant_ == TypeCourant::ColorCell)
    {
        populationColor_->afficherArbre(
            id, std::cout
        );
    }
    else if (typeCourant_ == TypeCourant::ChromoCell)
    {
        populationChromo_->afficherArbre(
            id, std::cout
        );
    }
    else
    {
        throw std::runtime_error(
            "Aucune population courante."
        );
    }
}

// ==========================================
// ANALYSE D'UNE TRANSACTION
// ==========================================

void TransTerminal::traiterLigne(
    const std::string& ligne
)
{
    std::istringstream flux(ligne);

    std::string operation;

    if (!(flux >> operation) || operation[0] == '#')
        return;

    if (operation == "C" ||
        operation == "O" ||
        operation == "S")
    {
        std::string argument;

        if (!(flux >> argument))
        {
            throw std::invalid_argument(
                "Argument manquant pour " + operation
            );
        }

        verifierFin(flux);

        if (operation == "C")
            commandeCreer(argument);
        else if (operation == "O")
            commandeOuvrir(argument);
        else
            commandeSauvegarder(argument);
    }
    else if (operation == "A")
    {
        std::string valeurs;

        std::getline(flux >> std::ws, valeurs);

        if (valeurs.empty())
        {
            throw std::invalid_argument(
                "Valeurs manquantes pour A."
            );
        }

        commandeAjouter(valeurs);
    }
    else if (operation == "+" || operation == "?")
    {
        int x, y;

        if (!(flux >> x >> y))
        {
            throw std::invalid_argument(
                "Deux identifiants requis pour " + operation
            );
        }

        verifierFin(flux);

        if (operation == "+")
            commandeCombiner(x, y);
        else
            commandeAncetre(x, y);
    }
    else if (operation == "-" || operation == "$")
    {
        int id;

        if (!(flux >> id))
        {
            throw std::invalid_argument(
                "Un identifiant est requis pour " + operation
            );
        }

        verifierFin(flux);

        if (operation == "-")
            commandeSupprimer(id);
        else
            commandeAfficher(id);
    }
    else
    {
        throw std::invalid_argument(
            "Operation inconnue : " + operation
        );
    }
}

// ==========================================
// EXECUTION DU FICHIER TRANSACTIONS
// ==========================================

void TransTerminal::executer(
    const std::string& fichierTransactions
)
{
    std::ifstream fichier(fichierTransactions);

    if (!fichier)
    {
        throw std::runtime_error(
            "Impossible d'ouvrir les transactions : " +
            fichierTransactions
        );
    }

    std::string ligne;
    std::size_t numero = 0;

    while (std::getline(fichier, ligne))
    {
        ++numero;

        try
        {
            traiterLigne(ligne);
        }
        catch (const std::exception& erreur)
        {
            // Une transaction invalide ne bloque
            // pas les transactions suivantes.
            std::cerr
                << "[ERREUR ligne " << numero << "] "
                << erreur.what() << '\n';
        }
    }

    if (fichier.bad())
    {
        throw std::runtime_error(
            "Erreur de lecture du fichier de transactions."
        );
    }
}
