
#ifndef INDIVIDU_H
#define INDIVIDU_H

// ==========================================
// CLASSE GENERIQUE INDIVIDU<T>
// ==========================================

template<typename T>
class Individu
{
private:
    // Identifiant de l'individu
    int id_;

    // Caracteristiques genetiques
    T valeur_;

    // Pointeurs non proprietaires vers les parents
    Individu<T>* parent1_;
    Individu<T>* parent2_;

public:
    // ======================================
    // CONSTRUCTEUR
    // ======================================

    Individu(
        int id,
        const T& valeur,
        Individu<T>* parent1 = nullptr,
        Individu<T>* parent2 = nullptr
    )
        : id_(id),
          valeur_(valeur),
          parent1_(parent1),
          parent2_(parent2)
    {
    }

    // ======================================
    // ACCESSEURS
    // ======================================

    int getId() const
    {
        return id_;
    }

    const T& getValeur() const
    {
        return valeur_;
    }

    const Individu<T>* getParent1() const
    {
        return parent1_;
    }

    const Individu<T>* getParent2() const
    {
        return parent2_;
    }

    // ======================================
    // MODIFICATION DES PARENTS
    // ======================================

    void setParent1(Individu<T>* parent)
    {
        parent1_ = parent;
    }

    void setParent2(Individu<T>* parent)
    {
        parent2_ = parent;
    }

    // ======================================
    // INTERDICTION DE COPIE
    // ======================================

    Individu(const Individu&) = delete;

    Individu& operator=(const Individu&) = delete;
};

#endif
