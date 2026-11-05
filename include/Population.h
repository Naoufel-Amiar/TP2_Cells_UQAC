#ifndef POPULATION_H
#define POPULATION_H

#include <cstddef>
#include <ios>
#include <istream>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "Individu.h"

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
    // Les unique_ptr sont les uniques proprietaires des individus.
    // Les pointeurs parentaux restent non proprietaires.
    std::map<int, std::unique_ptr<Individu<T>>> individus_;
    int prochainId_ = 1;

    Individu<T>* trouverInterne(int id) const
    {
        auto it = individus_.find(id);
        return it == individus_.end() ? nullptr : it->second.get();
    }

    void afficherArbreRecursif(
        const Individu<T>* individu,
        std::ostream& sortie,
        int profondeur
    ) const
    {
        if (!individu)
            return;

        sortie << std::string(
            static_cast<std::size_t>(profondeur) * 4, ' '
        ) << individu->getId()
          << " : " << individu->getValeur() << '\n';

        afficherArbreRecursif(
            individu->getParent1(),
            sortie,
            profondeur + 1
        );

        afficherArbreRecursif(
            individu->getParent2(),
            sortie,
            profondeur + 1
        );
    }

    void collecterAncetres(
        const Individu<T>* individu,
        int distance,
        std::map<int, int>& distances
    ) const
    {
        if (!individu)
            return;

        auto it = distances.find(individu->getId());

        if (it != distances.end() && it->second <= distance)
            return;

        distances[individu->getId()] = distance;

        collecterAncetres(
            individu->getParent1(),
            distance + 1,
            distances
        );

        collecterAncetres(
            individu->getParent2(),
            distance + 1,
            distances
        );
    }

