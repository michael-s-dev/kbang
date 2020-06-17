#ifndef CHARACTERSTARKFUENTE_H
#define CHARACTERSTARKFUENTE_H

#include "characterbase.h"

class CharacterStarkFuente : public CharacterBase
{
Q_OBJECT;
public:
    enum Type {
        ElenaFuente,
        MollyStark

    };
    CharacterStarkFuente(QObject *parent , Type type);

    virtual int maxLifePoints() const;
    virtual void respondCard(ReactionHandler*, PlayingCard* targetCard);

private:
    PlayingCard* swapCards(PlayingCard* card);

    PlayingCard* mp_bang;
    PlayingCard* mp_missed;
    Type m_type;

};

#endif
