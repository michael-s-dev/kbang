#ifndef CHARACTERCHUCKWENGMAN_H
#define CHARACTERCHUCKWENGMAN_H

#include "characterbase.h"


class CharacterChuckWengam : public CharacterBase
{
Q_OBJECT
public:
    CharacterChuckWengam(QObject *parent);
    virtual void useAbility();


};
#endif
