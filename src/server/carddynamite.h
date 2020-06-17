#ifndef CARDDYNAMITE_H
#define CARDDYNAMITE_H

#include "playingcard.h"
#include "checkdeckresulthandler.h"

class CardDynamite : public PlayingCard, public CheckDeckResultHandler
{
public:
    CardDynamite(Game *game, int id, CardSuit, CardRank);
    virtual ~CardDynamite();

    virtual void play();
    virtual void checkResult(bool result);
    virtual void registerPlayer(Player* player);
    virtual void unregisterPlayer(Player* player);

    static bool checkDynamite(PlayingCard*);
private:
    static const int PredrawCheck = 20;
};

#endif // CARDDYNAMITE_H