public:
    Population() = default;
    ~Population() = default;

    Population(const Population&) = delete;
    Population& operator=(const Population&) = delete;

    // ==========================================
    // INFORMATIONS GENERALES
    // ==========================================

    std::size_t taille() const
    {
        return individus_.size();
    }

    bool estVide() const
    {
        return individus_.empty();
    }

    // ==========================================
    // AJOUT D'UN INDIVIDU
    // ==========================================

    int ajouter(const T& valeur)
    {
        if (prochainId_ == std::numeric_limits<int>::max())
        {
            throw std::overflow_error(
                "Limite des identifiants atteinte."
            );
        }

        const int id = prochainId_;

        auto individu = std::make_unique<Individu<T>>(
            id,
            valeur
        );

        individus_.emplace(id, std::move(individu));

        ++prochainId_;

        return id;
    }

    // ==========================================
    // COMBINAISON DE DEUX INDIVIDUS
    // ==========================================

    int combiner(int id1, int id2)
    {
        if (id1 == id2)
        {
            throw std::invalid_argument(
                "Les deux individus doivent etre differents."
            );
        }

        Individu<T>* parent1 = trouverInterne(id1);
        Individu<T>* parent2 = trouverInterne(id2);

        if (!parent1 || !parent2)
        {
            throw std::invalid_argument(
                "Un ou plusieurs individus sont introuvables."
            );
        }

        if (prochainId_ == std::numeric_limits<int>::max())
        {
            throw std::overflow_error(
                "Limite des identifiants atteinte."
            );
        }

        T valeur =
            parent1->getValeur() + parent2->getValeur();

        const int id = prochainId_;

        auto individu = std::make_unique<Individu<T>>(
            id,
            valeur,
            parent1,
            parent2
        );

        individus_.emplace(id, std::move(individu));

        ++prochainId_;

        return id;
    }

    // ==========================================
    // RECHERCHE D'UN INDIVIDU
    // ==========================================

    const Individu<T>* trouver(int id) const
    {
        return trouverInterne(id);
    }

    // ==========================================
    // SUPPRESSION D'UN INDIVIDU
    // ==========================================

    bool supprimer(int id)
    {
        Individu<T>* cible = trouverInterne(id);

        if (!cible)
            return false;

        // Detacher toutes les references avant
        // liberation de la cible.
        for (auto& entree : individus_)
        {
            Individu<T>* courant = entree.second.get();

            if (courant->getParent1() == cible)
                courant->setParent1(nullptr);

            if (courant->getParent2() == cible)
                courant->setParent2(nullptr);
        }

        individus_.erase(id);

        return true;
    }

    // ==========================================
    // AFFICHAGE DE L'ARBRE
    // ==========================================

    void afficherArbre(
        int id,
        std::ostream& sortie
    ) const
    {
        const Individu<T>* individu = trouver(id);

        if (!individu)
        {
            throw std::invalid_argument(
                "Individu introuvable pour l'affichage."
            );
        }

        afficherArbreRecursif(individu, sortie, 0);
    }

    // ==========================================
    // RECHERCHE D'UN ANCETRE COMMUN
    // ==========================================

    std::optional<AncetreCommun> rechercherAncetreCommun(
        int id1,
        int id2
    ) const
    {
        const Individu<T>* premier = trouver(id1);
        const Individu<T>* second = trouver(id2);

        if (!premier || !second)
        {
            throw std::invalid_argument(
                "Un ou plusieurs individus sont introuvables."
            );
        }

        std::map<int, int> distances1, distances2;

        // Distance 0 pour soi-meme :
        // utile si X est directement ancetre de Y.
        collecterAncetres(premier, 0, distances1);
        collecterAncetres(second, 0, distances2);

        std::optional<AncetreCommun> meilleur;

        for (const auto& entree : distances1)
        {
            auto it = distances2.find(entree.first);

            if (it == distances2.end())
                continue;

            const int d1 = entree.second;
            const int d2 = it->second;

            const long long total =
                static_cast<long long>(d1) + d2;

            const long long meilleurTotal = meilleur
                ? static_cast<long long>(
                    meilleur->distance1
                  ) + meilleur->distance2
                : std::numeric_limits<long long>::max();

            // En cas d'egalite, l'ID le plus petit
            // est choisi (ordre de std::map).
            if (total < meilleurTotal)
            {
                meilleur = AncetreCommun{
                    entree.first,
                    d1,
                    d2
                };
            }
        }

        return meilleur;
    }

    // ==========================================
    // SAUVEGARDE DE LA POPULATION
    // ==========================================

    void sauvegarder(
        std::ostream& sortie,
        const std::string& nomType
    ) const
    {
        sortie << nomType << ' '
               << individus_.size() << '\n';

        for (const auto& entree : individus_)
        {
            const Individu<T>& individu = *entree.second;

            sortie << individu.getId() << ' ';

            if (individu.getParent1())
                sortie << individu.getParent1()->getId();
            else
                sortie << '/';

            sortie << ' ';

            if (individu.getParent2())
                sortie << individu.getParent2()->getId();
            else
                sortie << '/';

            sortie << ' '
                   << individu.getValeur()
                   << '\n';
        }

        if (!sortie)
        {
            throw std::runtime_error(
                "Erreur d'ecriture de population."
            );
        }
    }

    // ==========================================
    // CHARGEMENT DE LA POPULATION
    // ==========================================

    // L'en-tete TYPE N a deja ete lu
    // par le controleur.
    void charger(
        std::istream& entree,
        std::size_t nombreIndividus
    )
    {
        // Construction dans une population temporaire :
        // en cas d'erreur, l'original reste intact.
        Population<T> temporaire;

        struct Parents
        {
            int p1;
            int p2;
        };

        std::map<int, Parents> liens;
        std::string ligne;

        for (std::size_t numero = 0;
             numero < nombreIndividus;
             ++numero)
        {
            if (!std::getline(entree >> std::ws, ligne))
            {
                throw std::runtime_error(
                    "Nombre de lignes insuffisant dans la population."
                );
            }

            std::istringstream flux(ligne);

            int id = 0;
            std::string parent1, parent2;
            T valeur;

            if (!(flux >> id >> parent1 >> parent2 >> valeur))
            {
                throw std::runtime_error(
                    "Ligne de population invalide : " + ligne
                );
            }

            flux >> std::ws;

            if (!flux.eof())
            {
                throw std::runtime_error(
                    "Donnees supplementaires : " + ligne
                );
            }

            if (id <= 0 ||
                id == std::numeric_limits<int>::max())
            {
                throw std::runtime_error(
                    "Identifiant invalide."
                );
            }

            if (temporaire.individus_.count(id))
            {
                throw std::runtime_error(
                    "Identifiant duplique : " +
                    std::to_string(id)
                );
            }

            auto convertirParent =
                [id](const std::string& texte) -> int
            {
                if (texte == "/")
                    return 0;

                std::istringstream f(texte);

                int parent = 0;
                char surplus;

                if (!(f >> parent) ||
                    (f >> surplus) ||
                    parent <= 0 ||
                    parent >= id)
                {
                    throw std::runtime_error(
                        "Identifiant de parent invalide : " +
                        texte
                    );
                }

                return parent;
            };

            int p1 = convertirParent(parent1);
            int p2 = convertirParent(parent2);

            if (p1 != 0 && p1 == p2)
            {
                throw std::runtime_error(
                    "Les deux parents doivent etre differents."
                );
            }

            temporaire.individus_.emplace(
                id,
                std::make_unique<Individu<T>>(id, valeur)
            );

            liens.emplace(id, Parents{p1, p2});

            if (id >= temporaire.prochainId_)
                temporaire.prochainId_ = id + 1;
        }

        // Tous les individus existent en memoire.
        // On peut maintenant lier les parents.
        for (const auto& entreeLiens : liens)
        {
            Individu<T>* enfant =
                temporaire.trouverInterne(
                    entreeLiens.first
                );

            const Parents& parents = entreeLiens.second;

            if (parents.p1)
            {
                auto* parent =
                    temporaire.trouverInterne(parents.p1);

                if (!parent)
                {
                    throw std::runtime_error(
                        "Parent 1 absent du fichier."
                    );
                }

                enfant->setParent1(parent);
            }

            if (parents.p2)
            {
                auto* parent =
                    temporaire.trouverInterne(parents.p2);

                if (!parent)
                {
                    throw std::runtime_error(
                        "Parent 2 absent du fichier."
                    );
                }

                enfant->setParent2(parent);
            }
        }

        individus_.swap(temporaire.individus_);

        std::swap(
            prochainId_,
            temporaire.prochainId_
        );
    }

    // ==========================================
    // LIBERATION DE LA POPULATION
    // ==========================================

    void vider()
    {
        individus_.clear();
        prochainId_ = 1;
    }
};

#endif
