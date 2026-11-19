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

