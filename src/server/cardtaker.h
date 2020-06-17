#ifndef CARDTAKER_H
#define CARDTAKER_H

#include "playingcard.h"
#include "playingcard.h"

class CardTaker : public PlayingCard
{
public:
    enum Type {
        Panic,
        CatBalou,
        conestoga,
        cancan,
        RagTime,
        Gift
    };

    CardTaker(Game *game, int id, Type, CardSuit, CardRank);
    ~CardTaker();

    virtual void play();
    virtual void play(Player* targetPlayer );
    virtual void play(PlayingCard* targetCard );
    virtual void play(PlayingCard* targetCard , PlayingCard* targetCard2 );
    virtual void play(PlayingCard* targetCard , Player* targetPlayer);

private:
    Type m_type;
    PlayingCard* m_targetCard;
};

#endif // CARDTAKER_H
