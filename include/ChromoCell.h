#ifndef CHROMOCELL_H
#define CHROMOCELL_H

#include <array>
#include <iostream>
#include <string>

class ChromoCell
{
private:
    std::array<std::string, 4> paires_;

public:
    // Constructeurs
    ChromoCell();

    ChromoCell(
        const std::string& paire1,
        const std::string& paire2,
        const std::string& paire3,
        const std::string& paire4
    );

    // Accesseurs
    const std::array<std::string, 4>&
    getPaires() const;

    // Modification et validation
    void setPaires(
        const std::array<std::string, 4>& paires
    );

    // Combinaison chromosomique
    ChromoCell operator+(const ChromoCell& autre) const;

    // Lecture et affichage textuels
    friend std::istream& operator>>(
        std::istream& entree,
        ChromoCell& cellule
    );

    friend std::ostream& operator<<(
        std::ostream& sortie,
        const ChromoCell& cellule
    );
};

#endif
