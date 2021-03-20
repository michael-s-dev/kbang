#ifndef CHARACTERBLACKJACK_H
#define CHARACTERBLACKJACK_H

#include "characterbase.h"

class CharacterBlackJack : public CharacterBase
{
Q_OBJECT;
public:
    enum Type {
        BlackJack,
        KingSchultz,
        BillNoface,
        SeanMallory,
        Tuco
    };

    CharacterBlackJack(QObject *parent , Type);
    virtual void draw(bool specialDraw);
    virtual int maxLifePoints() const;


private:
    Type m_type;
};

#endif // CHARACTERBLACKJACK_H



