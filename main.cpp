#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ColorCell.h"

int main()
{
    std::cout << "====================================\n";
    std::cout << "  TP2 - TESTS COLORCELL\n";
    std::cout << "====================================\n";

    // TEST 1 : Constructeur par defaut
    std::cout << "\n=== TEST 1 : CONSTRUCTEUR ===\n";

    ColorCell celluleDefaut;
    std::cout << "Cellule par defaut : "
              << celluleDefaut << "\n";

    // TEST 2 : Addition
    std::cout << "\n=== TEST 2 : ADDITION RGB ===\n";

    ColorCell cellule1(0, 0, 255);
    ColorCell cellule2(0, 255, 0);

    ColorCell resultat = cellule1 + cellule2;

    std::cout << "Cellule 1 : " << cellule1 << "\n";
    std::cout << "Cellule 2 : " << cellule2 << "\n";
    std::cout << "Resultat  : " << resultat << "\n";

    if (resultat.getRouge() == 0 &&
        resultat.getVert() == 127 &&
        resultat.getBleu() == 127)
    {
        std::cout << "[OK] Addition RGB correcte\n";
    }
    else
    {
        std::cout << "[ERREUR] Addition RGB incorrecte\n";
    }

    // TEST 3 : Modification RGB
    std::cout << "\n=== TEST 3 : SET RGB ===\n";

    celluleDefaut.setRGB(255, 128, 64);

    std::cout << "Nouvelle valeur : "
              << celluleDefaut << "\n";

    // TEST 4 : Lecture depuis un flux texte
    std::cout << "\n=== TEST 4 : LECTURE ===\n";

    std::istringstream flux("100 200 50");
    ColorCell celluleLue;

    if (flux >> celluleLue)
    {
        std::cout << "[OK] Lecture : "
                  << celluleLue << "\n";
    }
    else
    {
        std::cout << "[ERREUR] Lecture impossible\n";
    }

    // TEST 5 : Validation RGB
    std::cout << "\n=== TEST 5 : VALEURS INVALIDES ===\n";

    try
    {
        ColorCell celluleInvalide(300, 0, 0);

        std::cout << "[ERREUR] Valeur invalide acceptee\n";
    }
    catch (const std::out_of_range&)
    {
        std::cout << "[OK] Valeur invalide refusee\n";
    }

    // TEST 6 : Valeurs limites
    std::cout << "\n=== TEST 6 : LIMITES ===\n";

    ColorCell minimum(0, 0, 0);
    ColorCell maximum(255, 255, 255);

    std::cout << "Minimum : " << minimum << "\n";
    std::cout << "Maximum : " << maximum << "\n";

    std::cout << "\n====================================\n";
    std::cout << "  FIN DES TESTS COLORCELL\n";
    std::cout << "====================================\n";

    return 0;
}
