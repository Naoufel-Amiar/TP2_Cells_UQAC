#ifndef POPULATION_H
#define POPULATION_H

#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>

#include "Individu.h"

// Resultat d'une recherche d'ancetre commun
struct AncetreCommun
{
    int id;
    int distance1;
    int distance2;
};

template<typename T>
class Population
{
private:
    // Une seule instance de chaque individu
    std::map<
        int,
        std::unique_ptr<Individu<T>>
    > individus_;

    // Prochain identifiant disponible
    int prochainId_ = 1;

    // Recherche interne d'un individu
    Individu<T>* trouverInterne(int id) const;

    // Affichage recursif d'une genealogie
    void afficherArbreRecursif(
        const Individu<T>* individu,
        std::ostream& sortie,
        int profondeur
    ) const;

    // Recherche des ancetres et distances
    void collecterAncetres(
        const Individu<T>* individu,
        int distance,
        std::map<int, int>& distances
    ) const;

public:
    // Constructeur et destructeur
    Population() = default;
    ~Population() = default;

    // Population non copiable
    Population(const Population&) = delete;
    Population& operator=(const Population&) = delete;

    // Informations generales
    std::size_t taille() const;
    bool estVide() const;

    // Ajout d'un individu sans parent
    int ajouter(const T& valeur);

    // Combinaison de deux individus
    int combiner(int id1, int id2);

    // Recherche d'un individu
    const Individu<T>* trouver(int id) const;

    // Suppression d'un individu
    bool supprimer(int id);

    // Affichage de l'arbre genealogique
    void afficherArbre(
        int id,
        std::ostream& sortie
    ) const;

    // Recherche d'un ancetre commun
    std::optional<AncetreCommun>
    rechercherAncetreCommun(
        int id1,
        int id2
    ) const;

    // Sauvegarde de la population
    void sauvegarder(
        std::ostream& sortie,
        const std::string& nomType
    ) const;

    // Chargement de la population
    // L'en-tete du fichier est lu par TransTerminal
    void charger(
        std::istream& entree,
        std::size_t nombreIndividus
    );

    // Liberation de tous les individus
    void vider();
};

#endif
