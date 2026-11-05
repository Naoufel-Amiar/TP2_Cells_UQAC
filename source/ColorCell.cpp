#include "ColorCell.h"
#include <stdexcept>

ColorCell::ColorCell()
    : rouge_(0), vert_(0), bleu_(0)
{
}

ColorCell::ColorCell(int rouge, int vert, int bleu)
    : rouge_(0), vert_(0), bleu_(0)
{
    setRGB(rouge, vert, bleu);
}

int ColorCell::getRouge() const
{
    return rouge_;
}

int ColorCell::getVert() const
{
    return vert_;
}

int ColorCell::getBleu() const
{
    return bleu_;
}

void ColorCell::setRGB(int rouge, int vert, int bleu)
{
    if (rouge < 0 || rouge > 255 ||
        vert < 0 || vert > 255 ||
        bleu < 0 || bleu > 255)
    {
        throw std::out_of_range(
            "Les composantes RGB doivent etre entre 0 et 255.");
    }

    rouge_ = rouge;
    vert_ = vert;
    bleu_ = bleu;
}

ColorCell ColorCell::operator+(const ColorCell& autre) const
{
    return ColorCell(
        (rouge_ + autre.rouge_) / 2,
        (vert_ + autre.vert_) / 2,
        (bleu_ + autre.bleu_) / 2
    );
}

std::istream& operator>>(std::istream& entree, ColorCell& cellule)
{
    int rouge, vert, bleu;

    if (entree >> rouge >> vert >> bleu)
    {
        try
        {
            cellule.setRGB(rouge, vert, bleu);
        }
        catch (const std::out_of_range&)
        {
            entree.setstate(std::ios::failbit);
        }
    }

    return entree;
}

std::ostream& operator<<(std::ostream& sortie, const ColorCell& cellule)
{
    sortie << cellule.rouge_ << " "
           << cellule.vert_ << " "
           << cellule.bleu_;

    return sortie;
}
