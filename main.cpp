#include <exception>
#include <iostream>

#include "TransTerminal.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr
            << "Utilisation : "
            << argv[0]
            << " <fichier_transactions>\n";

        return 1;
    }

    try
    {
        TransTerminal terminal;
        terminal.executer(argv[1]);
    }
    catch (const std::exception& erreur)
    {
        std::cerr
            << "Erreur fatale : "
            << erreur.what() << '\n';

        return 1;
    }

    return 0;
}
