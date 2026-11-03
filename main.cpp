
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr
            << "Utilisation : TP2_Cells <fichier_transactions>"
            << std::endl;

        return 1;
    }

    std::string fichierTransactions = argv[1];

    std::cout << "================================\n";
    std::cout << "  TP2 - Arborescence genetique\n";
    std::cout << "================================\n";

    std::cout << "Fichier de transactions : "
              << fichierTransactions << std::endl;

    return 0;
}
