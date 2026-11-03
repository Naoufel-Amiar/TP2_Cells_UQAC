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
    // Constructeurs
    ColorCell();
    ColorCell(int rouge, int vert, int bleu);

    // Accesseurs
    int getRouge() const;
    int getVert() const;
    int getBleu() const;

    // Modification des composantes
    void setRGB(int rouge, int vert, int bleu);

    // Addition de deux cellules RGB
    ColorCell operator+(const ColorCell& autre) const;

    // Lecture et affichage textuels
    friend std::istream& operator>>(
        std::istream& entree,
        ColorCell& cellule
    );

    friend std::ostream& operator<<(
        std::ostream& sortie,
        const ColorCell& cellule
    );
};

#endif
