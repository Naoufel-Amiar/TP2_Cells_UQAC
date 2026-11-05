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
    ChromoCell();

    ChromoCell(
        const std::string& paire1,
        const std::string& paire2,
        const std::string& paire3,
        const std::string& paire4);

    const std::array<std::string, 4>& getPaires() const;

    void setPaires(const std::array<std::string, 4>& paires);

    ChromoCell operator+(const ChromoCell& autre) const;

    friend std::istream& operator>>(
        std::istream& entree, ChromoCell& cellule);

    friend std::ostream& operator<<(
        std::ostream& sortie, const ChromoCell& cellule);
};

#endif
