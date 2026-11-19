#include "HorlogeCell.h"
#include <stdexcept>
#include <iomanip>



HorlogeCell::HorlogeCell()
    : heures_(0), minutes_(0)
{
    setHeures(0);
    setMinutes(0);
}

HorlogeCell::HorlogeCell(int heures, int minutes)
    : heures_(0), minutes_(0)
{
    setHeures(heures);
    setMinutes(minutes);
}

int HorlogeCell::getHeures() const
{
    return heures_;
}

int HorlogeCell::getMinutes() const
{
    return minutes_;
}

void HorlogeCell::setHeures(int heures)
{
    if (heures < 0 || heures > 23)
    {
        throw std::out_of_range(
            "Les heures doivent etre entre 0 et 23.");
    }

    heures_ = heures;
}

void HorlogeCell::setMinutes(int minutes)
{
    if (minutes < 0 || minutes > 59)
    {
        throw std::out_of_range(
            "Les minutes doivent etre entre 0 et 59.");
    }

    minutes_ = minutes;
}

HorlogeCell HorlogeCell::operator+(const HorlogeCell& autre) const
{
    int M1 = getHeures()*60 + getMinutes();
    int M2 = autre.getHeures()*60 + autre.getMinutes();
    int M3 = 0;
    int recul = 0;
    int avance = (M2 - M1 + 1440) % 1440;

    if (avance <= 720){
        M3 = M1 + (avance / 2);
    }
    else{
        recul = 1440 - avance;
        M3 = M1 - (recul / 2);
    }
    M3 = (M3 + 1440) % 1440;
    return HorlogeCell(M3 / 60, M3 % 60);
}

std::istream& operator>>(std::istream& entree, HorlogeCell& cellule)
{
    int heures;
    char separateur;
    int minutes;

    if (entree >> heures >> separateur >> minutes && separateur == ':'){
        try{
            cellule.setHeures(heures);
            cellule.setMinutes(minutes);
        }
        catch (const std::out_of_range& e){
            entree.setstate(std::ios::failbit);
        }
    }
    else {
        entree.setstate(std::ios::failbit);
    }
    return entree;
    
}

std::ostream& operator<<(std::ostream& sortie, const HorlogeCell& cellule)
{
    sortie << std::setfill('0')
           << std::setw(2) << cellule.heures_
           << ":"
           << std::setw(2) << cellule.minutes_;

    sortie << std::setfill(' ');

    return sortie;
}