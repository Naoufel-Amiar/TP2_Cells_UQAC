
#include "ChromoCell.h"

#include <stdexcept>

// ==========================================
// CONSTRUCTEURS
// ==========================================

ChromoCell::ChromoCell()
    : paires_{"AA", "AA", "AA", "AA"}
{
}

ChromoCell::ChromoCell(
    const std::string& paire1,
    const std::string& paire2,
    const std::string& paire3,
    const std::string& paire4
)
{
    setPaires({paire1, paire2, paire3, paire4});
}

// ==========================================
// ACCESSEURS
// ==========================================

const std::array<std::string, 4>&
ChromoCell::getPaires() const
{
    return paires_;
}

// ==========================================
// MODIFICATION ET VALIDATION
// ==========================================

void ChromoCell::setPaires(
    const std::array<std::string, 4>& paires
)
{
    for (const std::string& paire : paires)
    {
        if (paire.size() != 2)
        {
            throw std::invalid_argument(
                "Une paire doit contenir deux chromosomes."
            );
        }

        for (char chromosome : paire)
        {
            if (chromosome < 'A' || chromosome > 'L')
            {
                throw std::invalid_argument(
                    "Chromosome invalide : lettres A a L uniquement."
                );
            }
        }
    }

    paires_ = paires;
}

// ==========================================
// ADDITION DE DEUX CELLULES
// ==========================================

ChromoCell ChromoCell::operator+(
    const ChromoCell& autre
) const
{
    std::array<std::string, 4> resultat;

    for (std::size_t i = 0; i < 4; ++i)
    {
        resultat[i] =
            std::string(1, paires_[i][0]) +
            autre.paires_[i][1];
    }

    ChromoCell nouvelleCellule;
    nouvelleCellule.setPaires(resultat);

    return nouvelleCellule;
}

// ==========================================
// LECTURE TEXTUELLE
// ==========================================

std::istream& operator>>(
    std::istream& entree,
    ChromoCell& cellule
)
{
    std::array<std::string, 4> paires;

    if (entree >> paires[0] >> paires[1]
               >> paires[2] >> paires[3])
    {
        try
        {
            cellule.setPaires(paires);
        }
        catch (const std::invalid_argument&)
        {
            entree.setstate(std::ios::failbit);
        }
    }

    return entree;
}

// ==========================================
// AFFICHAGE TEXTUEL
// ==========================================

std::ostream& operator<<(
    std::ostream& sortie,
    const ChromoCell& cellule
)
{
    for (std::size_t i = 0; i < 4; ++i)
    {
        if (i > 0)
        {
            sortie << " ";
        }

        sortie << cellule.paires_[i];
    }

    return sortie;
}
