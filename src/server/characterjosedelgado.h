#ifndef CHARACTERJOSEDELGADO_H
#define CHARACTERJOSEDELGADO_H

#include "characterbase.h"

class CharacterJoseDelgado : public CharacterBase
{
Q_OBJECT
public:
    CharacterJoseDelgado(QObject *parent);
    virtual void useAbility(QList<PlayingCard*> cards);
    virtual int maxLifePoints() const;

};

#endif
