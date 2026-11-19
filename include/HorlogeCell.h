#ifndef HORLOGECELL_H
#define HORLOGECELL_H

#include <iostream>

class HorlogeCell
{
private:
    int heures_;
    int minutes_;

public:
    HorlogeCell();
    HorlogeCell(int heures, int minutes);

    int getHeures() const;
    int getMinutes() const;

    void setHeures(int heures);
    void setMinutes(int minutes);

    HorlogeCell operator+(const HorlogeCell& autre) const;

    friend std::istream& operator>>(
        std::istream& entree, HorlogeCell& cellule);
    friend std::ostream& operator<<(
        std::ostream& sortie, const HorlogeCell& cellule);
};

#endif