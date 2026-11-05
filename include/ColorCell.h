#ifndef COLORCELL_H
#define COLORCELL_H

#include <iostream>

class ColorCell
{
private:
    int rouge_;
    int vert_;
    int bleu_;

public:
    ColorCell();
    ColorCell(int rouge, int vert, int bleu);

    int getRouge() const;
    int getVert() const;
    int getBleu() const;

    void setRGB(int rouge, int vert, int bleu);

    ColorCell operator+(const ColorCell& autre) const;

    friend std::istream& operator>>(
        std::istream& entree, ColorCell& cellule);

    friend std::ostream& operator<<(
        std::ostream& sortie, const ColorCell& cellule);
};

#endif
