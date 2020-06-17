#ifndef CHARACTERSIDKETCHUM_H
#define CHARACTERSIDKETCHUM_H

#include "characterbase.h"

class CharacterSidKetchum : public CharacterBase
{
Q_OBJECT
public:
    enum Type{
        SidKetchum,
        DocHoliday
    };
    CharacterSidKetchum(QObject *parent , Type type = SidKetchum);
    virtual void useAbility(QList<PlayingCard*> cards);
    virtual void useAbility(Player* targetPlayer);


private:
     PlayingCard* swapCards();
     PlayingCard* mp_bang;
     Type m_type;
     int m_virtualbang;

};
#endif // CHARACTERSIDKETCHUM_H
