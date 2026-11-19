#ifndef HORLOGECELL_H
#define HORLOGECELL_H

class HorlogeCell
{
private:
    int heures_;
    int minutes_;

public:
    HorlogeCell();
    HorlogeCell(int heures, int minutes);

    int getHeures() const;
    int getMinutes() const;

    void setHeures(int heures);
    void setMinutes(int minutes);



#endif