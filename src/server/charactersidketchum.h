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
    virtual void useAbility(QList<PlayingCard*> cards, Player* targetPlayer);


private:
     Type m_type;
     PlayingCard* mp_bang;

};
#endif // CHARACTERSIDKETCHUM_H
