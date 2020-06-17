#ifndef CHARACTERHERBHUNTER_H
#define CHARACTERHERBHUNTER_H

#include "characterbase.h"

class CharacterHerbHunter : public CharacterBase
{
Q_OBJECT;
public:
    enum Type {
        HerbHunter,
        GregDigger,
        ApacheKid
    };
    CharacterHerbHunter(QObject* parent , Type);

    virtual int maxLifePoints() const;

private:
    Type m_type;
};

#endif
