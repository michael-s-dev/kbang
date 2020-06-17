#ifndef CHARACTERJESSEJONES_H
#define CHARACTERJESSEJONES_H

#include "characterbase.h"

class Player;

class CharacterJesseJones : public CharacterBase
{
Q_OBJECT
public:
    enum Type {
        JesseJones,
        PatBrennan
    };
    CharacterJesseJones(QObject *parent , Type);
    virtual void useAbility(Player* targetPlayer );
    virtual void useAbility(QList<PlayingCard*> cards);
    virtual void draw(bool specialDraw);
private:
    Player* mp_targetPlayer;
    PlayingCard* mp_targetCard;
    Type m_type;
};
#endif // CHARACTERJESSEJONES_H
