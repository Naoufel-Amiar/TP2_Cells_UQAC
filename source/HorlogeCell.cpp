#include "HorlogeCell.h"
#include <stdexcept>


HorlogeCell::HorlogeCell()
    : heures_(0), minutes_(0)
{
    setHeures(0);
    setMinutes(0);
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

HorlogeCell HorlogeCell::operator+(const HorlogeCell& C1, const HorlogeCell& C2)
{
    int M1 = C1.getHeures()*60 + C1.getMinutes();
    int M2 = C2.getHeures()*60 + C2.getMinutes();
    int M3 = 0;
    int recul = 0;
    int avance = (M1 - M2 + 1440) % 1440;

    if (avance <= 720){
        M3 = (M1 + avance) / 2;
    }
    else{
        recul = 1440 - avance;
        M3 = M1 - recul / 2;
    }
    M3 = (M3 + 1440) % 1440;
    return HorlogeCell(M3 / 60, M3 % 60);
}