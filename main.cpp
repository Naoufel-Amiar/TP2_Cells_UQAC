
#include <iostream>

#include "ColorCell.h"
#include "ChromoCell.h"
#include "Individu.h"

int main()
{
    std::cout << "====================================\n";
    std::cout << "  TP2 - TESTS INDIVIDU<T>\n";
    std::cout << "====================================\n";

    // ======================================
    // TEST 1 : INDIVIDUS SANS PARENTS
    // ======================================

    std::cout << "\n=== TEST 1 : CREATION ===\n";

    Individu<ColorCell> individu1(
        1, ColorCell(0, 0, 255)
    );

    Individu<ColorCell> individu2(
        2, ColorCell(0, 255, 0)
    );

    std::cout << "Individu "
              << individu1.getId()
              << " : "
              << individu1.getValeur()
              << "\n";

    std::cout << "Individu "
              << individu2.getId()
              << " : "
              << individu2.getValeur()
              << "\n";

    if (individu1.getParent1() == nullptr &&
        individu1.getParent2() == nullptr)
    {
        std::cout << "[OK] Individu sans parents\n";
    }
    else
    {
        std::cout << "[ERREUR] Parents incorrects\n";
    }

    // ======================================
    // TEST 2 : CREATION D'UN DESCENDANT
    // ======================================

    std::cout << "\n=== TEST 2 : DESCENDANT ===\n";

    ColorCell valeur3 =
        individu1.getValeur() + individu2.getValeur();

    Individu<ColorCell> individu3(
        3,
        valeur3,
        &individu1,
        &individu2
    );

    std::cout << "Individu "
              << individu3.getId()
              << " : "
              << individu3.getValeur()
              << "\n";

    if (individu3.getParent1() == &individu1 &&
        individu3.getParent2() == &individu2)
    {
        std::cout << "[OK] Parents correctement lies\n";
    }
    else
    {
        std::cout << "[ERREUR] Liens incorrects\n";
    }

    // ======================================
    // TEST 3 : ACCES AUX PARENTS
    // ======================================

    std::cout << "\n=== TEST 3 : GENEALOGIE ===\n";

    std::cout << "Parent 1 : "
              << individu3.getParent1()->getId()
              << "\n";

    std::cout << "Parent 2 : "
              << individu3.getParent2()->getId()
              << "\n";

    // ======================================
    // TEST 4 : MODIFICATION D'UN PARENT
    // ======================================

    std::cout << "\n=== TEST 4 : MODIFICATION ===\n";

    individu3.setParent1(nullptr);

    if (individu3.getParent1() == nullptr &&
        individu3.getParent2() == &individu2)
    {
        std::cout << "[OK] Parent 1 devenu inconnu\n";
    }
    else
    {
        std::cout << "[ERREUR] Modification incorrecte\n";
    }

    // ======================================
    // TEST 5 : TYPE CHROMOCELL
    // ======================================

    std::cout << "\n=== TEST 5 : TEMPLATE CHROMOCELL ===\n";

    Individu<ChromoCell> individuChromo(
        1,
        ChromoCell("AB", "CD", "EF", "GH")
    );

    std::cout << "Individu "
              << individuChromo.getId()
              << " : "
              << individuChromo.getValeur()
              << "\n";

    std::cout << "[OK] Template compatible ChromoCell\n";

    std::cout << "\n====================================\n";
    std::cout << "  FIN DES TESTS INDIVIDU<T>\n";
    std::cout << "====================================\n";

    return 0;
}
